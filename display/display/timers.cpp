/*
 * timer.cpp
 *
 * Created: 01.12.2018 19:45:04
 *  Author: MarcinS
 */ 
#include "timers.h"


inline uint8_t fTimerFlag()
{
	if(TIFR1 & (1<<ICF1))
	{
		TIFR1= 1<<ICF1;
		return 1;
	}
	return 0;
} 



void timer1init()
{
	/*
	| timer set to CTC, NO interrupts, intended setting flag with a secound of delay
	*/
	TCCR1A =  TCCR1A &(( 0xFF ^ (1<<WGM11)) ^ (1<<WGM10) );
	TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM13) | (1<<WGM12) ;
	TCCR1B = TCCR1B & ( (0xFF ^ (1<<CS11)) );
	TCNT1 =0;
	ICR1=F_CPU/1024; // 	
}

void timer2init()
{
	TCCR2A = (1<<WGM21);
	//TCCR2B = (1<<CS22);
	TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);// TEST
	TCNT2=0;
	OCR2A=TO_COUNT_FOR_TIMER_2; // 15*120*64 =115 200
	TIMSK2 |= 1<<OCIE2A;
}

inline void setTimer2Zero()
{
	TCNT2=0;
}

// TIMER2 INTERRUPT
inline void displayInterruptProd()
{
	fDisplayed=true;
	display.Display();	
}

ISR(TIMER2_COMPA_vect)
{
	displayInterruptProd();
}
