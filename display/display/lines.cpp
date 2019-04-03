/*
 * lines.cpp
 *
 * Created: 01.12.2018 20:05:30
 *  Author: Marek Fudalinski
 */ 



#include "lines.h"
#include "CDiagNeopixel.h"
#include <avr/io.h>




void createLines(){
	/* Without any niddle */
	/* One dot */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 1;i++){
		NoNiddleTwoDots[3*i+1] = BACKGROUND_RED;
		NoNiddleTwoDots[3*i+2] = BACKGROUND_GREEN;
		NoNiddleTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 1;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleTwoDots[3*i+1] = DOT_RED;
		NoNiddleTwoDots[3*i+2] = DOT_GREEN;
		NoNiddleTwoDots[3*i+3] = DOT_BLUE;
	}
	/* Two dots */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 2;i++){
		NoNiddleTwoDots[3*i+1] = BACKGROUND_RED;
		NoNiddleTwoDots[3*i+2] = BACKGROUND_GREEN;
		NoNiddleTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 2;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleTwoDots[3*i+1] = DOT_RED;
		NoNiddleTwoDots[3*i+2] = DOT_GREEN;
		NoNiddleTwoDots[3*i+3] = DOT_BLUE;
	}
	/* Three dots */
	for(uint8_t i=0;i<NUMBER_OF_DIAG_LEDS - 3;i++){
		NoNiddleThreeDots[3*i+1] = BACKGROUND_RED;
		NoNiddleThreeDots[3*i+2] = BACKGROUND_GREEN;
		NoNiddleThreeDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS - 3;i<NUMBER_OF_DIAG_LEDS;i++){
		NoNiddleThreeDots[3*i+1] = DOT_RED;
		NoNiddleThreeDots[3*i+2] = DOT_GREEN;
		NoNiddleThreeDots[3*i+3] = DOT_BLUE;
	}
	
	/* Only second frames */
	/* TwoDots */
	for(uint8_t i=0;i<SECOND_SIZE;i++){
		OnylSecondsOnTwoDots[3*i+1] = SECOND_RED;
		OnylSecondsOnTwoDots[3*i+2] = SECOND_GREEN;
		OnylSecondsOnTwoDots[3*i+3] = SECOND_BLUE;
	}
	OnylSecondsOnTwoDots[SECOND_SIZE+1] = BACKGROUND_RED;
	OnylSecondsOnTwoDots[SECOND_SIZE+2] = BACKGROUND_GREEN;
	OnylSecondsOnTwoDots[SECOND_SIZE+3] = BACKGROUND_BLUE;
	for(uint8_t i=SECOND_SIZE+1;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylSecondsOnTwoDots[3*i+1] = DOT_RED;
		OnylSecondsOnTwoDots[3*i+2] = DOT_GREEN;
		OnylSecondsOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/* ThreeDots */
	for(uint8_t i=0;i<SECOND_SIZE;i++){
		OnylSecondsOnThreeDots[3*i+1] = SECOND_RED;
		OnylSecondsOnThreeDots[3*i+2] = SECOND_GREEN;
		OnylSecondsOnThreeDots[3*i+3] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylSecondsOnThreeDots[3*i+1] = DOT_RED;
		OnylSecondsOnThreeDots[3*i+2] = DOT_GREEN;
		OnylSecondsOnThreeDots[3*i+3] = DOT_BLUE;
	}
	
	/* Only minute frames */
	/*On  one dot*/
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnOneDot[3*i+1] = MINUTE_RED;
		OnylMinuteOnOneDot[3*i+2] = MINUTE_GREEN;
		OnylMinuteOnOneDot[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		OnylMinuteOnOneDot[3*i+1] = BACKGROUND_RED;
		OnylMinuteOnOneDot[3*i+2] = BACKGROUND_GREEN;
		OnylMinuteOnOneDot[3*i+3] = BACKGROUND_BLUE;
		}for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnOneDot[3*i+1] = DOT_RED;
		OnylMinuteOnOneDot[3*i+2] = DOT_GREEN;
		OnylMinuteOnOneDot[3*i+3] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnTwoDots[3*i+1] = MINUTE_RED;
		OnylMinuteOnTwoDots[3*i+2] = MINUTE_GREEN;
		OnylMinuteOnTwoDots[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		OnylMinuteOnTwoDots[3*i+1] = BACKGROUND_RED;
		OnylMinuteOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		OnylMinuteOnTwoDots[3*i+3] = BACKGROUND_BLUE;
		}for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnTwoDots[3*i+1] = DOT_RED;
		OnylMinuteOnTwoDots[3*i+2] = DOT_GREEN;
		OnylMinuteOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		OnylMinuteOnThreeDots[3*i+1] = MINUTE_RED;
		OnylMinuteOnThreeDots[3*i+2] = MINUTE_GREEN;
		OnylMinuteOnThreeDots[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		OnylMinuteOnThreeDots[3*i+1] = BACKGROUND_RED;
		OnylMinuteOnThreeDots[3*i+2] = BACKGROUND_GREEN;
		OnylMinuteOnThreeDots[3*i+3] = BACKGROUND_BLUE;
		}for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylMinuteOnThreeDots[3*i+1] = DOT_RED;
		OnylMinuteOnThreeDots[3*i+2] = DOT_GREEN;
		OnylMinuteOnThreeDots[3*i+3] = DOT_BLUE;
	}
	
	/* Only houres frames */
	/*On  one dot*/
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnOneDot[3*i+1] = HOUR_RED;
		OnylHoureOnOneDot[3*i+2] = HOUR_GREEN;
		OnylHoureOnOneDot[3*i+3] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		OnylHoureOnOneDot[3*i+1] = BACKGROUND_RED;
		OnylHoureOnOneDot[3*i+2] = BACKGROUND_GREEN;
		OnylHoureOnOneDot[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnOneDot[3*i+1] = DOT_RED;
		OnylHoureOnOneDot[3*i+2] = DOT_GREEN;
		OnylHoureOnOneDot[3*i+3] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnTwoDots[3*i+1] = HOUR_RED;
		OnylHoureOnTwoDots[3*i+2] = HOUR_GREEN;
		OnylHoureOnTwoDots[3*i+3] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		OnylHoureOnTwoDots[3*i+1] = BACKGROUND_RED;
		OnylHoureOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		OnylHoureOnTwoDots[3*i+3] = BACKGROUND_BLUE;
		}for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnTwoDots[3*i+1] = DOT_RED;
		OnylHoureOnTwoDots[3*i+2] = DOT_GREEN;
		OnylHoureOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		OnylHoureOnThreeDots[3*i+1] = HOUR_RED;
		OnylHoureOnThreeDots[3*i+2] = HOUR_GREEN;
		OnylHoureOnThreeDots[3*i+3] = HOUR_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		OnylHoureOnThreeDots[3*i+1] = BACKGROUND_RED;
		OnylHoureOnThreeDots[3*i+2] = BACKGROUND_GREEN;
		OnylHoureOnThreeDots[3*i+3] = BACKGROUND_BLUE;
		}for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		OnylHoureOnThreeDots[3*i+1] = DOT_RED;
		OnylHoureOnThreeDots[3*i+2] = DOT_GREEN;
		OnylHoureOnThreeDots[3*i+3] = DOT_BLUE;
	}
	
	/*Houre with minute */
	/*On  one dot*/
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnOneDot[3*i+1] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnOneDot[3*i+2] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnOneDot[3*i+3] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnOneDot[3*i+1] = MINUTE_RED;
		HoureAndMinutesOnOneDot[3*i+2] = MINUTE_GREEN;
		HoureAndMinutesOnOneDot[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-1;i++){
		HoureAndMinutesOnOneDot[3*i+1] = BACKGROUND_RED;
		HoureAndMinutesOnOneDot[3*i+2] = BACKGROUND_GREEN;
		HoureAndMinutesOnOneDot[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-1;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnOneDot[3*i+1] = DOT_RED;
		HoureAndMinutesOnOneDot[3*i+2] = DOT_GREEN;
		HoureAndMinutesOnOneDot[3*i+3] = DOT_BLUE;
	}
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnTwoDots[3*i+1] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnTwoDots[3*i+2] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnTwoDots[3*i+3] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnTwoDots[3*i+1] = MINUTE_RED;
		HoureAndMinutesOnTwoDots[3*i+2] = MINUTE_GREEN;
		HoureAndMinutesOnTwoDots[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		HoureAndMinutesOnTwoDots[3*i+1] = BACKGROUND_RED;
		HoureAndMinutesOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		HoureAndMinutesOnTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnTwoDots[3*i+1] = DOT_RED;
		HoureAndMinutesOnTwoDots[3*i+2] = DOT_GREEN;
		HoureAndMinutesOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = HOUR_RED + MINUTE_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = HOUR_GREEN + MINUTE_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = HOUR_BLUE + MINUTE_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<MINUTE_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = MINUTE_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = MINUTE_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = MINUTE_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = BACKGROUND_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = BACKGROUND_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = DOT_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = DOT_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = DOT_BLUE;
	}
	
	/*Houre with second */
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HouresAndSecondsOnTwoDots[3*i+1] = HOUR_RED + SECOND_RED;
		HouresAndSecondsOnTwoDots[3*i+2] = HOUR_GREEN + SECOND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+3] = HOUR_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<SECOND_SIZE;i++){
		HouresAndSecondsOnTwoDots[3*i+1] = SECOND_RED;
		HouresAndSecondsOnTwoDots[3*i+2] = SECOND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+3] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		HouresAndSecondsOnTwoDots[3*i+1] = BACKGROUND_RED;
		HouresAndSecondsOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		HouresAndSecondsOnTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HouresAndSecondsOnTwoDots[3*i+1] = DOT_RED;
		HouresAndSecondsOnTwoDots[3*i+2] = DOT_GREEN;
		HouresAndSecondsOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = HOUR_RED + SECOND_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = HOUR_GREEN + SECOND_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = HOUR_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=HOUR_SIZE;i<SECOND_SIZE;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = SECOND_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = SECOND_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = BACKGROUND_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = BACKGROUND_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureAndMinutesOnThreeDots[3*i+1] = DOT_RED;
		HoureAndMinutesOnThreeDots[3*i+2] = DOT_GREEN;
		HoureAndMinutesOnThreeDots[3*i+3] = DOT_BLUE;
	}
	/*Minute with second */
	/*On two dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		MinuteAndSecondsOnTwoDots[3*i+1] = MINUTE_RED + SECOND_RED;
		MinuteAndSecondsOnTwoDots[3*i+2] = MINUTE_GREEN + SECOND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+3] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		MinuteAndSecondsOnTwoDots[3*i+1] = SECOND_RED;
		MinuteAndSecondsOnTwoDots[3*i+2] = SECOND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+3] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		MinuteAndSecondsOnTwoDots[3*i+1] = BACKGROUND_RED;
		MinuteAndSecondsOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		MinuteAndSecondsOnTwoDots[3*i+1] = DOT_RED;
		MinuteAndSecondsOnTwoDots[3*i+2] = DOT_GREEN;
		MinuteAndSecondsOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<MINUTE_SIZE;i++){
		MinuteAndSecondsOnThreeDots[3*i+1] = MINUTE_RED + SECOND_RED;
		MinuteAndSecondsOnThreeDots[3*i+2] = MINUTE_GREEN + SECOND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+3] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		MinuteAndSecondsOnThreeDots[3*i+1] = SECOND_RED;
		MinuteAndSecondsOnThreeDots[3*i+2] = SECOND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+3] = SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		MinuteAndSecondsOnThreeDots[3*i+1] = BACKGROUND_RED;
		MinuteAndSecondsOnThreeDots[3*i+2] = BACKGROUND_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		MinuteAndSecondsOnThreeDots[3*i+1] = DOT_RED;
		MinuteAndSecondsOnThreeDots[3*i+2] = DOT_GREEN;
		MinuteAndSecondsOnThreeDots[3*i+3] = DOT_BLUE;
	}
	/*Minute houre and second together */
	/*On two dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = HOUR_RED + MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = HOUR_GREEN + MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = HOUR_BLUE + MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-2;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = BACKGROUND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-2;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = DOT_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = DOT_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = DOT_BLUE;
	}
	/*On three dots */
	for(uint8_t i=0;i<HOUR_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = HOUR_RED + MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = HOUR_GREEN + MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = HOUR_BLUE + MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=MINUTE_SIZE;i<SECOND_SIZE;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = MINUTE_RED + SECOND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = MINUTE_GREEN + SECOND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = MINUTE_BLUE + SECOND_BLUE;
	}
	for(uint8_t i=SECOND_SIZE;i<NUMBER_OF_DIAG_LEDS-3;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = BACKGROUND_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = BACKGROUND_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = BACKGROUND_BLUE;
	}
	for(uint8_t i=NUMBER_OF_DIAG_LEDS-3;i<NUMBER_OF_DIAG_LEDS;i++){
		HoureMinuteSecondOnTwoDots[3*i+1] = DOT_RED;
		HoureMinuteSecondOnTwoDots[3*i+2] = DOT_GREEN;
		HoureMinuteSecondOnTwoDots[3*i+3] = DOT_BLUE;
	}
}

