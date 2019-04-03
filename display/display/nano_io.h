#ifndef _NANO_IO_H_
#define _NANO_IO_H_

#include <avr/sfr_defs.h>
#include <avr/io.h>


/*
	NANO	ATMGEAGA328
	D0			PD0
	D1			PD1
	D2			PD2
	D3			PD3
	D5			PD5
	D5			PD5
	D6			PD6
	D7			PD7
	D8			PB0
	D9			PB1
	D10			PB2
	D11			PB3
	D12			PB5
	D13			PB5
	
	A0			PC0
	A1			PC1
	A2			PC2
	A3			PC3
	A5			PC5
	A5			PC5
	A6			PC6	- analog only
	A7			PC7 - analog only
	

Addr    Name     Bit7   Bit6   Bit5   Bit4   Bit3   Bit2   Bit1   Bit0
...
0x03   PINB     PINB7  PINB6  PINB5  PINB4  PINB3  PINB2  PINB1  PINB0
0x04   DDRB     DDB7   DDB6   DDB5   DDB4   DDB3   DDB2   DDB1   DDB0
0x05   PORTB    PORTB7 PORTB6 PORTB5 PORTB4 PORTB3 PORTB2 PORTB1 PORTB0
0x06   PINC     x      PINC6  PINC5  PINC4  PINC3  PINC2  PINC1  PINC0
0x07   DDRC     x      DDC6   DDC5   DDC4   DDC3   DDC2   DDC1   DDC0
0x08   PORTC    x      PORTC6 PORTC5 PORTC4 PORTC3 PORTC2 PORTC1 PORTC0
0x09   PIND     PIND7  PIND6  PIND5  PIND4  PIND3  PIND2  PIND1  PIND0
0x0A   DDRD     DDD7   DDD6   DDD5   DDD4   DDD3   DDD2   DDD1   DDD0
0x0B   PORTD    PORTD7 PORTD6 PORTD5 PORTD4 PORTD3 PORTD2 PORTD1 PORTD0	
	
*/

// PD0
//#define clrD0()  __asm__ __volatile__ ("cbi  PORTD,PD0")
//#define setD0()  __asm__ __volatile__ ("sbi  PORTD,PD0")
//#define setD0()  __asm__ __volatile__ ("sbi  %0, x00" : : "I" (_SFR_IO_ADDR(PORTD)))
#define clrD0()  __asm__ __volatile__ ("cbi  0x0B,0x00")								// set D0 pin
#define setD0()  __asm__ __volatile__ ("sbi  0x0B,0x00")								// clear D0 pin
#define D0output()     __asm__ __volatile__ ("sbi  0x0A,0x00")							// set D0 pin as output. DDRD = 1
#define D0input()      __asm__ __volatile__ ("cbi  0x0A,0x00" "\n\t" "cbi  0x0B,0x00" )	// set D0 pin as input without pull up. DDRD = 0 PORTD = 0
#define D0inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x00" "\n\t" "sbi  0x0B,0x00")	// set D0 pin as input with pull up. DDRD = 1 PORTD = 1
// PD1
#define clrD1()  __asm__ __volatile__ ("cbi  0x0B,0x01")
#define setD1()  __asm__ __volatile__ ("sbi  0x0B,0x01")
#define D1output()     __asm__ __volatile__ ("sbi  0x0A,0x01")	// DDRD = 1
#define D1input()      __asm__ __volatile__ ("cbi  0x0A,0x01" "\n\t" "cbi  0x0B,0x01" )	// DDRD = 0 PORTD = 0
#define D1inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x01" "\n\t" "sbi  0x0B,0x01")	// DDRD = 1 PORTD = 1
// PD2
#define clrD2()  __asm__ __volatile__ ("cbi  0x0B,0x02")
#define setD2()  __asm__ __volatile__ ("sbi  0x0B,0x02")
#define D2output()     __asm__ __volatile__ ("sbi  0x0A,0x02")	// DDRD = 1
#define D2input()      __asm__ __volatile__ ("cbi  0x0A,0x02" "\n\t" "cbi  0x0B,0x02" )	// DDRD = 0 PORTD = 0
#define D2inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x02" "\n\t" "sbi  0x0B,0x02")	// DDRD = 1 PORTD = 1
// PD3
#define clrD3()  __asm__ __volatile__ ("cbi  0x0B,0x03")
#define setD3()  __asm__ __volatile__ ("sbi  0x0B,0x03")
#define D3out()        __asm__ __volatile__ ("sbi  0x0A,0x03")	// DDRD = 1
#define D3input()      __asm__ __volatile__ ("cbi  0x0A,0x03" "\n\t" "cbi  0x0B,0x03" )	// DDRD = 0 PORTD = 0
#define D3inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x03" "\n\t" "sbi  0x0B,0x03")	// DDRD = 1 PORTD = 1
// PD4
#define clrD4()  __asm__ __volatile__ ("cbi  0x0B,0x04")
#define setD4()  __asm__ __volatile__ ("sbi  0x0B,0x04")
#define D4output()     __asm__ __volatile__ ("sbi  0x0A,0x04")	// DDRD = 1
#define D4input()      __asm__ __volatile__ ("cbi  0x0A,0x04" "\n\t" "cbi  0x0B,0x04" )	// DDRD = 0 PORTD = 0
#define D4inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x04" "\n\t" "sbi  0x0B,0x04")	// DDRD = 1 PORTD = 1
// PD5
#define clrD5()  __asm__ __volatile__ ("cbi  0x0B,0x05")
#define setD5()  __asm__ __volatile__ ("sbi  0x0B,0x05")
#define D5output()        __asm__ __volatile__ ("sbi  0x0A,0x05")	// DDRD = 1
#define D5input()      __asm__ __volatile__ ("cbi  0x0A,0x05" "\n\t" "cbi  0x0B,0x05" )	// DDRD = 0 PORTD = 0
#define D5inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x05" "\n\t" "sbi  0x0B,0x05")	// DDRD = 1 PORTD = 1
// PD6
#define clrD6()  __asm__ __volatile__ ("cbi  0x0B,0x06")
#define setD6()  __asm__ __volatile__ ("sbi  0x0B,0x06")
#define D6output()     __asm__ __volatile__ ("sbi  0x0A,0x06")	// DDRD = 1
#define D6input()      __asm__ __volatile__ ("cbi  0x0A,0x06" "\n\t" "cbi  0x0B,0x06" )	// DDRD = 0 PORTD = 0
#define D6inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x06" "\n\t" "sbi  0x0B,0x06")	// DDRD = 1 PORTD = 1
// PD7
#define clrD7()  __asm__ __volatile__ ("cbi  0x0B,0x07")
#define setD7()  __asm__ __volatile__ ("sbi  0x0B,0x07")
#define D7output()        __asm__ __volatile__ ("sbi  0x0A,0x07")	// DDRD = 1
#define D7input()      __asm__ __volatile__ ("cbi  0x0A,0x07" "\n\t" "cbi  0x0B,0x07" )	// DDRD = 0 PORTD = 0
#define D7inputpull()  __asm__ __volatile__ ("cbi  0x0A,0x07" "\n\t" "sbi  0x0B,0x07")	// DDRD = 1 PORTD = 1

// PB0
#define clrD8()  __asm__ __volatile__ ("cbi  0x05,0x00")
#define setD8()  __asm__ __volatile__ ("sbi  0x05,0x00")
#define D8output()     __asm__ __volatile__ ("sbi  0x04,0x00")							// set D8 pin as output. DDRB = 1
#define D8input()      __asm__ __volatile__ ("cbi  0x04,0x00" "\n\t" "cbi  0x05,0x00" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D8inputpull()  __asm__ __volatile__ ("cbi  0x04,0x00" "\n\t" "sbi  0x05,0x00")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1
// PB1
#define clrD9()  __asm__ __volatile__ ("cbi  0x05,0x01")
#define setD9()  __asm__ __volatile__ ("sbi  0x05,0x01")
#define D9output()     __asm__ __volatile__ ("sbi  0x04,0x01")							// set D8 pin as output. DDRB = 1
#define D9input()      __asm__ __volatile__ ("cbi  0x04,0x01" "\n\t" "cbi  0x05,0x01" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D9inputpull()  __asm__ __volatile__ ("cbi  0x04,0x01" "\n\t" "sbi  0x05,0x01")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1
// PB2
#define clrD10() __asm__ __volatile__ ("cbi  0x05,0x02")
#define setD10() __asm__ __volatile__ ("sbi  0x05,0x02")
#define D10output()    __asm__ __volatile__ ("sbi  0x04,0x02")							// set D8 pin as output. DDRB = 1
#define D10input()     __asm__ __volatile__ ("cbi  0x04,0x02" "\n\t" "cbi  0x05,0x02" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D10inputpull() __asm__ __volatile__ ("cbi  0x04,0x02" "\n\t" "sbi  0x05,0x02")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1
// PB3
#define clrD11() __asm__ __volatile__ ("cbi  0x05,0x03")
#define setD11() __asm__ __volatile__ ("sbi  0x05,0x03")
#define D11output()    __asm__ __volatile__ ("sbi  0x04,0x03")							// set D8 pin as output. DDRB = 1
#define D11input()     __asm__ __volatile__ ("cbi  0x04,0x03" "\n\t" "cbi  0x05,0x03" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D11inputpull() __asm__ __volatile__ ("cbi  0x04,0x03" "\n\t" "sbi  0x05,0x03")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1
// PB4
#define clrD12() __asm__ __volatile__ ("cbi  0x05,0x04")
#define setD12() __asm__ __volatile__ ("sbi  0x05,0x04")
#define D12output()    __asm__ __volatile__ ("sbi  0x04,0x04")							// set D8 pin as output. DDRB = 1
#define D12input()     __asm__ __volatile__ ("cbi  0x04,0x04" "\n\t" "cbi  0x05,0x04" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D12inputpull() __asm__ __volatile__ ("cbi  0x04,0x04" "\n\t" "sbi  0x05,0x04")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1
// PB5 and L pin arduino build in led;
#define clrD13() __asm__ __volatile__ ("cbi  0x05,0x05")
#define setD13() __asm__ __volatile__ ("sbi  0x05,0x05")
#define D13output()    __asm__ __volatile__ ("sbi  0x04,0x05")							// set D8 pin as output. DDRB = 1
#define D13input()     __asm__ __volatile__ ("cbi  0x04,0x05" "\n\t" "cbi  0x05,0x05" )	// set D8 pin as input without pull up. DDRB = 0 PORTB = 0
#define D13inputpull() __asm__ __volatile__ ("cbi  0x04,0x05" "\n\t" "sbi  0x05,0x05")	// set D8 pin as input with pull up. DDRB = 1 PORTB = 1

// PC0
#define clrA0()  __asm__ __volatile__ ("cbi  0x08,0x00")
#define setA0()  __asm__ __volatile__ ("sbi  0x08,0x00")
#define A0output()     __asm__ __volatile__ ("sbi  0x07,0x00")							// set A0 pin as output. DDRC = 1
#define A0input()      __asm__ __volatile__ ("cbi  0x07,0x00" "\n\t" "cbi  0x08,0x00" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A0inputpull()  __asm__ __volatile__ ("cbi  0x07,0x00" "\n\t" "sbi  0x08,0x00")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1
// PC1
#define clrA1()  __asm__ __volatile__ ("cbi  0x08,0x01")
#define setA1()  __asm__ __volatile__ ("sbi  0x08,0x01")
#define A1output()     __asm__ __volatile__ ("sbi  0x07,0x01")							// set A0 pin as output. DDRC = 1
#define A1input()      __asm__ __volatile__ ("cbi  0x07,0x01" "\n\t" "cbi  0x08,0x01" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A1inputpull()  __asm__ __volatile__ ("cbi  0x07,0x01" "\n\t" "sbi  0x08,0x01")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1
// PC2
#define clrA2()  __asm__ __volatile__ ("cbi  0x08,0x02")
#define setA2()  __asm__ __volatile__ ("sbi  0x08,0x02")
#define A2output()     __asm__ __volatile__ ("sbi  0x07,0x02")							// set A0 pin as output. DDRC = 1
#define A2input()      __asm__ __volatile__ ("cbi  0x07,0x02" "\n\t" "cbi  0x08,0x02" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A2inputpull()  __asm__ __volatile__ ("cbi  0x07,0x02" "\n\t" "sbi  0x08,0x02")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1
// PC3
#define clrA3()  __asm__ __volatile__ ("cbi  0x08,0x03")
#define setA3()  __asm__ __volatile__ ("sbi  0x08,0x03")
#define A3output()     __asm__ __volatile__ ("sbi  0x07,0x03")							// set A0 pin as output. DDRC = 1
#define A3input()      __asm__ __volatile__ ("cbi  0x07,0x03" "\n\t" "cbi  0x08,0x03" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A3inputpull()  __asm__ __volatile__ ("cbi  0x07,0x03" "\n\t" "sbi  0x08,0x03")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1
// PC4
#define clrA4()  __asm__ __volatile__ ("cbi  0x08,0x04")
#define setA4()  __asm__ __volatile__ ("sbi  0x08,0x04")
#define A4output()     __asm__ __volatile__ ("sbi  0x07,0x04")							// set A0 pin as output. DDRC = 1
#define A4input()      __asm__ __volatile__ ("cbi  0x07,0x04" "\n\t" "cbi  0x08,0x04" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A4inputpull()  __asm__ __volatile__ ("cbi  0x07,0x04" "\n\t" "sbi  0x08,0x04")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1
// PC5
#define clrA5()  __asm__ __volatile__ ("cbi  0x08,0x05")
#define setA5()  __asm__ __volatile__ ("sbi  0x08,0x05")
#define A5output()     __asm__ __volatile__ ("sbi  0x07,0x05")							// set A0 pin as output. DDRC = 1
#define A5input()      __asm__ __volatile__ ("cbi  0x07,0x05" "\n\t" "cbi  0x08,0x05" )	// set A0 pin as input without pull up. DDRC = 0 PORTC = 0
#define A5inputpull()  __asm__ __volatile__ ("cbi  0x07,0x05" "\n\t" "sbi  0x08,0x05")	// set A0 pin as input with pull up. DDRC = 1 PORTC = 1





//#define loop_until_bit_is_clear_(port,bit) \ __asm__ __volatile__ ( \ "L_%=: " "sbic %0, %1" "\n\t" \ "rjmp L_%=" \ : /* no outputs */ : "I" (_SFR_IO_ADDR(port)), "I" (bit) )
//When used for the first time, L_= may be translated to L_1505, the next usage might create L_1505 or whatever. In any case, the labels became unique too.
//Another option is to use Unix-assembler style numeric labels. They are explained in How do I trace an assembler file in avr-gdb?. The above example would then look like:
//#define loop_until_bit_is_clear(port,bit) __asm__ __volatile__ ( "1: " "sbic %0, %1" "\n\t" "rjmp 1b" : /* no outputs */ : "I" (_SFR_IO_ADDR(port)), "I" (bit) ) 




#endif //_NANO_IO_H_