#include <HUB75driver.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#include "fontBig.h"

HUB75driver matrix;

void setup()
{
	//if first argument is true double buffering used, need swapBuffers() to refresh
	//if second argument is true additional dimming will be applyed. brightness will reduce by half
	//It is impossible to use double buffering in this example becouse amount of memort
	//used by other libraries leave no room for second buffer each buffer takes 768 bytes
	matrix.init(false, true);
	matrix.start();//Enable interupt
	setSyncProvider(RTC.get);   // the function to get the time from the RTC

}

void loop()
{
	uint8_t r, g, b;
	r = 4;
	g = 1;
	b = 0;
	putLargeTime(2, 2, hour(), minute(), second(), r, g, b);
	delay(10);
}

void putLargeTime(uint8_t x, uint8_t y, int h, int m, int s, uint8_t r, uint8_t g, uint8_t b)
{
	//Width =6 
	putDigitLarge(x, y, '0' + h / 10, r, g, b);
	putDigitLarge(x + 6, y, '0' + h % 10, r, g, b);

	putDigitLarge(x + 15, y, '0' + m / 10, r, g, b);
	putDigitLarge(x + 21, y, '0' + m % 10, r, g, b);

	if (millis()%1000 >500) {
		r = 0;
		g = 0;
		b = 0;
	}

	matrix.draw_point(x + 13, y + 2, r, g, b);
	matrix.draw_point(x + 14, y + 2, r, g, b);
	matrix.draw_point(x + 13, y + 3, r, g, b);
	matrix.draw_point(x + 14, y + 3, r, g, b);

	matrix.draw_point(x + 13, y + 8, r, g, b);
	matrix.draw_point(x + 14, y + 8, r, g, b);
	matrix.draw_point(x + 13, y + 9, r, g, b);
	matrix.draw_point(x + 14, y + 9, r, g, b);
}

void putDigitLarge(uint8_t x, uint8_t y, char c, uint8_t r, uint8_t g, uint8_t b)
{
	// fonts defined for ascii 32 and beyond (index 0 in font array is ascii 32);
	byte charIndex = c - '0' + 22;
	putChar(x, y, bigFont[charIndex], 12, 6, r, g, b);
}

void putChar(uint8_t x, uint8_t y, const unsigned char * c, uint8_t h, uint8_t w, uint8_t r, uint8_t g, uint8_t b) {
	for (byte row = 0; row<h; row++)
	{
		byte rowDots = pgm_read_byte_near(&c[row]);
		for (byte col = 0; col<w; col++)
		{
			if (rowDots & (1 << (w - col - 1)))
				matrix.draw_point(x + col, y + row, r, g, b);
			else
				matrix.draw_point(x+col, y+row, 0,0,0);
		}
	}
}