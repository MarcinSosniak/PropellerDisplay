
#ifndef CDIAGNOSTIC_H_
#define CDIAGNOSTIC_H_

#include "CDiagNeopixel.h" 

#define DIAG_AVG_LOWER_R  3
#define DIAG_AVG_LOWER_G  0
#define DIAG_AVG_LOWER_B  0

#define DIAG_IN_RANGE_R  0
#define DIAG_IN_RANGE_G  3
#define DIAG_IN_RANGE_B  0

#define DIAG_AVG_OK_NOISE_R  3
#define DIAG_AVG_OK_NOISE_G  0
#define DIAG_AVG_OK_NOISE_B  3

#define DIAG_AVG_OK_NOISE_LOWER_R  3
#define DIAG_AVG_OK_NOISE_LOWER_G  3
#define DIAG_AVG_OK_NOISE_LOWER_B  0

#define DIAG_AVG_OK_NOISE_GREATER_R  0
#define DIAG_AVG_OK_NOISE_GREATER_G  3
#define DIAG_AVG_OK_NOISE_GREATER_B  3

#define DIAG_AVG_OVER_R  0
#define DIAG_AVG_OVER_G  0
#define DIAG_AVG_OVER_B  3

#define DIAG_PROG_R 0
#define DIAG_PROG_G 0
#define DIAG_PROG_B 0


// L diode timing
#define WORKING_ON_TIME  1
#define WORKING_OFF_TIME 9

#define DONE_ON_TIME  5
#define DONE_OFF_TIME 5



enum DIAG_DEVICE {DIAG_WEGHT_1 = 0, DIAG_WEGHT_2, DIAG_WEGHT_3};


///////////////////////////////////////////////////////////////////////////////
class CDiagnostic {
	public:
	CDiagnostic(uint8_t on, uint8_t off);
	
	void Init();
	
	uint8_t IsDiagPushed();  // True - button pushed from last calling this function
	
	void EnterProgrammingMode();
	void LeaveProgrammingMode();
	
	
	void ElementAvgUnder(enum DIAG_DEVICE i);
	void ElementInRange(enum DIAG_DEVICE i);
	void ElementNoise(enum DIAG_DEVICE i);
	void ElementNoiseLower(enum DIAG_DEVICE i);
	void ElementNoiseGreater(enum DIAG_DEVICE i);
	void ElementAvgOver(enum DIAG_DEVICE i);
	void ElementProg(enum DIAG_DEVICE i);
	
	void SetLOnOffTime(uint8_t on, uint8_t off);
	
	void Run();

	CDiagNeopixel Neopixel;
	
	private:
	uint8_t m_LastDiagButtonState;
	uint8_t m_DiagButtonPushed;

	uint8_t m_ProgrammingMode; 		

	uint8_t m_LOnTime;
	uint8_t m_LOffTime;
	
	
	uint8_t m_LCnt;
	uint8_t m_LState;
	
};



#endif /* CDIAGNOSTIC_H_ */