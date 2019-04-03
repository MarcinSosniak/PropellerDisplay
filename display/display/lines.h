/*
 * IncFile2.h
 *
 * Created: 01.12.2018 20:06:04
 *  Author: MarcinS
 */ 


#ifndef INCFILE2_H_
#define INCFILE2_H_
/*SUM OF NIDDLE COLORS CANNOT BE GREATER THAN 255 */
/*Second niddle is the largest while Houre niddle is the smallest */
#include <avr/io.h>
#include "CDiagNeopixel.h"

void createLines();

/*NIDDLES*/
#define SECOND_SIZE 9
#define SECOND_RED 10
#define SECOND_GREEN 0
#define SECOND_BLUE 0

#define MINUTE_SIZE 7
#define MINUTE_RED 0
#define MINUTE_GREEN 10
#define MINUTE_BLUE 0

#define HOUR_SIZE 5
#define HOUR_RED 0
#define HOUR_GREEN 0
#define HOUR_BLUE 10

/*Background */
#define BACKGROUND_RED 0
#define BACKGROUND_GREEN 0
#define BACKGROUND_BLUE 0

/*Dots */
#define DOT_RED 10
#define DOT_GREEN 10
#define DOT_BLUE 10

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






#endif /* INCFILE2_H_ */