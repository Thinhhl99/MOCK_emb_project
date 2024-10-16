#include<main.h>
#include<delay.h>
#include<systick.h>

#define CLOCK_FCORE 			(72 * 1000000)
#define RELOAD_Time				(0.001)						// 1000 times reload
#define RELOAD_VALUE 			(CLOCK_FCORE * RELOAD_Time)

void SysTick_Handler(void);
static volatile uint32_t delay_counter;
/*--------------------delay 01-----------------------*/
void delay(void /*unsigned int ms_second*/){
	for (int i=0; i<1000; i++){
			for (int j=0; j<1500; j++){}
	}
}
/*--------------------delay 02-----------------------*/
void delay_ms (unsigned int ms_second){
	SYSTICK->SYST_CSR.FIELD.ENABLE = BIT_SET; // BIT_SET = 0x1u
	SYSTICK->SYST_CSR.FIELD.TICKINT = BIT_SET;
	SYSTICK->SYST_RVR.FIELD.RELOAD = ((uint32_t) (RELOAD_VALUE -1));
	delay_counter = ms_second;
	while(delay_counter>0){}
	SYSTICK->SYST_CSR.FIELD.ENABLE =BIT_CLEAR;
}
void SysTick_Handler(void){
	if (delay_counter >0){
		delay_counter--;
	}
}



