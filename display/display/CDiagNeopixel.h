
#ifndef _CDIAGNEOPIXEL_H_
#define _CDIAGNEOPIXEL_H_ 

#include <inttypes.h>




#define  NUMBER_OF_DIAG_LEDS   12





//extern void DisplayNeopixel(LEDBUF* pBuf, uint8_t ucCounter);

///////////////////////////////////////////////////////////////////////////////
class CDiagNeopixel {
public:
	CDiagNeopixel();
	void SetLedRGB (uint8_t i, uint8_t ValR, uint8_t ValG, uint8_t ValB);
	void SetLedRGBfromTable(uint8_t * table); // it goes like this RGBRGBRGBRGB... or (RGB)^14
	void Display();
	void ForceDisplay();
	uint8_t IsInvalidated() {return m_Invalidated;};
private:	
	volatile struct LEDBUF{
					uint8_t g;
					uint8_t r;
					uint8_t b;
				}	m_LedBuf[NUMBER_OF_DIAG_LEDS];
	uint8_t m_Invalidated;
};






#endif

