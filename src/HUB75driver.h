// HUB75driver.h

#ifndef _HUB75DRIVER_h
#define _HUB75DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
#endif

#define bit0 B00000001
#define bit1 B00000010
#define bit2 B00000100
#define bit3 B00001000
#define RSTBITSRGB1 B11100011
#define RSTBITSRGB2 B00011111

//Assembly cod for bits 0,1,2
#define pew "ld  __tmp_reg__, %a[ptr]+"    "\n\t"   \
      "out %[data]    , __tmp_reg__" "\n\t"   \
      "SBI 5 , 0"     "\n\t"   \
      "CBI 5 , 0"     "\n\t"

//Assembly cod for bit 3
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

#define copy_bitl "ld  r16, %a[ptr]" "\n\t"\
	"bst %[b] , %[bit] " "\n\t"\
	"bld r16 , 4 " "\n\t"\
	"bst %[g] , %[bit] " "\n\t"\
	"bld r16 , 3 " "\n\t"\
	"bst %[r] , %[bit] " "\n\t"\
	"bld r16 , 2 " "\n\t"\
	"st %a[ptr] , r16 \n\t"

#define copy_bith "ld  r16, %a[ptr]" "\n\t"\
	"bst %[b] , %[bit] " "\n\t"\
	"bld r16 , 7 " "\n\t"\
	"bst %[g] , %[bit] " "\n\t"\
	"bld r16 , 6 " "\n\t"\
	"bst %[r] , %[bit] " "\n\t"\
	"bld r16 , 5 " "\n\t"\
	"st %a[ptr] , r16 \n\t"

#define copy_bitl3 \
	"ld  r16, %a[ptr1] \n\t" \
	"bst %[b] , 3   \n\t" \
	"bld r16 , 0  \n\t" \
	"st %a[ptr1] , r16 \n\t" \
	"ld  r16, %a[ptr2]" "\n\t" \
	"bst %[g] , 3  \n\t" \
	"bld r16 , 1  \n\t" \
	"bst %[r] , 3  \n\t" \
	"bld r16 , 0  \n\t" \
	"st %a[ptr2] , r16 \n\t"

#define copy_bith3 \
	"ld  r16, %a[ptr] \n\t" \
	"bst %[b] , 3   \n\t" \
	"bld r16 , 1  \n\t" \
	"bst %[g] , 3  \n\t" \
	"bld r16 , 0  \n\t" \
	"st %a[ptr] , r16 \n\t" \
	"ld  r16, %a[ptr1]" "\n\t" \
	"bst %[r] , 3  \n\t" \
	"bld r16 , 1  \n\t" \
	"st %a[ptr1] , r16 \n\t"

//Assembly code to switch off all pixels
#define pew2 "out %[data]    , __tmp_reg__" "\n\t"   \
      "SBI 5 , 0"     "\n\t"   \
      "CBI 5 , 0"     "\n\t"

//#define push_bit0
class HUB75driver
{
public:
	HUB75driver();
	uint8_t init(boolean dbuf=false, boolean extra_dim=false);
	void updateDisplay();
	void drawPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
	void cleanScreen();
	void swapBuffers(boolean cp_old = false);
	void begin();
	void debug();

private:
	uint8_t         *matrixbuff[2],pwm_count_max;
	uint8_t use_dbuf,half_brightness,cp_back_to_front;
	volatile uint8_t pwm_count,line,display_buffer_index,draw_buffer_index,swap_needed;
	int buffsize;
	volatile uint8_t *buffptr, *img;
};

#endif

