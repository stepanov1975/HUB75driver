#include <HUB75driver.h>
#include "font.h"

HUB75driver matrix;

const char str[] PROGMEM = { "Hello world! This is scrolling text ;)" };

void setup()
{

	//if first argument is true double buffering used, need swapBuffers() to refresh
	//if second argument is true additional dimming will be applyed. brightness will reduce by half
	matrix.init(true, true);
	matrix.begin();//Enable interupt
}

void loop()
{
	uint8_t i = 0;
	uint8_t len = strlen_P(str);
	for (i = 0; i < len; i++) {
		for (uint8_t offset = 0; offset < 8; offset++) {
			
			matrix.cleanScreen();
			put_string_from_progmem(-offset, 4, str, i, 3, 0, 0);
			//put_string_from_progmem(-offset+1, 4, str, i, r, g, b);
			matrix.swapBuffers();
			delay(25);
		}
	}
	
}

void put_string_from_progmem(uint8_t x, uint8_t y, const char message[], uint8_t start, uint8_t r, uint8_t g, uint8_t b) {
	char c;
	uint8_t len = strlen_P(message);
	if (!message) return;
	for (uint8_t i = 0; i < 5; i++) {
		uint8_t offset = start + i;
		if (offset < len) {
			c = pgm_read_word_near(message + offset);
			putNormalChar(x + 8 * i, y, c, r, g, b);
		}
	}
	
}

void putNormalChar(uint8_t x, uint8_t y, char c, uint8_t r, uint8_t g, uint8_t b) {
	// fonts defined for ascii 32 and beyond (index 0 in font array is ascii 32);
	byte charIndex = c - 32;
	putChar(x, y, myfont8x8[charIndex], 8, 8, r, g, b);
}

void putChar(uint8_t x, uint8_t y, const unsigned char * c, uint8_t h, uint8_t w, uint8_t r, uint8_t g, uint8_t b) {
	for (byte row = 0; row<h; row++)
	{
		byte rowDots = pgm_read_byte_near(&c[row]);
		for (byte col = 0; col<w; col++)
		{
			if (rowDots & (1 << (col)))
				matrix.drawPixel(x + col, y + row, r, g, b);
		}
	}
}