#define __SFR_OFFSET 0          // Use 0 for the I/O register offset
#include <avr/io.h>

// code segment
.section .text

// export function
.global DisplayNeopixelA4


// neopixel LED WS2812B
// required 16 MHz clock
// updateadte for arudino nano pro
// switched PortC,PIN4 into PDO meaning PortD,PIN0

//T0H		0 code,high voltage time	0.4us±150ns
//T1H		1 code,high voltage time	0.8us±150ns
//T0L		0 code, low voltage time	0.85us±150ns
//T1L		1 code, low voltage time	0.45us±150ns
//RES		low voltage time			Above 50μs

// +------------+         T0L            |     0 code
// |   T0H      +------------------------+
//
// +---------------------+      T1L      |     1 code
// |         T1H         +---------------+
//
//  62.5 ns @ 16 MHz
//  T0H -   7 cycles * 62.5ns = 437.5ns
//  T0L -  14 cycles * 62.5ns = 875.0ns
//
//  T1H -  13 cycles * 62.5ns = 812.5ns
//  T1L -   7 cycles * 62.5ns = 437.5ns
//  


#define param R18
#define param1 R19
#define param2 R22

#define PortD 0x0B

/*
Add to C or CPP file:

// numer of LEDs
#define NEOPIXEL_LEDS  23

extern void DisplayNeopixel(char * pBuf, unsigned char ucCounter);

struct {
	uint8_t g;
	uint8_t r;
	uint8_t b;	
	} LedBuf[NEOPIXEL_LEDS];

*/

// param - data
// param1 - bit counter
// param2 - byte counter (size of data buffer)
// Z - pointer to data buffer. Organization data in buffer:  3 Bytes per 1 LED  gggggggg rrrrrrrr bbbbbbbb

// C/C++ code
// void DisplayNeopixel(char * pBuf, unsigned char ucCounter);
// pBuf stored in R25:R24
// ucCounter stored in R23:R22, in this key R22 - number of LED.

DisplayNeopixelA4:

	mov		ZL, R24
	mov		ZH, R25
	
	mov		R23,param2
	add		R23,param2	// *2
	add		R23,param2	// *3
	mov		param2,R23

	cli					// disable interrupts

	ld		param,Z+	// get first Byte
	ldi		param1,8	// always 8 bit per Byte
//	ldi		param2,24	// 24 Bytes / 3 = 8 neopixel LEDs

LoopByteDelay:			//			|	|	|	4	|	|	11
	nop					// 1 cycle	|	|	|	5	|	|	12	
	nop					// 1 cycle	|	|	|	6	|	|	13		
LoopByte:				//			|	|	|	|	6	13	|
	sbi		PortD,PIN0	// 2 cycles	0	0	0	8	8	15	15			Begin of TxH
	rol		param		// 1 cycle	1	1	1	|	|	|	|			Bit to Carry flag
	dec		param1		// 1 cycle	2	2	2	|	|	|	|			Decrement bit counter. Zero flag set or cleared for this bit loop. dec instruction does not change Carry flag
	brcc	EndTH		// 1/2		|	|	|	|	|	|	|			Jump if 0 code
	// T1H				//			3	3	|	|	|	|	|			
	brne	DelayT1H	// 1/2		|	|	|	|	|	|	|			Jump if T1H without loading byte
						//			4	|	|	|	|	|	|	
	rjmp	Del1		// 2 cycles	6	|	|	|	|	|	|	
Del1:
	rjmp	Del2		// 2 cycles	8	|	|	|	|	|	|	
Del2:
	ld		param,Z+	// 2 cycles	10	|	|	|	|	|	|	
	ldi		param1,8	// 1 cycle	11	|	|	|	|	|	|	
EndTH:					//			|	10	4	|	|	|	|
	nop					// 1 cycle	|	11	5	|	|	|	|		
	cbi		PortD,PIN0	// 2 cycles	13	13	7	0	0	0	0			End of TxH, begin TxL
	brcs	EndTL		// 1/2		|	|	|	|	|	|	|			Jump if 1 code
	// T0L				//			|	|	|	|	|	1	|
	brne    DelayT0L	// 1/2		|	|	|	|	|	|	|	
						//  		|	|	|	|	|	2	|
	rjmp	Del3		// 2 cycles	|	|	|	|	|	4	|	
Del3:
	rjmp	Del4		// 2 cycles	|	|	|	|	|	6	|							
Del4:
	ld		param,Z+	// 2 cycles	|	|	|	|	|	8	|
	ldi		param1,8	// 1 cycle	|	|	|	|	|	9	|
EndTL:					//			|	|	|	2	2	|	9		
	brne	LoopByteDelay// 1/2		|	|	|	|	|	|	|		
						//  		|	|	|	|	3	10	|	
	dec		param2		// 1 cycle	|	|	|	|	4	11	|			Decrement Byte counter	
	brne 	LoopByte	// 2 cycles	|	|	|	|	|	|	|	
	rjmp	PacketEnd	//			|	|	|	|	|	|	|
						//			|	|	|	|	|	|	|
DelayT1H:				//			|	5	|	|	|	|	|			Delay for T1H without loading Byte
	rjmp	Del5		// 2 cycles	|	7	|	|	|	|	|
Del5:
	nop					// 1 cycle	|	8	|	|	|	|	|		
	rjmp	EndTH		// 2 cycles	|	|	|	|	|	|	|
						//			|	|	|	|	|	|	|	
DelayT0L:				//			|	|	|	|	|	|	2			Delay for T0L without loading Byte
	rjmp	Del6		// 2 cycles	|	|	|	|	|	|	4
Del6:
	rjmp	Del7		// 2 cycles	|	|	|	|	|	|	6	
Del7:
	nop					// 1 cycle	|	|	|	|	|	|	7
	rjmp	EndTL		// 2 cycles	|	|	|	|	|	|	|
						//			|	|	|	|	|	|	|		
						//			|	|	|	|	|	|	T0L without loading next byte
						//			|	|	|	|	|	T0L with loading next byte
						//			|	|	|	|	T1L without loading next byte
						//			|	|	|	T1L with loading next byte
						//			|	|	T0H
						//			|	T1H without loading next byte
						//			T1H with loading next byte
	
PacketEnd:
	
	sei					// enable interrupts
	
	ret
	
	
	

	
	
	