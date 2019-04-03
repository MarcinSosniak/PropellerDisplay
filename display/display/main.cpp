/*
 * display.cpp
 *
 * Created: 01.12.2018 13:40:07
 * Author : MarcinS Marek Fudalinski
 */ 


//#define DEBUG_IO 1;

#include <avr/io.h>
#include <avr/interrupt.h>
#include "CDiagNeopixel.h"
#include "F_CPU.h"
#include "nano_io.h"

//#include "lines.h"


#define FRAMERATE 15
#define LINES_PER_FRAME 120
#define TO_COUNT_FOR_TIMER_2 138


void createLines();
inline void displayInterruptProd();

/*NIDDLES*/
#define SECOND_SIZE 9
#define SECOND_RED 255
#define SECOND_GREEN 0
#define SECOND_BLUE 0

#define MINUTE_SIZE 7
#define MINUTE_RED 0
#define MINUTE_GREEN 255
#define MINUTE_BLUE 0

#define HOUR_SIZE 5
#define HOUR_RED 0
#define HOUR_GREEN 0
#define HOUR_BLUE 255

/*Background */
#define BACKGROUND_RED 0
#define BACKGROUND_GREEN 0
#define BACKGROUND_BLUE 0

/*Dots */
#define DOT_RED 255
#define DOT_GREEN 255
#define DOT_BLUE 255

/*No Niddle frames */
uint8_t NoNiddleOneDot[3*NUMBER_OF_DIAG_LEDS];
uint8_t NoNiddleTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t NoNiddleThreeDots[3*NUMBER_OF_DIAG_LEDS];
/*No covering */
/*Only Second Frames */
uint8_t OnylSecondsOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t OnylSecondsOnThreeDots[3*NUMBER_OF_DIAG_LEDS];

/*Only Minutes Frames*/
uint8_t OnylMinuteOnOneDot[3*NUMBER_OF_DIAG_LEDS];
uint8_t OnylMinuteOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t OnylMinuteOnThreeDots[3*NUMBER_OF_DIAG_LEDS];

/*Only Houres Frames*/
uint8_t OnylHoureOnOneDot[3*NUMBER_OF_DIAG_LEDS];
uint8_t OnylHoureOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t OnylHoureOnThreeDots[3*NUMBER_OF_DIAG_LEDS];
/*Covering */
/*Houre with minute */
uint8_t HoureAndMinutesOnOneDot[3*NUMBER_OF_DIAG_LEDS];
uint8_t HoureAndMinutesOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t HoureAndMinutesOnThreeDots[3*NUMBER_OF_DIAG_LEDS];
/*Houre with second */
uint8_t HouresAndSecondsOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t HouresAndSecondsOnThreeDots[3*NUMBER_OF_DIAG_LEDS];
/*Minute with second */
uint8_t MinuteAndSecondsOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t MinuteAndSecondsOnThreeDots[3*NUMBER_OF_DIAG_LEDS];

/*Minute houre and second together */
uint8_t HoureMinuteSecondOnTwoDots[3*NUMBER_OF_DIAG_LEDS];
uint8_t  HoureMinuteSecondOnThreeDots[3*NUMBER_OF_DIAG_LEDS];

/* The buffer that points which frame we need to to display */
uint8_t TestWhiteLine[3*12];

volatile uint8_t fDisplayed=false;
CDiagNeopixel display;
uint8_t debugState=0;
uint8_t outTable[3*NUMBER_OF_DIAG_LEDS];

/* Niddles position are between 0 and 119 */
volatile uint8_t ready=0;
uint8_t hour=10;
uint8_t hour_pos;
uint8_t minutes=20;
uint8_t min_pos;
uint8_t seconds=00;//seconds_pos is 2*seconds;
uint8_t position=0;
/* Needed to calculate which position on the frame is calculated */
uint8_t exactMinute = 0;
uint8_t exactOneDot = 0;


/*
Timer varaibale
*/
volatile uint8_t   secondTimerCounter=0;
volatile uint8_t secondTimerFlag=0;

/*
GLOBUL 
*/


/* Timer functions */
inline uint8_t fSecondTimerFlag()
{
	if(secondTimerFlag)
	{
		secondTimerFlag=0;
		return 1;
	}
	return 0;
} 

inline void initPosControl()
{
	clrD1();
	D1inputpull();
	//D1input();
}
inline uint8_t readPosControl()
{
	return PIND & (1<<PIND1);
}

 inline void timerSecondInit()
{
	/*
	| timer set to CTC, NO interrupts, intended setting flag with a secound of delay
	*/
	TCCR2A = (1<<WGM21);
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	TCNT2=0;
	OCR2A=125;
	TIMSK2 |= 1<<OCIE2A;
	
	
	/* old timer
	TCCR1A =  TCCR1A &(( 0xFF ^ (1<<WGM11)) ^ (1<<WGM10) );
	TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM13) | (1<<WGM12) ;
	TCCR1B = TCCR1B & ( (0xFF ^ (1<<CS11)) );
	TCNT1 =0;
	ICR1=F_CPU/1024; //
	*/ 	
}

ISR(TIMER2_COMPA_vect)
{
	secondTimerCounter++;
	if(secondTimerCounter==125)
	{
		secondTimerCounter=0;
		secondTimerFlag=1;
	}
}	

inline void timerDisplayInit()
{
	TCCR1A = 0;
	TCCR1B = (1<<CS10) | (1<<WGM13) | (1<<WGM12) ;
	TCNT1 =0;
	//ICR1=8885; //
	ICR1=8888; // TEST
	TIMSK1 |= 1<<OCIE1A;
	/* old timer
	TCCR2A = (1<<WGM21);
	TCCR2B = (1<<CS22);
	TCNT2=0;
	OCR2A=138;
	TIMSK2 |= 1<<OCIE2A;
	*/
}
ISR(TIMER1_COMPA_vect)
{
	if(ready)
		displayInterruptProd();
}

inline void resetDisplayTimer()
{
	TCNT1=0;
}
/* display timer  INTERRUPT */
inline void displayInterruptProd()
{
	fDisplayed=true;
	display.Display();	
}

inline void waitAWhile()
{
	ready=1;
	while(!fSecondTimerFlag())
		;
	while(!fSecondTimerFlag())
		;
	ready=0;
}



/*Initializing timers and displaying table */
inline void init()
{
	#ifdef DEBUG_IO
	D13output();
	#endif
	createLines();
	timerSecondInit();
	timerDisplayInit();
	initPosControl();
	sei();
	uint8_t i=0;
	for(;i<3*NUMBER_OF_DIAG_LEDS;i++)
	{
		outTable[i]=10;
	}
	display.SetLedRGBfromTable(outTable);
	waitAWhile();
	
	for(;i<3*NUMBER_OF_DIAG_LEDS;i++)
	{
		outTable[i]=0;
	}
	display.SetLedRGBfromTable(outTable);
	
}


void debugRainbow()
{
	volatile uint8_t r=outTable[0];
	volatile uint8_t g=outTable[1];
	volatile uint8_t b=outTable[2];
	volatile uint8_t tmp;
	volatile uint8_t i;
	for(i=1;i<NUMBER_OF_DIAG_LEDS;i++)
	{
		tmp=outTable[3*i+0];
		outTable[3*i+0]=r;
		r=tmp;
		
		tmp=outTable[3*i+1];
		outTable[3*i+1]=g;
		g=tmp;
		
		tmp=outTable[3*i+2];
		outTable[3*i+2]=b;
		b=tmp;
	}
	outTable[0]=r;
	outTable[1]=g;
	outTable[2]=b;
	display.SetLedRGBfromTable(outTable);
}

void debugShowFirst()
{
	for(uint8_t i=3;i<3*NUMBER_OF_DIAG_LEDS;i++)
	{
		outTable[i]=0;
	}	
	display.SetLedRGBfromTable(outTable);
	display.Display();
}

/*
 *This is needed to synchronize displaing clock 
 *with a top of the clock.
 *The engin RPM MUST be slightly slower than 
 *assumed RPM's in main program.
 */
inline bool fSynchr()
{
	return true;
}

/* 
 *It calculate current niddle positions
*/
inline void calculateHands()
{
	int_fast8_t tmp=minutes;
	hour_pos=hour*10; 
	while(tmp>=6)	
	{
		hour_pos++;
		tmp-=6;
	}
	min_pos=2*minutes;
	if(seconds>=30)
		min_pos++;
}
inline void addSecond()
{
	if(seconds==59){
		seconds=0;
		if(minutes==59)
		{
			minutes=0;
			if(hour==11)
				hour=0;
			else
				hour++;
		}
		else
			minutes++;
	}
	else
		seconds++;
}


/* The function choose which line to display
 * on the given position
 * using global variables:
 * 		.niddlePosition's
 * we start displaying from 12
*/
inline uint8_t* calculateLine(){
	/* First we need to chose if we need to display one,two or three dotted clock's frame */
	if(exactOneDot == 0){//sprawdzamy dalej
		if(exactMinute == 0){//we display on three dots
			if(hour_pos == position){
				if(min_pos == position){
					if(seconds*2 == position){
						return HoureMinuteSecondOnThreeDots;
					}
					return HoureAndMinutesOnThreeDots;
				}
				if(seconds*2 == position){
					return HouresAndSecondsOnThreeDots;
				}
				return OnylHoureOnThreeDots;
			}else{
				if(min_pos == position){
					if(seconds*2 == position){
						return MinuteAndSecondsOnThreeDots;
					}
					return OnylMinuteOnThreeDots;
				}
				if(seconds*2 == position){
					return OnylSecondsOnThreeDots;
				}
				return NoNiddleThreeDots;
			}
		}else{//we display on 2 dots
			if(hour_pos == position){
				if(min_pos == position){
					if(seconds*2 == position){
						return HoureMinuteSecondOnTwoDots;
					}
					return HoureAndMinutesOnTwoDots;
				}
				if(seconds*2 == position){
					return HouresAndSecondsOnTwoDots;
				}
				return  OnylHoureOnTwoDots;
			}else{
				if(min_pos == position){
					if(seconds*2 == position){
						return MinuteAndSecondsOnTwoDots;
					}
					return OnylMinuteOnTwoDots;
				}
				if(seconds*2 == position){
					return OnylSecondsOnTwoDots;
				}
				return NoNiddleTwoDots;
			}
		}
	}else{//we display on one dot
		if(min_pos == position){
			if(hour_pos == position){
				return HoureAndMinutesOnOneDot;
			}
			return OnylMinuteOnOneDot;
		}
		if(hour_pos == position){
			return OnylHoureOnOneDot;
		}
		return NoNiddleOneDot;
	}
}

/* Acktualizing position in order to know what we want to project in the line
	 * ASSUMPTION:
	 *		we have 120 lines per rotation
	 * 		in other case it shall be modified
*/
inline void actualizePosition(){
	exactOneDot ++;
	if(exactOneDot == 2){
		exactOneDot = 0;
		exactMinute ++;
		if(exactMinute == 5){
			exactMinute = 0;
		}
	}
	
}

/* 
 * The function chose the correct frame to display
 * using current hour, niddle positions,
 * We need to save which frame to display at which position
 * It is stored in Frame[120] where each index indicates the line number
 * we have 120 lines per rotation
*/

inline void calculateLineAndRabin()
{
	if(fSecondTimerFlag())
	{
		addSecond();
		calculateHands();
	}
	display.SetLedRGBfromTable(calculateLine());
	actualizePosition();
	(position>=120-1) ? position=0 : position++;
}


inline void waitForTimer()
{
	while(!fDisplayed)
		;
	fDisplayed=false;
}
/*
inline bool TEST_BUTTON_INIT()
{
	A3inputpull();
}
*/
inline void TEST_AwaitButtonPress()
{
	/*
	while(!fSecondTimerFlag())
		;
	while((PINC & (1<< 3)) != 0)
		;
	TCNT1=0; // reset timer
	// let's use A3 button 
	*/
}

void setTimeAndRun(uint8_t h,uint8_t m, uint8_t s )
{
	minutes=m;
	hour=h;
	seconds=s;
	position=0;
	exactMinute=0;
	exactOneDot=0;
	calculateHands();
	display.SetLedRGBfromTable(TestWhiteLine);
	display.Display();
	for(volatile uint8_t i=0;i<120;i++)
	{
		calculateLineAndRabin();
		display.Display();
	}
	
}


inline void testTIME()
{
	setTimeAndRun(00,01,02);
	setTimeAndRun(0,1,35);
	setTimeAndRun(0,6,1);
	setTimeAndRun(0,12,1);
}


inline void test()
{
	//TEST_BUTTON_INIT();
	volatile uint16_t debugState=0;
	display.SetLedRGBfromTable(TestWhiteLine);
	display.Display();
	while(1)
	{
		//TEST_AwaitButtonPress();
			if(debugState==0)
				display.SetLedRGBfromTable(NoNiddleOneDot);
			else if(debugState==1)
				display.SetLedRGBfromTable(NoNiddleTwoDots);
			else if(debugState==2)
				display.SetLedRGBfromTable(NoNiddleThreeDots);
			else if(debugState==3)
				display.SetLedRGBfromTable(OnylSecondsOnTwoDots);
			else if(debugState==4)
				display.SetLedRGBfromTable(OnylSecondsOnThreeDots);
			else if(debugState==5)
				display.SetLedRGBfromTable(OnylMinuteOnOneDot);
			else if(debugState==6)
				display.SetLedRGBfromTable(OnylMinuteOnTwoDots);
			else if(debugState==7)
				display.SetLedRGBfromTable(OnylMinuteOnThreeDots);
			else if(debugState==8)
				display.SetLedRGBfromTable(OnylHoureOnOneDot);
			else if(debugState==9)
				display.SetLedRGBfromTable(OnylHoureOnTwoDots);
			else if(debugState==10)
				display.SetLedRGBfromTable(OnylHoureOnThreeDots);
			else if(debugState==11)
				display.SetLedRGBfromTable(HoureAndMinutesOnOneDot);
			else if(debugState==12)
				display.SetLedRGBfromTable(HoureAndMinutesOnTwoDots);
			else if(debugState==13)
				display.SetLedRGBfromTable(HoureAndMinutesOnThreeDots);//ok jendak dalej to samo nope (3x biale, 4x red, 5 x red+blue), inaczje sekundy godizny 3 kropki
			else if(debugState==14)
				display.SetLedRGBfromTable(HouresAndSecondsOnTwoDots);// ok
			else if(debugState==15)
				display.SetLedRGBfromTable(HouresAndSecondsOnThreeDots);//  ok
			else if(debugState==16)
				display.SetLedRGBfromTable(MinuteAndSecondsOnTwoDots);//ok
			else if(debugState==17)
				display.SetLedRGBfromTable(MinuteAndSecondsOnThreeDots);//ok
			else if(debugState==18)
				display.SetLedRGBfromTable(HoureMinuteSecondOnTwoDots);//nope 3x biale 2xRed+Green 2x empty 5x white 
			else if(debugState==19)
				display.SetLedRGBfromTable(HoureMinuteSecondOnThreeDots); //nope 3x biale, 2x red+green 2x empty 5x white
			
			display.Display();
			
			debugState++;
			if(debugState>=20)
				debugState=0;

	}
}


void testPos()
{
	ready=1;
	while(true)
	{
		uint8_t pinStatus= readPosControl();
		if(!pinStatus)
		{	
			for(int i=0;i<12*3;i++)
			{
				outTable[i]=0;		
			}
			outTable[15]=255;
			outTable[16]=255;
			outTable[17]=255;
		}
		else
		{
			for(int i=0;i<12*3;i++)
			{
				outTable[i]=0;
			}
		}
		display.SetLedRGBfromTable(outTable);
		while(!fDisplayed)
			;
	}
}

void waitForSpeed()
{
	
	uint8_t timesInSeconds=0;
	while(timesInSeconds<15)
	{
		if(fSecondTimerFlag())
			timesInSeconds=0;
		while(true)
		{
			if(!readPosControl())
			timesInSeconds++;
			for(uint8_t i=0;i<60;i++)
				while(!fDisplayed)
					fDisplayed=true;
			
		}
	}
}


void testArtifacts()
{
	ready=0;
	volatile uint32_t lineCounter=0;
	secondTimerFlag=0;
	calculateLineAndRabin();
	for(uint8_t i=0;i<10;i++)
	{
		while(true)
		{
			if(lineCounter == long(2*i) + long(i*15*120))
			{
				display.Display();
				volatile uint8_t hue;
				hue=1;
				hue=2;
				hue=hue-hue;
				secondTimerFlag=1;
				calculateLineAndRabin();
				lineCounter++;
				break;
			}
			else
			{
				cli();
				__asm__ __volatile__ ("nop");
				__asm__ __volatile__ ("nop");
				secondTimerFlag=0;
				calculateLineAndRabin();
				lineCounter++;
				sei();
			
			}
		}
	}
}

int main(void)
{
	D13output();
	//setD13();
	init();
	#ifdef DEBUG_IO
	//uint8_t state=0;
	uint16_t times=0;
	#endif
    uint8_t linesCounter=0;
	//testPos();
	//testTIME();
	//test();
	testArtifacts();
	ready=1;
    while (1) 
    {
		if (linesCounter==LINES_PER_FRAME-1)
		{
			resetDisplayTimer(); // make sure that timer will not interrupt us.
			calculateLineAndRabin();	// calculate while waiting for synchronization
			// IO signal will take longer than calculation.
			volatile uint8_t posStatuts= readPosControl();
			while(posStatuts)
			{
				resetDisplayTimer();
				posStatuts= readPosControl();
			}
			resetDisplayTimer(); // we set timer to 0 
			displayInterruptProd(); // and call our "fake" interrupt. 
			//we made it like timer made the tick for us.
			linesCounter=0;
		}
		else
		{
			calculateLineAndRabin();
			waitForTimer();
			linesCounter++;
		}
    }
}






































































































/* Generating frames to Display */
void createLines(){
	/* Without any niddle */
	/* One dot */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 1;i++){
		NoNiddleOneDot[3*i+0] = BACKGROUND_RED;
		NoNiddleOneDot[3*i+1] = BACKGROUND_GREEN;
		NoNiddleOneDot[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 1;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleOneDot[3*i+0] = DOT_RED;
		NoNiddleOneDot[3*i+1] = DOT_GREEN;
		NoNiddleOneDot[3*i+2] = DOT_BLUE;
	}
	/* Two dots */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 2;i++){
		NoNiddleTwoDots[3*i+0] = BACKGROUND_RED;
		NoNiddleTwoDots[3*i+1] = BACKGROUND_GREEN;
		NoNiddleTwoDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 2;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleTwoDots[3*i+0] = DOT_RED;
		NoNiddleTwoDots[3*i+1] = DOT_GREEN;
		NoNiddleTwoDots[3*i+2] = DOT_BLUE;
	}
	/* Three dots */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 3;i++){
		NoNiddleThreeDots[3*i+0] = BACKGROUND_RED;
		NoNiddleThreeDots[3*i+1] = BACKGROUND_GREEN;
		NoNiddleThreeDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 3;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleThreeDots[3*i+0] = DOT_RED;
		NoNiddleThreeDots[3*i+1] = DOT_GREEN;
		NoNiddleThreeDots[3*i+2] = DOT_BLUE;
	}
	
	/* Only second frames */
	/* TwoDots */
	for(volatile uint8_t i=0;i<SECOND_SIZE;i++){
		OnylSecondsOnTwoDots[3*i+0] = SECOND_RED;
		OnylSecondsOnTwoDots[3*i+1] = SECOND_GREEN;
		OnylSecondsOnTwoDots[3*i+2] = SECOND_BLUE;
	}
	OnylSecondsOnTwoDots[3*SECOND_SIZE] = BACKGROUND_RED;
	OnylSecondsOnTwoDots[3*SECOND_SIZE+1] = BACKGROUND_GREEN;
	OnylSecondsOnTwoDots[3*SECOND_SIZE+2] = BACKGROUND_BLUE;
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylSecondsOnTwoDots[3*i+0] = DOT_RED;
		OnylSecondsOnTwoDots[3*i+1] = DOT_GREEN;
		OnylSecondsOnTwoDots[3*i+2] = DOT_BLUE;
	}
	
	/* ThreeDots */
	for(uint8_t i=0;i<SECOND_SIZE;i++){
		OnylSecondsOnThreeDots[3*i+0] = SECOND_RED;
		OnylSecondsOnThreeDots[3*i+1] = SECOND_GREEN;
		OnylSecondsOnThreeDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylSecondsOnThreeDots[3*i+0] = DOT_RED;
		OnylSecondsOnThreeDots[3*i+1] = DOT_GREEN;
		OnylSecondsOnThreeDots[3*i+2] = DOT_BLUE;
	}
	
	/* Only minute frames */
	/*On  one dot*/
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnOneDot[3*i+0] = MINUTE_RED;
		OnylMinuteOnOneDot[3*i+1] = MINUTE_GREEN;
		OnylMinuteOnOneDot[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		OnylMinuteOnOneDot[3*i+0] = BACKGROUND_RED;
		OnylMinuteOnOneDot[3*i+1] = BACKGROUND_GREEN;
		OnylMinuteOnOneDot[3*i+2] = BACKGROUND_BLUE;
		}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnOneDot[3*i+0] = DOT_RED;
		OnylMinuteOnOneDot[3*i+1] = DOT_GREEN;
		OnylMinuteOnOneDot[3*i+2] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnTwoDots[3*i+0] = MINUTE_RED;
		OnylMinuteOnTwoDots[3*i+1] = MINUTE_GREEN;
		OnylMinuteOnTwoDots[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		OnylMinuteOnTwoDots[3*i+0] = BACKGROUND_RED;
		OnylMinuteOnTwoDots[3*i+1] = BACKGROUND_GREEN;
		OnylMinuteOnTwoDots[3*i+2] = BACKGROUND_BLUE;
		}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnTwoDots[3*i+0] = DOT_RED;
		OnylMinuteOnTwoDots[3*i+1] = DOT_GREEN;
		OnylMinuteOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnThreeDots[3*i+0] = MINUTE_RED;
		OnylMinuteOnThreeDots[3*i+1] = MINUTE_GREEN;
		OnylMinuteOnThreeDots[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		OnylMinuteOnThreeDots[3*i+0] = BACKGROUND_RED;
		OnylMinuteOnThreeDots[3*i+1] = BACKGROUND_GREEN;
		OnylMinuteOnThreeDots[3*i+2] = BACKGROUND_BLUE;
		}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnThreeDots[3*i+0] = DOT_RED;
		OnylMinuteOnThreeDots[3*i+1] = DOT_GREEN;
		OnylMinuteOnThreeDots[3*i+2] = DOT_BLUE;
	}
	
	/* Only houres frames */
	/*On  one dot*/
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnOneDot[3*i+0] = HOUR_RED;
		OnylHoureOnOneDot[3*i+1] = HOUR_GREEN;
		OnylHoureOnOneDot[3*i+2] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		OnylHoureOnOneDot[3*i+0] = BACKGROUND_RED;
		OnylHoureOnOneDot[3*i+1] = BACKGROUND_GREEN;
		OnylHoureOnOneDot[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnOneDot[3*i+0] = DOT_RED;
		OnylHoureOnOneDot[3*i+1] = DOT_GREEN;
		OnylHoureOnOneDot[3*i+2] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnTwoDots[3*i+0] = HOUR_RED;
		OnylHoureOnTwoDots[3*i+1] = HOUR_GREEN;
		OnylHoureOnTwoDots[3*i+2] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		OnylHoureOnTwoDots[3*i+0] = BACKGROUND_RED;
		OnylHoureOnTwoDots[3*i+1] = BACKGROUND_GREEN;
		OnylHoureOnTwoDots[3*i+2] = BACKGROUND_BLUE;
		}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnTwoDots[3*i+0] = DOT_RED;
		OnylHoureOnTwoDots[3*i+1] = DOT_GREEN;
		OnylHoureOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnThreeDots[3*i+0] = HOUR_RED;
		OnylHoureOnThreeDots[3*i+1] = HOUR_GREEN;
		OnylHoureOnThreeDots[3*i+2] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		OnylHoureOnThreeDots[3*i+0] = BACKGROUND_RED;
		OnylHoureOnThreeDots[3*i+1] = BACKGROUND_GREEN;
		OnylHoureOnThreeDots[3*i+2] = BACKGROUND_BLUE;
		}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnThreeDots[3*i+0] = DOT_RED;
		OnylHoureOnThreeDots[3*i+1] = DOT_GREEN;
		OnylHoureOnThreeDots[3*i+2] = DOT_BLUE;
	}
	
	/*Houre with minute */
	/*On  one dot*/
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnOneDot[3*i+0] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnOneDot[3*i+1] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnOneDot[3*i+2] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnOneDot[3*i+0] = MINUTE_RED;
		HoureAndMinutesOnOneDot[3*i+1] = MINUTE_GREEN;
		HoureAndMinutesOnOneDot[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		HoureAndMinutesOnOneDot[3*i+0] = BACKGROUND_RED;
		HoureAndMinutesOnOneDot[3*i+1] = BACKGROUND_GREEN;
		HoureAndMinutesOnOneDot[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnOneDot[3*i+0] = DOT_RED;
		HoureAndMinutesOnOneDot[3*i+1] = DOT_GREEN;
		HoureAndMinutesOnOneDot[3*i+2] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnTwoDots[3*i+0] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnTwoDots[3*i+1] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnTwoDots[3*i+2] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnTwoDots[3*i+0] = MINUTE_RED;
		HoureAndMinutesOnTwoDots[3*i+1] = MINUTE_GREEN;
		HoureAndMinutesOnTwoDots[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		HoureAndMinutesOnTwoDots[3*i+0] = BACKGROUND_RED;
		HoureAndMinutesOnTwoDots[3*i+1] = BACKGROUND_GREEN;
		HoureAndMinutesOnTwoDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnTwoDots[3*i+0] = DOT_RED;
		HoureAndMinutesOnTwoDots[3*i+1] = DOT_GREEN;
		HoureAndMinutesOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+0] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnThreeDots[3*i+1] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnThreeDots[3*i+2] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+0] = MINUTE_RED;
		HoureAndMinutesOnThreeDots[3*i+1] = MINUTE_GREEN;
		HoureAndMinutesOnThreeDots[3*i+2] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		HoureAndMinutesOnThreeDots[3*i+0] = BACKGROUND_RED;
		HoureAndMinutesOnThreeDots[3*i+1] = BACKGROUND_GREEN;
		HoureAndMinutesOnThreeDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnThreeDots[3*i+0] = DOT_RED;
		HoureAndMinutesOnThreeDots[3*i+1] = DOT_GREEN;
		HoureAndMinutesOnThreeDots[3*i+2] = DOT_BLUE;
	}
	
	/*Houre with second */
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HouresAndSecondsOnTwoDots[3*i+0] = HOUR_RED + SECOND_RED;
		HouresAndSecondsOnTwoDots[3*i+1] = HOUR_GREEN + SECOND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+2] = HOUR_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<SECOND_SIZE;i++){
		HouresAndSecondsOnTwoDots[3*i+0] = SECOND_RED;
		HouresAndSecondsOnTwoDots[3*i+1] = SECOND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		HouresAndSecondsOnTwoDots[3*i+0] = BACKGROUND_RED;
		HouresAndSecondsOnTwoDots[3*i+1] = BACKGROUND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HouresAndSecondsOnTwoDots[3*i+0] = DOT_RED;
		HouresAndSecondsOnTwoDots[3*i+1] = DOT_GREEN;
		HouresAndSecondsOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HouresAndSecondsOnThreeDots[3*i+0] = HOUR_RED + SECOND_RED;
		HouresAndSecondsOnThreeDots[3*i+1] = HOUR_GREEN + SECOND_GREEN;
		HouresAndSecondsOnThreeDots[3*i+2] = HOUR_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<SECOND_SIZE;i++){
		HouresAndSecondsOnThreeDots[3*i+0] = SECOND_RED;
		HouresAndSecondsOnThreeDots[3*i+1] = SECOND_GREEN;
		HouresAndSecondsOnThreeDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		HouresAndSecondsOnThreeDots[3*i+0] = BACKGROUND_RED;
		HouresAndSecondsOnThreeDots[3*i+1] = BACKGROUND_GREEN;
		HouresAndSecondsOnThreeDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HouresAndSecondsOnThreeDots[3*i+0] = DOT_RED;
		HouresAndSecondsOnThreeDots[3*i+1] = DOT_GREEN;
		HouresAndSecondsOnThreeDots[3*i+2] = DOT_BLUE;
	}
	/*Minute with second */
	/*On two dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		MinuteAndSecondsOnTwoDots[3*i+0] = MINUTE_RED + SECOND_RED;
		MinuteAndSecondsOnTwoDots[3*i+1] = MINUTE_GREEN + SECOND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+2] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		MinuteAndSecondsOnTwoDots[3*i+0] = SECOND_RED;
		MinuteAndSecondsOnTwoDots[3*i+1] = SECOND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		MinuteAndSecondsOnTwoDots[3*i+0] = BACKGROUND_RED;
		MinuteAndSecondsOnTwoDots[3*i+1] = BACKGROUND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		MinuteAndSecondsOnTwoDots[3*i+0] = DOT_RED;
		MinuteAndSecondsOnTwoDots[3*i+1] = DOT_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		MinuteAndSecondsOnThreeDots[3*i+0] = MINUTE_RED + SECOND_RED;
		MinuteAndSecondsOnThreeDots[3*i+1] = MINUTE_GREEN + SECOND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+2] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		MinuteAndSecondsOnThreeDots[3*i+0] = SECOND_RED;
		MinuteAndSecondsOnThreeDots[3*i+1] = SECOND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		MinuteAndSecondsOnThreeDots[3*i+0] = BACKGROUND_RED;
		MinuteAndSecondsOnThreeDots[3*i+1] = BACKGROUND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+2] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		MinuteAndSecondsOnThreeDots[3*i+0] = DOT_RED;
		MinuteAndSecondsOnThreeDots[3*i+1] = DOT_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+2] = DOT_BLUE;
	}
	/*Minute houre and second together */
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+0] = HOUR_RED + MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+1] = HOUR_GREEN + MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+2] = HOUR_BLUE + MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+0] = MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+1] = MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+2] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+0] = SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+1] = SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+2] = SECOND_BLUE;
	}
	HoureMinuteSecondOnTwoDots[3*SECOND_SIZE+0]=BACKGROUND_RED;
	HoureMinuteSecondOnTwoDots[3*SECOND_SIZE+1]=BACKGROUND_GREEN;
	HoureMinuteSecondOnTwoDots[3*SECOND_SIZE+2]=BACKGROUND_BLUE;
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureMinuteSecondOnTwoDots[3*i+0] = DOT_RED;
		HoureMinuteSecondOnTwoDots[3*i+1] = DOT_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+2] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureMinuteSecondOnThreeDots[3*i+0] = HOUR_RED + MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnThreeDots[3*i+1] = HOUR_GREEN + MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnThreeDots[3*i+2] = HOUR_BLUE + MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureMinuteSecondOnThreeDots[3*i+0] = MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnThreeDots[3*i+1] = MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnThreeDots[3*i+2] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		HoureMinuteSecondOnThreeDots[3*i+0] = SECOND_RED;
		HoureMinuteSecondOnThreeDots[3*i+1] = SECOND_GREEN;
		HoureMinuteSecondOnThreeDots[3*i+2] = SECOND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureMinuteSecondOnThreeDots[3*i+0] = DOT_RED;
		HoureMinuteSecondOnThreeDots[3*i+1] = DOT_GREEN;
		HoureMinuteSecondOnThreeDots[3*i+2] = DOT_BLUE;
	}
}