// Library to drive HUB75 interface 32x16 LED matrix using Arduino Uno
// RGBmatrixPanel Arduino library for Adafruit used as example
// Pins usaga compatible with Adafruit RGBmatrixPanel Arduino library
// https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/
// Pins mapping for HUB75 interface A A0,B A1,C A2,R1 2,R2 5,B1 4,B2 7,G1 3,G2 6,LAT A3,CLK 8,OE 9

#include "HUB75driver.h"

static HUB75driver *activePanel = NULL;

#define pew "ld  __tmp_reg__, %a[ptr]+"    "\n\t"   \
      "out %[data]    , __tmp_reg__" "\n\t"   \
      "SBI 5 , 0"     "\n\t"   \
      "CBI 5 , 0"     "\n\t"

#define pew1 "ld  __tmp_reg__, %a[ptr]+"    "\n\t"   \
      "bst __tmp_reg__,1 " "\n\t"   \
      "bld r1 , 7 " "\n\t"   \
      "bst __tmp_reg__,0 " "\n\t"   \
      "bld r1,6 " "\n\t"   \
	  "ld  __tmp_reg__, %a[ptr1]+"    "\n\t"   \
	  "bst __tmp_reg__,1 " "\n\t"   \
	  "bld r1,5 " "\n\t"   \
	  "bst __tmp_reg__,0 " "\n\t"   \
	  "bld r1,4 " "\n\t"   \
	  "ld  __tmp_reg__, %a[ptr2]+"    "\n\t"   \
	  "bst __tmp_reg__,1 " "\n\t"   \
	  "bld r1,3 " "\n\t"   \
	  "bst __tmp_reg__,0 " "\n\t"   \
	  "bld r1,2 " "\n\t"   \
      "out %[data]    , r1" "\n\t"   \
      "SBI 5 , 0"     "\n\t"   \
      "CBI 5 , 0"     "\n\t"

#define pew2 "out %[data]    , __tmp_reg__" "\n\t"   \
      "SBI 5 , 0"     "\n\t"   \
      "CBI 5 , 0"     "\n\t"

HUB75driver::HUB75driver()
{
	
}

int HUB75driver::init(boolean dbuf,boolean extra_dim)
{
	/*Initialisation of matrix
	if dbuf=true double buffering used
	in this case swapBuffers() function need to be called to update picture
	Pin mapping:
	A A0,B A1,C A2,R1 2,R2 5,B1 4,B2 7,G1 3,G2 6,LAT A3,CLK 8,OE 9
	*/

	use_dbuf = dbuf;
	swap_needed = 0;
	half_brightness = extra_dim;
	activePanel = this; // For interrupt hander

	DDRD = DDRD | B11111100;//sets pins 2 to 7 as outputs without changing the value of pins 0 & 1, which are RX & TX
	DDRC = DDRC | B00001111;//Set pins A0,A1,A2,A3 as output
	DDRB = DDRB | B00000011;//Set pins 8,9 as output
	PORTD = PORTD & B00000011;//Zero to outputs 2 to 7
	PORTC = PORTC & B11111000;//Zero to A0,A1,A2
	PORTB = (PORTB & B11111110) | B00000010;//* - CLK low,9 OE high

	// Allocate and initialize matrix buffer:
	buffsize = 32 * 8 * 3; // x3 = 3 bytes holds 4 planes "packed"
	matrixbuff[0] = (uint8_t *)calloc(buffsize, sizeof(uint8_t));//allocate for single buffer
	if (matrixbuff[0] == NULL) return 1;
	if (dbuf) {//If double buffering used
		matrixbuff[1] = (uint8_t *)calloc(buffsize, sizeof(uint8_t));//Alocate for second buffer
		if (matrixbuff[1] == NULL) return 1;
		display_buffer_index = 0;
		draw_buffer_index = 1;
	}
	else {
		display_buffer_index = 0;
		draw_buffer_index = 0;
	}
	
	
	return 0;
}

ISR(TIMER1_COMPA_vect) {
	activePanel->drive();//Matrix refrshing function
}

void HUB75driver::drive()
{
	/*
	This function refreshing matix
	Using 4 bits per color,3 bytes packed like this:
	3 byte per 2 pixels
	32*3 bytes per line
	First 32 bytes bits 7 to 2 is bit 0 in format B2,G2,R2,B1,G1,R1,x,x
	Second 32 bytes bit 1
	Third 32 bytes bit 2
	Bit4 packed in lass two bits of each byte 
	Binary Code Modulation used as it faster then PWM
	*/

	//*** Debug ***
	//long int time_start = micros();
	//*****
	
	int addr, addr_pre,i,addr1,addr2;
	uint8_t data_out;
	uint8_t  *ptr,*ptr1,*ptr2;
	img = matrixbuff[display_buffer_index];
	
	//Calculate starting address for relevant bit
	if (pwm_count==0 || pwm_count == 7) addr_pre = line * 96;
	else if (pwm_count == 1) addr_pre = line * 96 + 32;
	else if (pwm_count == 3) addr_pre = line * 96 + 64;
	
	buffptr = &img[addr_pre];
	ptr = (uint8_t *)buffptr;
	
	if (pwm_count == 0 || pwm_count == 1 || pwm_count == 3) {//For bits 0,1,2
		//Clock in data for 32 columns
		//~12us for 32 data shift commands
		//x4 pixels can be driven if 64us period will be selected
		{
			__asm__ volatile(
				pew pew pew pew pew pew pew pew
				pew pew pew pew pew pew pew pew
				pew pew pew pew pew pew pew pew
				pew pew pew pew pew pew pew pew
				::[ptr]  "e" (ptr),
				[data] "I" (_SFR_IO_ADDR(PORTD))
				:"r0"
				);
		}//asm

	}//if
	else if (pwm_count == 7) {//For bit 3
		buffptr = &img[addr_pre + 32];
		ptr1 = (uint8_t *)buffptr;
		buffptr = &img[addr_pre + 64];
		ptr2 = (uint8_t *)buffptr;
		//Clock in data for 32 columns
		//~52us for 32 data shift commands
		{
			__asm__ volatile(
				pew1 pew1 pew1 pew1 pew1 pew1 pew1 pew1
				pew1 pew1 pew1 pew1 pew1 pew1 pew1 pew1
				pew1 pew1 pew1 pew1 pew1 pew1 pew1 pew1
				pew1 pew1 pew1 pew1 pew1 pew1 pew1 pew1
				::[ptr]  "e" (ptr), [ptr1]  "e" (ptr1), [ptr2]  "e" (ptr2),
				[data] "I" (_SFR_IO_ADDR(PORTD))
				: "r1"
				);
		}//asm
	}//if
	
	if (half_brightness && pwm_count == 16) {
		{
			__asm__ volatile(
				"CLR __tmp_reg__ \n\t"
				pew2 pew2 pew2 pew2 pew2 pew2 pew2 pew2
				pew2 pew2 pew2 pew2 pew2 pew2 pew2 pew2
				pew2 pew2 pew2 pew2 pew2 pew2 pew2 pew2
				pew2 pew2 pew2 pew2 pew2 pew2 pew2 pew2
				::[data] "I" (_SFR_IO_ADDR(PORTD))
				);
		}//asm
	}
	

	if (pwm_count == 0 || pwm_count == 1 || pwm_count == 3 || pwm_count == 7) {
		//Display clocked in data
		PORTB = PINB | B00000010; //OE high
		PORTC = (PINC & B11111000) | line; //Select line
		{__asm__ volatile (
			"SBI 8 , 3\n\t" //LAT high PORTC
			"CBI 8 , 3\n\t" //LAT low
			"CBI 5 , 1\n\t" //OE low
			);
		}//asm
	}//if
	
	//Counters for lines and Binary Code Modulation
	if (pwm_count < pwm_count_max) {//15 levels per bit
		pwm_count++;
	}
	else {
		pwm_count = 0;
		if (line < 7) line++;//Line counter 0-7
		else {
			line = 0;
			if (swap_needed==1) {//If double buffering mode
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
	/*Function to draw point on matrix
	Coordinates starts from 0,0
	Using 4 bits per color,3 bytes packed like this
	3 byte per 2 pixels
	32*3 bytes per line
	First 32 bytes is bit 0 in format B2,G2,R2,B1,G1,R1,x,x
	Second 32 bytes bit 1
	Third 32 bytes bit 2
	Bit4 packed in lass two bits of each byte
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
	//Clear panel
	memset(matrixbuff[draw_buffer_index], 0, buffsize);
}

void HUB75driver::swapBuffers()
{
	//If double buffer mode used this function need to be called each time new information 
	//need to be displayed
	//Only flag raised here Actual swap will be synchronised with end of frame
	if (use_dbuf) {
		swap_needed = 1;
	}
}

void HUB75driver::start()
{
	//Start refreshing Nothing will be displayed before this function called
	//Set timer1
	cli();// disable global interrupts
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1 = 0;//initialize counter value to 0

	TCCR1B |= (1 << CS10); //No prescaller
	TCCR1B |= (1 << WGM12);//CTC mode
	if (half_brightness) {
		OCR1A = 496;//31nsec
		pwm_count_max = 32;
	}
	else {
		OCR1A = 992;//62nsec
		pwm_count_max = 16;
	}

	TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
	sei();//allow interrupts
}


