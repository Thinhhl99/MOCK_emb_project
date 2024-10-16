#include"main.h"
#include"scg.h"
#include"pcc.h"
#define SCS_OFFSET 				(16u)
#define EREF_CRYSTAL 			(1<<3)
/*
FIRC -> SYSCLK 24Mhz
SIRC -> SYSCLK 1Mhz
SOSC -> SYSCLK 2Mhz
SPLL -> SYSCLK 40Mhz
*/
/*------------------- HOME WORK 13/11/2023 --------------------------*/
void firc_SYSCLK_24MHz(void){
	
	SCG->SCG_RCCR.FIELD.DIVCORE = 0x01;// divide by 2 ==> 48/2=24
	//SCG->SCG_RCCR.FIELD.SCS |= 0x11u;
}

void sirc_SYSCLK_1MHz(void){
	//SCG->SCG_SIRCCSR						= CLEAR_BIT_AT_OFFSET(SCG->SCG_SIRCCSR,23);
	
	SCG->SCG_SIRCCFG 							=		(0x1u);								// 0: 2MHz; 1: 8MHz
	SCG->SCG_SIRCCSR							= 	(0x1u);								// Slow IRC enable
	while(!(GET_BIT_AT_OFFSET(SCG->SCG_SIRCCSR,24)==1)){}
	SCG->SCG_RCCR.FIELD.SCS 			= 	0x2; 									// Slow IRC select
	SCG->SCG_RCCR.FIELD.DIVCORE 	= 	(0x7u);								// 0x7 (0b0111) divide by 8; 8/8= 1MHz
	

}

void sosc_SYSCLK_2MHz(void){
	// Crystal
	SCG->SCG_SOSCCFG.FIELD.EREFS	= 1u;												// 1 Internal crystal oscillator of OSC selected
  // MISSING SET GAIN, RANGE
	SCG->SCG_SOSCCFG.FIELD.HGO		= 1;
	SCG->SCG_SOSCCFG.FIELD.RANGE	= 0x3;											// RANGE : 11
	
	// MISSING CHECK LK BIT
	// if (CG->SCG_SOSCCSR & (0x1 << 23) == 0)
	SCG->SCG_SOSCCSR 							&=~(0x1u << 23);							// LK = 0 (Lock =0)
	SCG->SCG_SOSCCSR							= 	(0x1u);										// System OSC enable
		while(!(GET_BIT_AT_OFFSET(SCG->SCG_SOSCCSR,24)==1)){}
			
	/*--------*///check Lock SOSCCSR -> SOSCVLD co gia tri valid hay ko
	SCG->SCG_RCCR.FIELD.SCS				=	0x0001u; 	// System OSC select
	SCG->SCG_RCCR.FIELD.DIVCORE		= 	(0x3u);										// divide by 4; 8\4= 2MHz
}

void spll_SYSCLK_40MHz(void){
	SCG->SCG_SPLLCFG.FIELD.SOURCE =1u;
	/*prediv and mult at SPLLCFG*/
	SCG->SCG_SPLLCFG.FIELD.PREDIV = 0x5; // 48/6 = 8
	SCG->SCG_SPLLCFG.FIELD.MULT		= 0x4; // 8*20 = 80
	SCG->SCG_RCCR.FIELD.SCS				= 0x6; //select SPLL
	SCG->SCG_RCCR.FIELD.DIVCORE 	= 0x3; // 160/4= 40MHz
}
void spll_BUS_CLK_40MHz(void){
	SCG->SCG_FIRCCSR.FIELD.EN =0u;
	//default Range of Fast IRC is 48 MHZ
	SCG->SCG_FIRCDIV.FIELD.DIV2 = 0x3;
	SCG->SCG_FIRCCSR.FIELD.LK 	=	0u;
	SCG->SCG_FIRCCSR.FIELD.EN		= 1u;
	while(SCG->SCG_FIRCCSR.FIELD.VLD ==0){}
	SCG->SCG_RCCR.FIELD.SCS 		= 3u;
	SCG->SCG_RCCR.FIELD.DIVCORE = 0u;
	SCG->SCG_RCCR.FIELD.DIVBUS 	=	1u;			//BUS_CLK =24MHz;
	while(!(SCG->SCG_RCCR.REG == SCG->SCG_CSR)){}
} 
void firc_FIRCDIV2CLK_12MHz(void){
	SCG->SCG_FIRCCSR.FIELD.EN =0u;
	//default Range of Fast IRC is 48 MHZ
	SCG->SCG_FIRCDIV.FIELD.DIV2 = 0x3;
	SCG->SCG_FIRCCSR.FIELD.LK 	=	0u;
	SCG->SCG_FIRCCSR.FIELD.EN		= 1u;
	while(SCG->SCG_FIRCCSR.FIELD.VLD ==0){}
	SCG->SCG_RCCR.FIELD.SCS 		= 3u;
	SCG->SCG_RCCR.FIELD.DIVCORE = 0u;
	SCG->SCG_RCCR.FIELD.DIVBUS 	=	1u;			//BUS_CLK =24MHz;
	while(!(SCG->SCG_RCCR.REG == SCG->SCG_CSR)){}
}
void scg_spll_config(void){
	/* crystal */
	SCG->SCG_SOSCCFG.FIELD.EREFS =1u; 			/* Select Crystal */
	/* SET GAIN, RANGE, HGO */
	SCG->SCG_SOSCCFG.FIELD.HGO 		=1u;
	SCG->SCG_SOSCCFG.FIELD.RANGE	=2u;
	/* SET LK =0, and enable clock*/
	SCG->SCG_SOSCCSR							&=~(0x1u << 23); 	/* SET LK =0*/
	SCG->SCG_SOSCCSR							= 	0x1u; 				/* Enable Clock*/
	/* Wait: check Lock SOSCCSR -> SOSCVLD co gia tri valid hay ko*/
	while(!(GET_BIT_AT_OFFSET(SCG->SCG_SOSCCSR,24)==1)){}
	SCG->SCG_SPLLCFG.FIELD.SOURCE =	0u; 		/* select crystal source clock*/
	SCG->SCG_SPLLCFG.FIELD.PREDIV =	0u; 		/* Div by 1, 8 MHz*/
	SCG->SCG_SPLLCFG.FIELD.MULT 	=	2u; 		/* Multi for 18, 18*8= 144MHz, dau ra SPLL_CLK= 144/2= 72MHz*/
	SCG->SCG_SPLLDIV.FIELD.DIV2		=	3u;			/* SPLLDIV2= 72/4 = 18MHz*/
		
	SCG->SCG_SPLLCSR.FIELD.LK 		= 0u;
	SCG->SCG_SPLLCSR.FIELD.SPLLEN = 1u;
	
	//while(SCG->SCG_SPLLCSR.FIELD.SPLL_VLD ==0){}
	while(!(GET_BIT_AT_OFFSET(SCG->SCG_SPLLCSR.REG,24)==1)){}
	SCG->SCG_RCCR.FIELD.DIVSLOW		= 2u;			/* 2b:FLASH_CLK= 72/3=24(<26,6MHz)*/
	SCG->SCG_RCCR.FIELD.DIVCORE		= 0u;			/* 0b:Divcore by 1, CORE_CLK = 72MHz*/
	SCG->SCG_RCCR.FIELD.DIVBUS		= 1u;			/* 1b:Divbus by 2, 72/2=36, BUS_CLK =36MHz (<40MHz)*/
	SCG->SCG_RCCR.FIELD.SCS 			= 6u;			/* Select Spll for Divcore*/
	//SCG->SCG_RCCR.REG = 0x
	while(!(SCG->SCG_RCCR.REG == SCG->SCG_CSR)){}
}

/*------------------- HOME WORK 13/11/2023 --------------------------*/
//scg_sosc_config_t cfg = {scg_sosc_eref_cystal, scg_sosc_div_disable, scg_sosc_div_8};

void scg_sosc_config (scg_sosc_config_t sosc_config){
   // SCG->SOSCCFG.field.EREF = sosc_config.eref;
	SCG->SCG_SOSCCFG.FIELD.EREFS = sosc_config.eref = scg_sosc_eref_external_signal;
   // SCG->SOSCDIV.field.DIV1 = sosc_config.div1;
	
   // SCG->SOSCDIV.field.DIV2 = sosc_config.div2;
}
