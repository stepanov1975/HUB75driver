#ifndef FONTBIG_H_INCLUDED
#define FONTBIG_H_INCLUDED




/***********************************************************************
 * fontBig.h - digits defined in 6x12 grid;
 *           - used for displaying the time on 24x16 display of Wise Clock 2;
 * Copyright Aug 1/2010, by FlorinC;
 *   Copyrighted and distributed under the terms of the Berkeley license
 *   (copy freely, but include this notice of original author.)
 ***********************************************************************
 */


//*********************************************************************************************************
//*	Edit History, started April, 2010
//*	please put your initials and comments here anytime you make changes
//*********************************************************************************************************
//* Oct 10/10 (rp) added blank at pos. 10 and more fonts
//*	Jun 20/11 (rp) Changed inverse Space Character from 0x01 to 0x3f, corrected 0 in Font 9, changed 1 in Font 6
//* Oct 15/11 (rp) Changed Font 7 into column font;
//*
//* Feb 3
//*********************************************************************************************************


// There are 9 BIG Fonts, with 11 characters each, one character is 12 bytes long
// define big digits 0-9 and space character;
// The fourth font must be the inverse one, see displayBigTime() in WiseClock2.cpp

const unsigned char PROGMEM bigFont[55][12] = {		// 11 characters of 12 bytes (rows) each;

// Font 0

   {
    0x0E,    // __XXX_  	0
    0x1F,    // _XXXXX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },

  {
    0x06,    // ___XX_		1
    0x0E,    // __XXX_
    0x1E,    // _XXXX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1E,    // _XXXX_  	2
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x06,    // ___XX_
    0x0C,    // __XX__
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1E,    // _XXXX_  	3
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x0E,    // __XXX_
    0x0E,    // __XXX_
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1E     // _XXXX_
  },
  {
    0x18,    // _XX___  	4
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03     // ____XX
  },
  {
    0x1F,    // _XXXXX  	5
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1E,    // _XXXX_
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1E     // _XXXX_
  },
  {
    0x0E,    // __XXX_  	6
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1E,    // _XXXX_
    0x1F,    // _XXXXX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x1F,    // _XXXXX
    0x0E    // ___XXX_
  },
  {
    0x1F,    // _XXXXX  	7
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x06,    // ___XX_
    0x0C,    // __XX__
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x18     // _XX___
  },
  {
    0x0E,    // __XXX_  	8
    0x1F,    // _XXXXX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x0E,    // __XXX_
    0x0E,    // __XXX_
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	9
    0x1F,    // _XXXXX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x13,    // _X__XX
    0x1F,    // _XXXXX
    0x0F,    // __XXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // ____XX
    0x0E     // _XXXX_
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
  },

// Font 1

  {
    0x1F,    // _XXXXX  	0
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },

  {
    0x0C,    // __XX__		1
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x0C     // __XX__
  },

  {
    0x1F,    // _XXXXX  	2
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	3
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1B,    // _XX_XX  	4
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_xx
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03     // ____XX
  },
  {
    0x1F,    // _XXXXX  	5
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	6
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1F,    // _XXXXx
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _Xx_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F    // __XXXXX
  },
  {
    0x1F,    // _XXXXX  	7
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03     // ____XX
  },
  {
    0x1F,    // _XXXXX  	8
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	9
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
  },

// Font 2

  {
    0x0E,    // __XXX_  	0
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },

  {
    0x02,    // ____X_		1
    0x06,    // ___XX_
    0x0E,    // __XXX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },

  {
    0x0E,    // __XXX_  	2
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x06,    // ___XX_
    0x0C,    // __XX__
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1F,    // _XXXXX
    0x1F     // _XXXXX
  },
  {
    0x0E,    // __XXX_  	3
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x0E,    // __XXX_
    0x0E,    // __XXX_
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },
  {
    0x03,    // ____XX		4
    0x03,    // ____XX
    0x06,    // ___XX_
    0x06,    // ___XX_
    0x0C,    // __XX__
    0x0C,    // __XX__
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03     // ____XX
   },
  {
    0x1F,    // _XXXXX  	5
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1E,    // _XXXX_
    0x0F,    // __XXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	6
    0x1F,    // _XXXXX
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x1E,    // _XXXX_
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x0E    // ___XXX_
  },
  {
    0x1F,    // _XXXXX  	7
    0x1F,    // _XXXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x06,    // ___XX_
    0x0C,    // __XX__
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x18,    // _XX___
    0x18     // _XX___
  },
  {
    0x0E,    // __XXX_  	8
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x0E,    // __XXX_
    0x0E,    // __XXX_
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	9
    0x1F,    // _XXXXX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1B,    // _XX_XX
    0x1F,    // _XXXXX
    0x0F,    // __XXXX
    0x03,    // ____XX
    0x03,    // ____XX
    0x03,    // ____XX
    0x1F,    // _XXXXX
    0x0E     // __XXX_
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
  },

// Font 3

  {
    0x1F,    // _XXXXX  	0
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F     // _XXXXX
  },

  {
    0x04,    // ___X__		1
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04     // ___X__
  },

  {
    0x1F,    // _XXXXX  	2
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x1F,    // _XXXXX
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	3
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x1F     // _XXXXX
  },
  {
    0x11,    // _X___X  	4
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01     // _____X
  },
  {
    0x1F,    // _XXXXX  	5
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	6
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1F,    // _XXXXX
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F    // __XXXXX
  },
  {
    0x1F,    // _XXXXX  	7
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01     // _____X
  },
  {
    0x1F,    // _XXXXX  	8
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F,    // _XXXXX
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F     // _XXXXX
  },
  {
    0x1F,    // _XXXXX  	9
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x1F     // _XXXXX
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
  },

// Font 4

  {
    0x0E,    // __XXX_  	0
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E     // __XXX_
  },

  {
    0x04,    // ___X__		1
    0x0C,    // __XX__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x1F     // _XXXXX
  },

  {
    0x0E,    // __XXX_  	2
    0x11,    // _X___X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x02,    // ____X_
    0x04,    // ___X__
    0x08,    // __X___
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1F     // _XXXXX
  },
  {
    0x0E,    // __XXX_  	3
    0x11,    // _X___X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x0E,    // __XXX_
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x11,    // _X___X 	4
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01     // _____X
  },
  {
    0x1F,    // _XXXXX  	5
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1E,    // _XXXX_
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	6
    0x11,    // _X___X
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1E,    // _XXXX_
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E    // ___XXX_
  },
  {
    0x1F,    // _XXXXX  	7
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x02,    // ____X_
    0x04,    // ___X__
    0x08,    // __X___
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10     // _X____
  },
  {
    0x0E,    // __XXX_  	8
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E,    // __XXX_
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	9
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0F,    // __XXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
    0x00,    // ______
  },



};

// There are 5 BIG Fonts, with 11 characters each, one character is 12 bytes long
//#define  NUMBER_OF_FONTS  9
//#define  CHARS_IN_FONT   11  //  0 - 9 + Space
//#define  BYTES_PER_CHARS 12
#endif // FONTBIG_H_INCLUDED

