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

	//Set timer1
	cli();// disable global interrupts
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1 = 0;//initialize counter value to 0

	TCCR1B |=  (1 << CS10); //No prescaller
	TCCR1B |= (1 << WGM12);//CTC mode
	OCR1A = 992;//62nsec
						   
	TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
	sei();//allow interrupts

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
	int addr, addr_pre,i;
	uint8_t data_out;
	uint8_t* img = matrixbuff[display_buffer_index];

	switch (pwm_count) {
	case 0:
	case 7:
		addr_pre = line * 32 * 3;
		break;
	case 1:
		addr_pre = line * 32 * 3 + 1;
		break;
	case 3:
		addr_pre = line * 32 * 3 + 2;
		break;
	}

	switch (pwm_count) {
	case 0:
	case 1:
	case 3:
		for (i = 0; i < 32*3; i+=3) {
			addr = addr_pre + i;
			PORTD = img[addr] & B11111100;
			PORTB = PINB | B00000001;//clock high
			PORTB = PINB & B11111110;//clock low
		}
		break;
	case 7:
		for (i = 0; i < 32 * 3; i += 3) {
			addr = addr_pre + i;
			data_out = ((img[addr] & B00000011) << 6) + ((img[addr + 1] & B00000011) << 4) + ((img[addr + 2] & B00000011) << 2);
			PORTD = data_out & B11111100;
			PORTB = PINB | B00000001;//clock high
			PORTB = PINB & B11111110;//clock low
		}
		break;
	}

	if (pwm_count == 0 || pwm_count == 1 || pwm_count == 3 || pwm_count == 7) {
		PORTB = PINB | B00000010;//OE high
		PORTC = (PINC & B11111000) | line;//Select line
		PORTC = PINC | B00001000;//LAT high
		PORTC = PINC & B11110111;//LAT low
		PORTB = PINB & B11111101;//OE low
	}

	//********************
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
}

void HUB75driver::draw_point(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b)
{
	int addr_s, addr_s1, addr_s2;
	uint8_t* img = matrixbuff[draw_buffer_index];
	if (x < 0 || y < 0 || x>31 || y>15) return;
	if (y < 8) {
		addr_s = (y * 32 + x) * 3;
		addr_s1 = addr_s + 1;
		addr_s2 = addr_s + 2;
		img[addr_s] = ((b&bit0) << 4) + ((g&bit0) << 3) + ((r&bit0) << 2) + (img[addr_s] & B11100011);
		img[addr_s1] = ((b&bit1) << 3) + ((g&bit1) << 2) + ((r&bit1) << 1) + (img[addr_s] & B11100011);
		img[addr_s2] = ((b&bit2) << 2) + ((g&bit2) << 1) + (r&bit2) + (img[addr_s] & B11100011);
		img[addr_s1] = ((b&bit3) >> 3) + (img[addr_s1] & B11111110);
		img[addr_s2] = ((g&bit3) >> 2) + ((r&bit3) >> 3) + (img[addr_s2] & B11111100);

	}
	else {
		addr_s = ((y - 8) * 32 + x) * 3;
		addr_s1 = addr_s + 1;
		addr_s2 = addr_s + 2;
		img[addr_s] = ((b&bit0) << 7) + ((g&bit0) << 6) + ((r&bit0) << 5) + (img[addr_s] & B00011111);
		img[addr_s1] = ((b&bit1) << 6) + ((g&bit1) << 5) + ((r&bit1) << 4) + (img[addr_s1] & B00011111);
		img[addr_s2] = ((b&bit2) << 5) + ((g&bit2) << 4) + ((r&bit2) << 3) + (img[addr_s2] & B00011111);
		img[addr_s] = ((b&bit3) >> 2) + ((g&bit3) >> 3) + (img[addr_s] & B11111100);
		img[addr_s1] = ((r&bit3) >> 2) + (img[addr_s1] & B11111101);/**/
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


