/*
 * timer.h
 *
 * Created: 01.12.2018 19:43:28
 *  Author: MarcinS
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "F_CPU.h"
#include "defs.h"
#include "CDiagNeopixel.h"

inline uint8_t fTimerFlag();
void timer1init();
void timer2init();
inline void setTimer2Zero();
inline void displayInterruptProd();
inline uint8_t fTimerFlag();





#endif /* TIMER_H_ */