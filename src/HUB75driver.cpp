// 
// 
// 

#include "HUB75driver.h"


static HUB75driver *activePanel = NULL;

HUB75driver::HUB75driver()
{
	
}

int HUB75driver::init(boolean dbuf)
{
	/*
	A A0,B A1,C A2,R1 2,R2 5,B1 4,B2 7,G1 3,G2 6,LAT A3,CLK 8,OE 9
	*/
	DDRD = DDRD | B11111100;//sets pins 2 to 7 as outputs without changing the value of pins 0 & 1, which are RX & TX
	DDRC = DDRC | B00001111;//Set pins A0,A1,A2,A3 as output
	DDRB = DDRB | B00000011;//Set pins 8,9 as output
	PORTD = PORTD & B00000011;//Zero to outputs 2 to 7
	PORTC = PORTC & B11111000;//Zero to A0,A1,A2
	PORTB = (PORTB & B11111110) | B00000010;//* - CLK low,9 OE high

	// Allocate and initialize matrix buffer:
	buffsize = 32 * 8 * 3; // x3 = 3 bytes holds 4 planes "packed"
	matrixbuff[0] = (uint8_t *)calloc(buffsize, sizeof(uint8_t));//(int*) calloc (i,sizeof(int));
	if (matrixbuff[0] == NULL) return 1;
	if (dbuf) {
		matrixbuff[1] = (uint8_t *)calloc(buffsize, sizeof(uint8_t));
		if (matrixbuff[1] == NULL) return 1;
		display_buffer_index = 0;
		draw_buffer_index = 1;
	}
	else {
		display_buffer_index = 0;
		draw_buffer_index = 0;
	}
	
	use_dbuf = dbuf;
	swap_needed = 0;

	activePanel = this; // For interrupt hander

	

	return 0;
}

ISR(TIMER1_COMPA_vect) {
	activePanel->drive();
}

void HUB75driver::drive()
{
	/*
	Using 4 bits per color,3 bytes packed like this
	byte 1 B2_0,G2_0,R2_0,B1_0,G1_0,R1_0,B2_3,G2_3
	byte 2 B2_1,G2_1,R2_1,B1_1,G1_1,R1_1,R2_3,B1_3
	byte 3 B2_2,G2_2,R2_2,B1_2,G1_2,R1_2,G1_3,R1_3
	Binary coded modulation
	Will need to execute cycles 0,1,3,7
	*/

	//*** Debug ***
	//long int time_start = micros();
	//*****

	int addr, addr_pre,i;
	uint8_t data_out,offswt=0;
	uint8_t* img = matrixbuff[display_buffer_index],ptr;

	switch (pwm_count) {
	case 0:
	case 7:
		addr_pre = line * 32 * 3;
		break;
	case 1:
		addr_pre = line * 32 * 3 + 32;
		break;
	case 3:
		addr_pre = line * 32 * 3 + 64;
		break;
	}
	
	switch (pwm_count) {
	case 0:
	case 1:
	case 3:
		for (i = 0; i < 32 ; i++) {
			//addr = addr_pre + i;
			//ptr = img[addr_pre + i];
			PORTD = img[addr_pre + i];

			//PORTD = img[addr] & B11111100;
			//PORTB = PINB | B00000001;//clock high
			//PORTB = PINB & B11111110;//clock low
			{__asm__ volatile ("SBI 5 , 0\n\t" "CBI 5 , 0\n\t"); }//toggle clock high,low
			
		}
		break;
	case 7:
		for (i = 0; i < 32; i++) {
			addr = addr_pre + i;
			data_out = ((img[addr] & B00000011) << 6) + ((img[addr + 32] & B00000011) << 4) + ((img[addr + 64] & B00000011) << 2);
			PORTD = data_out;//PORTD = data_out & B11111100;
			//PORTB = PINB | B00000001;//clock high
			//PORTB = PINB & B11111110;//clock low
			{__asm__ volatile ("SBI 5 , 0\n\t" "CBI 5 , 0\n\t"); }//toggle clock high,low
		}
		break;
	}

	if (pwm_count == 0 || pwm_count == 1 || pwm_count == 3 || pwm_count == 7) {
		PORTB = PINB | B00000010;//OE high
		PORTC = (PINC & B11111000) | line;//Select line
		PORTC = PINC | B00001000;//LAT high
		PORTC = PINC & B11110111;//LAT low
		PORTB = PINB & B11111101;//OE low
		/*
		{__asm__ volatile (
			"SBI 5 , 1\n\t" //OE high PORTB
			"SBI 8 , 3\n\t" //LAT high PORTC
			"IN r16 , 6\n\t"//Read from PINC
			"ANDI r16 , 0b11111000\n\t"
			"LD r0, %a[line]\n\t"
			"ADD r0, r16\n\t"
			"OUT 8, r0\n\t"
			"CBI 8 , 3\n\t" //LAT low
			"CBI 5 , 1\n\t" //OE low
		:
		: [line]  "e" ((uint8_t *)line)
		:"r16","r0");
		}/**/
	}
	
	if (pwm_count < 16) {
		pwm_count++;
	}
	else {
		pwm_count = 0;
		if (line < 7) line++;//Line counter 0-7
		else {
			line = 0;
			if (swap_needed==1) {
				if (display_buffer_index == 0) {
					display_buffer_index = 1;
					draw_buffer_index = 0;
				}
				else {
					display_buffer_index = 0;
					draw_buffer_index = 1;
				}
				swap_needed = 0;
			}
		}
	}
	//*** Debug ***
	//long elapsed = micros() - time_start;
	//Serial.println(elapsed);
	//********************
}

void HUB75driver::draw_point(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b)
{
	/*
	Using 4 bits per color,3 bytes packed like this
	3 byte per 2 pixels
	32*3 bytes per line
	First 32 bytes is bit 0 in format B2,G2,R2,B1,G1,R1,x,x
	Second 32 bytes bit 1
	Third 32 bytes bit 2
	Bit4 packed in lass two bits of each byte so for column n
	n*3 B2,G2
	n*3+1 R2,B1
	n*3+2 G1,R1

	*/
	int addr_0, addr_1, addr_2;
	int base = (y%8) * 32 * 3;
	uint8_t* img = matrixbuff[draw_buffer_index];
	addr_0 = base + x;
	addr_1 = base + 32 + x;
	addr_2 = base + 64 + x;

	if (y < 8) {
		//Set bits 5,4,3 - B1,G1,R1
		img[addr_0] = ((b&bit0) << 4) + ((g&bit0) << 3) + ((r&bit0) << 2) + (img[addr_0] & B11100011);
		img[addr_1] = ((b&bit1) << 3) + ((g&bit1) << 2) + ((r&bit1) << 1) + (img[addr_1] & B11100011);
		img[addr_2] = ((b&bit2) << 2) + ((g&bit2) << 1) + (r&bit2) + (img[addr_2] & B11100011);
		img[addr_1] = ((b&bit3) >> 3) + (img[addr_1] & B11111110);
		img[addr_2] = ((g&bit3) >> 2) + ((r&bit3) >> 3) + (img[addr_2] & B11111100);
	}
	else {
		img[addr_0] = ((b&bit0) << 7) + ((g&bit0) << 6) + ((r&bit0) << 5) + (img[addr_0] & B00011111);
		img[addr_1] = ((b&bit1) << 6) + ((g&bit1) << 5) + ((r&bit1) << 4) + (img[addr_1] & B00011111);
		img[addr_2] = ((b&bit2) << 5) + ((g&bit2) << 4) + ((r&bit2) << 3) + (img[addr_2] & B00011111);
		img[addr_0] = ((b&bit3) >> 2) + ((g&bit3) >> 3) + (img[addr_0] & B11111100);
		img[addr_1] = ((r&bit3) >> 2) + (img[addr_1] & B11111101);
	}
}

void HUB75driver::clear()
{
	memset(matrixbuff[draw_buffer_index], 0, buffsize);
}

void HUB75driver::swapBuffers()
{
	if (use_dbuf) {
		swap_needed = 1;
	}
}

void HUB75driver::start()
{
	//Set timer1
	cli();// disable global interrupts
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1 = 0;//initialize counter value to 0

	TCCR1B |= (1 << CS10); //No prescaller
	TCCR1B |= (1 << WGM12);//CTC mode
	OCR1A = 992;//62nsec

	TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
	sei();//allow interrupts
}


