#ifndef __S32K144_SYSTICK_H__
#define __S32K144_SYSTICK_H__

#include <stdint.h>
#include "common.h"

typedef union{
	uint32_t REG;
	struct {
		RW uint32_t 	ENABLE		: 		1;
		RW uint32_t 	TICKINT		: 		1;
		RW uint32_t 	CLKSOURCE	:			1;
		RO uint32_t 	RES01			: 		13;
		RW uint32_t 	COUNTLAG	: 		1;
	  RO uint32_t 	RES02			:			15;
	} FIELD; 				//SysTick Control and Status Register, SYST_CSR, ARMv7-M Arch... page 621 	
} SYST_CSR_REG_t;
/*--------------------------------------------------------*/

typedef union{
	uint32_t REG;
	struct {
		RW uint32_t 	RELOAD		: 			24;	
		RO uint32_t 	RES01			: 			8;
	} FIELD; 				//SysTick Reload Value Register, SYST_RVR on page B3-622	
} SYST_RVR_REG_t;
/*--------------------------------------------------------*/

typedef union{
	uint32_t REG;
	struct {
		RW uint32_t 	CURRENT		: 			32;	
	} FIELD; 				//SysTick Current Value Register, SYST_CVR on page B3-622
} SYST_CVR_REG_t;
/*--------------------------------------------------------*/

typedef union{
	uint32_t REG;
	struct {
		RW 	uint32_t 	TENMS			: 		24;
		RO	uint32_t 	RES01			: 		6;
		RW 	uint32_t 	SKEW			: 		1;
		RW 	uint32_t 	NOREF			: 		1;
	} FIELD; 				//SysTick Calibration value Register, SYST_CALIB on page B3-623
} SYST_CALIB_REG_t;
/*--------------------------------------------------------*/

typedef struct {
	IO RW 	SYST_CSR_REG_t			SYST_CSR;		//SysTick Control and Status Register
	IO RW 	SYST_RVR_REG_t			SYST_RVR;		//SysTick Reload Value Register
	IO RW 	SYST_CVR_REG_t			SYST_CVR;		//SysTick Current Value Register
	IO RO 	SYST_CALIB_REG_t		SYST_CALIB;	//SysTick Calibration value Register
}SYSTICK_t;

#define SYSTICK_BASE 					(0xE000E010)
#define SYSTICK								((SYSTICK_t *) SYSTICK_BASE)
#endif // systick.h
