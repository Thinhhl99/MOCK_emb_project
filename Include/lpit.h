#ifndef __S32K144_LPIT_H__
#define __S32K144_LPIT_H__
#include <stdint.h>
#include "common.h"

typedef union{
	uint32_t REG;
	struct{
		RO uint32_t FEATURE	:			16;
		RO uint32_t MINOR		:			8;
		RO uint32_t MAJOR		:			8;
	}FIELD;
}VERIG_REG_t;
	
typedef union {
	uint32_t REG;
	struct {
		RO uint32_t CHANNEL		:			8;
		RO uint32_t EXT_TRIG	:			8;
		RO uint32_t RES0			:			16;
	}FIELD;
}PARAM_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t M_CEN			:			1;
		RW uint32_t SW_RST		:			1;
		RW uint32_t DOZE_EN		:			1;
		RW uint32_t DBG_EN		:			1;
		RO uint32_t RES0			:			28;
	}FIELD;
}MCR_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t TIF0		:			1;
		RW uint32_t TIF1		:			1;
		RW uint32_t TIF2		:			1;
		RW uint32_t TIF3		:			1;
		RO uint32_t RES0		:			28;
	}FIELD;
}MSR_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t TIE0		:			1;
		RW uint32_t TIE1		:			1;
		RW uint32_t TIE2		:			1;
		RW uint32_t TIE3		:			1;
		RO uint32_t RES0		:			28;
	}FIELD;
}MIER_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t SET_T_EN_0		:			1;
		RW uint32_t SET_T_EN_1		:			1;
		RW uint32_t SET_T_EN_2		:			1;
		RW uint32_t SET_T_EN_3		:			1;
		RO uint32_t RES0					:			28;
	}FIELD;
}SETTEN_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t CLR_T_EN_0		:			1;
		RW uint32_t CLR_T_EN_1		:			1;
		RW uint32_t CLR_T_EN_2		:			1;
		RW uint32_t CLR_T_EN_3		:			1;
		RO uint32_t RES0					:			28;
	}FIELD;
}CLRTEN_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t TMR_VAL	:			32;
	}FIELD;
}TVAL_n_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RO uint32_t TMR_CUR_VAL	:			32;
	}FIELD;
}CVAL_n_REG_t;

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t T_EN		:			1;
		RW uint32_t CHAIN		: 		1;
		RW uint32_t MODE	  : 		2;
		RO uint32_t RES0	  :			12;
		RW uint32_t TSOT		:			1;
		RW uint32_t TSOI		:			1;
		RW uint32_t TROT		:			1;
		RO uint32_t RES1	  :			4;	
		RW uint32_t TRG_SRC	:			1;
		RW uint32_t TRG_SEL	:			4;
		RO uint32_t RES2	  :			4;
	}FIELD;
}TCTRL_n_REG_t;
typedef struct{
	IO VERIG_REG_t			VERID;			//Version ID Register (VERID)
	IO PARAM_REG_t			PARAM;			//Parameter Register (PARAM)
	IO MCR_REG_t		 	  MCR;				//Module Control Register (MCR)
	IO MSR_REG_t		 		MSR;				//Module Status Register (MSR)
	IO MIER_REG_t 	 		MIER;				//Module Interrupt Enable Register (MIER)
	IO SETTEN_REG_t			SETTEN;			//Set Timer Enable Register (SETTEN)
	IO CLRTEN_REG_t 	 	CLRTEN;			//Clear Timer Enable Register (CLRTEN)
	
	IO RO uint32_t	 RES01[1];
	IO TVAL_n_REG_t	 TVAL0;			//Timer Value Register (TVAL0)
	IO CVAL_n_REG_t	 CVAL0;			//Current Timer Value (CVAL0)
	IO TCTRL_n_REG_t TCTRL0;		//Timer Control Register (TCTRL0)
	
	IO RO uint32_t	 RES02[1];
	IO TVAL_n_REG_t	 TVAL1;			//Timer Value Register (TVAL1)
	IO CVAL_n_REG_t	 CVAL1;			//Current Timer Value (CVAL1)
	IO TCTRL_n_REG_t TCTRL1;		//Timer Control Register (TCTRL1)
	
	IO RO uint32_t	 RES03[1];
	IO TVAL_n_REG_t	 TVAL2;			//Timer Value Register (TVAL2)
	IO CVAL_n_REG_t	 CVAL2;			//Current Timer Value (CVAL2)
	IO TCTRL_n_REG_t TCTRL2;		//Timer Control Register (TCTRL2)
	
	IO RO uint32_t	 RES04[1];
	IO TVAL_n_REG_t	 TVAL3;			//Timer Value Register (TVAL3)
	IO CVAL_n_REG_t	 CVAL3;			//Current Timer Value (CVAL3)
	IO TCTRL_n_REG_t TCTRL3;		//Timer Control Register (TCTRL3)
}LPIT_t;
#define LPIT_BASE				(0x40037000)
#define LPIT						((LPIT_t*) LPIT_BASE)

/*-------------------------------------------------------------*/
void LPIT_init(void);
void LPIT_init_HW01(void);
void LPIT_init_HW03(void);
void LPIT_init_HW04(void);
void LPIT_init_HW05(void);
void LPIT_init_MOCK(void);
#endif /*LPIT.h*/
