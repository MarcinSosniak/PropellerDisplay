#include "CDiagNeopixel.h" 
#include "nano_io.h"
#include "F_CPU.h"
#include <util/delay.h>

//-----------------------------------------------------------------------------
extern "C" void DisplayNeopixelA4(char * pBuf, uint8_t ucCounter);
//-----------------------------------------------------------------------------

// Changed fro arduino nano 

//-----------------------------------------------------------------------------
CDiagNeopixel::CDiagNeopixel()
{
	/*
	clrA4();		// noepixel LEDs connected to Arduino NANO A5 pin
	A4output();
	*/
	clrD0(); // version for arduino nano
	D0output();
	for (uint8_t i= 0 ; i < NUMBER_OF_DIAG_LEDS; i++)
		SetLedRGB(i,0,0,0);
		
	m_Invalidated = 1;
}

//-----------------------------------------------------------------------------
void CDiagNeopixel::SetLedRGB (uint8_t i, uint8_t ValR, uint8_t ValG, uint8_t ValB)
{
	if (i >= NUMBER_OF_DIAG_LEDS)
		return;
	
	if ((m_LedBuf[i].g != ValG) || (m_LedBuf[i].r != ValR) || (m_LedBuf[i].b != ValB))
		m_Invalidated = 1;
		
	m_LedBuf[i].g = ValG;
	m_LedBuf[i].r = ValR;
	m_LedBuf[i].b = ValB;	
	
}

void CDiagNeopixel::SetLedRGBfromTable(uint8_t table[])
{
	volatile uint8_t k;
	for(volatile uint8_t i=0;i<NUMBER_OF_DIAG_LEDS;i++)
	{
		k=3*i;
		this->m_LedBuf[i].r=table[k];
		m_LedBuf[i].g=table[k+1];
		m_LedBuf[i].b=table[k+2];
	}
	m_Invalidated=1;
}


//-----------------------------------------------------------------------------
void CDiagNeopixel::Display()
{
	
	if (!m_Invalidated)
		return;
		
	_delay_us(70);	// reset Neopixel LEDs
	
	DisplayNeopixelA4((char*) m_LedBuf, NUMBER_OF_DIAG_LEDS);
	
	m_Invalidated = 0;
}

//-----------------------------------------------------------------------------
void CDiagNeopixel::ForceDisplay()
{
	m_Invalidated = 1;
	
	Display();
}