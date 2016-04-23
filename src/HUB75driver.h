// HUB75driver.h

#ifndef _HUB75DRIVER_h
#define _HUB75DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define bit0 B00000001
#define bit1 B00000010
#define bit2 B00000100
#define bit3 B00001000

class HUB75driver
{
public:
	HUB75driver();
	int init(boolean dbuf);
	void drive();
	void draw_point(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b);
	void clear();
	void swapBuffers();
	void start();

private:
	uint8_t         *matrixbuff[2];
	boolean use_dbuf;
	volatile uint8_t pwm_count,line,display_buffer_index,draw_buffer_index,swap_needed;
	int buffsize;
};

#endif

