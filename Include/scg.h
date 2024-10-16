#ifndef __S32K144_SCG_H__
#define __S32K144_SCG_H__

#include <stdint.h>
#include "common.h"
typedef union{
	uint32_t REG;
	struct{
		RO uint32_t 	RES01		: 2;
		RW uint32_t 	EREFS		: 1;
		RW uint32_t 	HGO			: 1;
		RW uint32_t 	RANGE 	: 2;
		RO uint32_t 	RES02 	: 26;
	}FIELD;
}SCG_SOSCCFG_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t DIVSLOW :	4;
		RW uint32_t DIVBUS	:	4;
		RO uint32_t RES01		:	8;
		RW uint32_t DIVCORE :	4;
		RO uint32_t RES02		:	4;
		RW uint32_t SCS			:	4;
		RO uint32_t RES03		:	4;
	}FIELD;
}SCG_xCCR_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t SOURCE	: 1;
		RO uint32_t RES01		:	7;
		RW uint32_t PREDIV	: 3;
		RO uint32_t RES02		:	5;
		RW uint32_t MULT 		: 5;
		RO uint32_t RES03		:	11;
		
	}FIELD;
}SCG_SPLLCFG_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t EN   : 1;
		RW uint32_t RES0 : 2;
		RW uint32_t REGOFF : 1;
		RO uint32_t RES1 : 19;
		RW uint32_t LK   : 1;
		RO uint32_t VLD  : 1;
		RO uint32_t SEL  : 1;
		RO uint32_t ERR  : 1;
		RO uint32_t RES2 : 5;
	}FIELD;
}SCG_FIRCCSR_REG_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t DIV1 : 3;
		DM uint32_t RES0 : 5;
		RW uint32_t DIV2 : 3;
		DM uint32_t RES1 : 21;
	}FIELD;
}S32K144_SCG_DIV_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t SPLLEN   	: 1;
		RW uint32_t RES0 			: 1;
		RW uint32_t RES1 			: 14;
		RW uint32_t SPLLCM   	: 1;
		RW uint32_t SPLLCMRE  : 1;
		RW uint32_t RES2 			: 5;
		RW uint32_t LK   			: 1;
		RO uint32_t SPLL_VLD  : 1;
		RO uint32_t SPLL_SEL  : 1;
		RO uint32_t SPLL_ERR  : 1;
		RO uint32_t RES3 			: 5;
	}FIELD;
}SCG_SPLLCSR_t;
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
typedef struct{
	IO 	RO uint32_t SCG_VERID;			//Version ID Register (SCG_VERID)
	IO 	RO uint32_t SCG_PARAM;			//Parameter Register (SCG_PARAM)
	IO  RO uint32_t RES00[2];
	IO 	RO uint32_t SCG_CSR;				//Clock Status Register (SCG_CSR)
	
	IO 	RW SCG_xCCR_t SCG_RCCR;				//Run Clock Control Register (SCG_RCCR)
	IO 	RW SCG_xCCR_t SCG_VCCR;				//VLPR Clock Control Register (SCG_VCCR)
	IO 	RW SCG_xCCR_t SCG_HCCR;				//HSRUN Clock Control Register (SCG_HCCR)
	IO 	RW uint32_t SCG_CLKOUTCNFG;	//SCG CLKOUT Configuration Register(SCG_CLKOUTCNFG)
	
			RO uint32_t RES01[55];	
	IO 	RW uint32_t SCG_SOSCCSR;		//System OSC Control Status Register (SCG_SOSCCSR)
	IO 	RW uint32_t SCG_SOSCDIV;		//System OSC Divide Register (SCG_SOSCDIV)
	IO 	RW SCG_SOSCCFG_t SCG_SOSCCFG;		//System Oscillator Configuration Register (SCG_SOSCCFG)
	
			RO uint32_t RES02[61];	
	IO 	RW uint32_t SCG_SIRCCSR;		//Slow IRC Control Status Register (SCG_SIRCCSR)
	IO 	RW uint32_t SCG_SIRCDIV;		//Slow IRC Divide Register (SCG_SIRCDIV)
	IO 	RW uint32_t SCG_SIRCCFG;		//Slow IRC Configuration Register (SCG_SIRCCFG)
	
			RO uint32_t RES03[61];	
	IO 	RW SCG_FIRCCSR_REG_t SCG_FIRCCSR;		//Fast IRC Control Status Register (SCG_FIRCCSR)
	IO 	RW S32K144_SCG_DIV_t SCG_FIRCDIV;		//Fast IRC Divide Register (SCG_FIRCDIV)
	IO 	RW uint32_t SCG_FIRCCFG;		//Slow IRC Configuration Register (SCG_SIRCCFG)
	
			RO uint32_t RES04[189];	
	IO 	RW SCG_SPLLCSR_t SCG_SPLLCSR;		//System PLL Control Status Register (SCG_SPLLCSR)
	IO 	RW S32K144_SCG_DIV_t SCG_SPLLDIV;		//System PLL Divide Register (SCG_SPLLDIV)
	IO 	RW SCG_SPLLCFG_t 		 SCG_SPLLCFG;		//System PLL Configuration Register (SCG_SPLLCFG)
	
}SCG_t;
#define SCG_BASE 				(0x40064000)
#define SCG							((SCG_t *) SCG_BASE)

/*---------------------------------------------------------------------------------------*/

typedef enum {//scg_sosc_eref
    scg_sosc_eref_external_signal = 0,
    scg_sosc_eref_cystal 					= 1
}scg_eref_t;

typedef enum scg_sosc_div{
    scg_sosc_div_disable,// 000
    scg_sosc_div_1			,// 001
    scg_sosc_div_2			,// 010
    scg_sosc_div_4			,// 011
    scg_sosc_div_8			,// 100
    scg_sosc_div_16			,// 101
    scg_sosc_div_32			,// 110
    scg_sosc_div_64			 // 111
}scg_div_t;

typedef struct{
    //scg_eref_t eref_bit;
	scg_eref_t eref;	
    //scg_div_t div1, div2;
	scg_div_t div01, div02;
}scg_sosc_config_t;


void scg_sosc_config (scg_sosc_config_t sosc_config);

//scg_sosc_config(cfg);
/*---------------------------------------------------------------------------------------*/
void firc_SYSCLK_24MHz(void);
void sirc_SYSCLK_1MHz(void);
void sosc_SYSCLK_2MHz(void);
void spll_SYSCLK_40MHz(void);
void spll_BUS_CLK_40MHz(void);
void firc_FIRCDIV2CLK_12MHz(void);
void scg_spll_config(void);
#endif /*SCG.h*/
