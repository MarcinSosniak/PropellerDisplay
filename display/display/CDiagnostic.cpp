#include "CDiagnostic.h"
#include <avr/io.h>
#include "nano_io.h"


//-----------------------------------------------------------------------------
CDiagnostic::CDiagnostic(uint8_t on, uint8_t off)
{
	D2inputpull();		// configure D2 pin as input DIAG pushbutton
	
	clrD13();			// L diode
	D13output();
	
	m_LastDiagButtonState = (1<<PIND2);  //  set last state as inactive
	m_DiagButtonPushed = 0;	
	
	m_ProgrammingMode = 0;
	
	m_LState = 0;
	m_LCnt = 0;

	SetLOnOffTime(on, off);		
}

//-----------------------------------------------------------------------------
void CDiagnostic::Init()
{
	Neopixel.Display(); // diodes off
	
	// set initial values
	ElementInRange(DIAG_WEGHT_1);
	ElementInRange(DIAG_WEGHT_2);
	ElementInRange(DIAG_WEGHT_3);
};

//-----------------------------------------------------------------------------
uint8_t CDiagnostic::IsDiagPushed()
{
	uint8_t	ret;
	
	ret = m_DiagButtonPushed;
	
	m_DiagButtonPushed = 0;
	
	return ret;
}

//-----------------------------------------------------------------------------
void CDiagnostic::EnterProgrammingMode()
{

	ElementProg(DIAG_WEGHT_1);
	ElementProg(DIAG_WEGHT_2);
	ElementProg(DIAG_WEGHT_3);
	
	
	Neopixel.Display();
	
	clrD13();	// switch L off
	m_ProgrammingMode = 1;	
}

//-----------------------------------------------------------------------------
void CDiagnostic::LeaveProgrammingMode()
{
	m_ProgrammingMode = 0;
}

//-----------------------------------------------------------------------------
void CDiagnostic::ElementAvgUnder(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_AVG_LOWER_R, DIAG_AVG_LOWER_G, DIAG_AVG_LOWER_B);
};

//-----------------------------------------------------------------------------
void CDiagnostic::ElementInRange(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_IN_RANGE_R, DIAG_IN_RANGE_G, DIAG_IN_RANGE_B);
};
//-----------------------------------------------------------------------------

void CDiagnostic::ElementNoise(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_AVG_OK_NOISE_R, DIAG_AVG_OK_NOISE_G, DIAG_AVG_OK_NOISE_B);	
};

//-----------------------------------------------------------------------------
void CDiagnostic::ElementNoiseLower(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_AVG_OK_NOISE_LOWER_R, DIAG_AVG_OK_NOISE_LOWER_G, DIAG_AVG_OK_NOISE_LOWER_B);	
};

//-----------------------------------------------------------------------------
void CDiagnostic::ElementNoiseGreater(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_AVG_OK_NOISE_GREATER_R, DIAG_AVG_OK_NOISE_GREATER_G, DIAG_AVG_OK_NOISE_GREATER_B);	
};

//-----------------------------------------------------------------------------
void CDiagnostic::ElementAvgOver(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_AVG_OVER_R, DIAG_AVG_OVER_G, DIAG_AVG_OVER_B);
};

//-----------------------------------------------------------------------------
void CDiagnostic::ElementProg(enum DIAG_DEVICE i)
{
	Neopixel.SetLedRGB(i, DIAG_PROG_R, DIAG_PROG_G, DIAG_PROG_B);
};

//-----------------------------------------------------------------------------
void CDiagnostic::SetLOnOffTime(uint8_t on, uint8_t off)
{
	if (on && off)
	{
		m_LOnTime = on;
		m_LOffTime = off;
		m_LCnt = m_LOffTime;
	}
	else
	{ // Disable
		m_LCnt = 0;
		clrD7();
	}
}

//-----------------------------------------------------------------------------
void CDiagnostic::Run()
{
	uint8_t cPort;
	

	cPort = PIND & (1<<PIND2);
	if (cPort != m_LastDiagButtonState)
	{	
		m_LastDiagButtonState = cPort;
		
		if(!cPort)
			m_DiagButtonPushed = 1;
	}

//	if(m_ProgrammingMode)
//		return;		// don't display neopixel LEDs in diagnostic mode
	
	
	Neopixel.Display();
	
		
	if(m_LCnt)
	{
		m_LCnt--;
		if(!m_LCnt)
		{
			if(m_LState)
			{ // switch to off
				m_LState = 0;
				m_LCnt = m_LOffTime;
				clrD13();
			}
			else
			{ // switch to on
				m_LState = 1;
				m_LCnt = m_LOnTime;
				setD13();
			}
		}
	}
	
}