#include "lpit.h"
#include "main.h"

void LPIT_init(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;
	PCC->PCC_LPIT.FIELD.PCS=3u; //fircdiv2
	PCC->PCC_LPIT.FIELD.CGC=1u; //
	
	LPIT->MCR.FIELD.M_CEN =1;
	LPIT->MCR.FIELD.DBG_EN=1;
	
	LPIT->TCTRL0.FIELD.MODE =0u;
	LPIT->TVAL0.REG = 0XFFFFFFFF;
	LPIT->TCTRL0.FIELD.T_EN =1u;
}
void LPIT_init_MOCK(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;	//disable clock
	PCC->PCC_LPIT.FIELD.PCS=6u; //splldiv2_select
	PCC->PCC_LPIT.FIELD.CGC=1u; //enable clock
	
	LPIT->MCR.FIELD.M_CEN 	=1;		/* 1b - Enable peripheral clock to timers*/
	LPIT->MCR.FIELD.DBG_EN	=1;		/* DBG_EN-0: Timer chans stop in Debug mode */
	LPIT->MIER.FIELD.TIE0 	=1;		/* Channel 0 Timer Interrupt Enable*/
	//LPIT->MIER.FIELD.TIE1 	=1;		/* Channel 1 Timer Interrupt Enable*/
	LPIT->TCTRL0.FIELD.MODE =0u;	/* 32 bit Periodic Counter*/
	//LPIT->TCTRL1.FIELD.MODE =0u;	/* 32 bit Periodic Counter*/
	LPIT->TVAL0.REG	= 9000000;		/*0.5s*/
	//LPIT->TVAL1.REG	= 9000000;
	
}
void LPIT_init_HW01(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;	//disable clock
	PCC->PCC_LPIT.FIELD.PCS=3u; //fircdiv2
	PCC->PCC_LPIT.FIELD.CGC=1u; //enable clock
	/*---- LPIT ----*/
	LPIT->MCR.FIELD.M_CEN 	=1;		/*1b - Enable peripheral clock to timers*/
	LPIT->MCR.FIELD.DBG_EN	=0;		/* DBG_EN-0: Timer chans stop in Debug mode */
	//LPIT->MIER.FIELD.TIE0 	=1;		/* Channel 0 Timer Interrupt Enable*/
	
	LPIT->TCTRL0.FIELD.MODE 	=	0u;//00b - 32-bit Periodic Counter
	LPIT->TVAL0.FIELD.TMR_VAL	= 12000000;/* Chan 0 Timeout period: 12M clocks */ // thuc hien 1s
	LPIT->TCTRL0.FIELD.T_EN		=	1u;
}
void LPIT_init_HW03(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;	//disable clock
	PCC->PCC_LPIT.FIELD.PCS=3u; //fircdiv2
	PCC->PCC_LPIT.FIELD.CGC=1u; //enable clock
	/*---- LPIT ----*/
	
	LPIT->MIER.FIELD.TIE0 	=1; 					/*Channel 0 Timer Interrupt Enable*/
	LPIT->MCR.FIELD.M_CEN 	=1;						/* 1b - Enable peripheral clock to timers*/
	LPIT->MCR.FIELD.DBG_EN	=0;						/* DBG_EN-0: Timer chans stop in Debug mode */
	LPIT->TCTRL0.FIELD.MODE =1u;  				/* 01b - Dual 16-bit Periodic Counter*/
	LPIT->TVAL0.FIELD.TMR_VAL	=0xea60ea60;/* chon 60000*2*100=12M (thuc hien 1s)*/
	LPIT->TCTRL0.FIELD.T_EN		=	1u;				/*1b - Timer Channel is enabled*/
}
void LPIT_init_HW04(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;	//disable clock
	PCC->PCC_LPIT.FIELD.PCS=3u; //fircdiv2
	PCC->PCC_LPIT.FIELD.CGC=1u; //enable clock
	
	LPIT->MIER.FIELD.TIE0 	=1; //Channel 0 Timer Interrupt Enable
	LPIT->MCR.FIELD.M_CEN 	=1;		/* 1b - Enable peripheral clock to timers*/
	LPIT->MCR.FIELD.DBG_EN	=1;		/* DBG_EN-0: Timer chans stop in Debug mode */
	LPIT->TCTRL0.FIELD.MODE	=0;		//00b - 32-bit Periodic Counter
	LPIT->TVAL0.FIELD.TMR_VAL= 12000000;
}
void LPIT_init_HW05(void){
	PCC->PCC_LPIT.FIELD.CGC=0u;	//disable clock
	PCC->PCC_LPIT.FIELD.PCS=3u; //fircdiv2
	PCC->PCC_LPIT.FIELD.CGC=1u; //enable clock
	
	//LPIT->MIER.FIELD.TIE1 	=1;
	LPIT->MCR.FIELD.M_CEN 	=1;		/* 1b - Enable peripheral clock to timers*/
	LPIT->MCR.FIELD.DBG_EN	=1;		/* DBG_EN-0: Timer chans stop in Debug mode */
	
	/*---- Set up Channel 1 ----*/
	LPIT->TCTRL1.FIELD.MODE		=0;		//00b - 32-bit Periodic Counter
	LPIT->TVAL1.FIELD.TMR_VAL	= 5999999;
	/*---- Set up Channel 2 ----*/
	LPIT->TCTRL2.FIELD.MODE 	=	0;	//00b - 32-bit Periodic Counter
	LPIT->TVAL2.FIELD.TMR_VAL	= 2;
	LPIT->TCTRL2.FIELD.CHAIN 	=	1;//1b - Channel Chaining is enabled. The timer decrements on the previous channel's timeout.
	
}

