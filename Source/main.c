/*
Name: 		Le Huu Thinh
Exercise_MOCK:  MOCK MCP MODULE
Des: 
*Hardware:
	+ 2 buttons (SW2 and SW3 onboard) + 1 LED + 1 USB UART CP2102
	+ 8-digit seven-segment LED display

*Write program:
	Write program: The Digital Clock
	SRS 1: Clock core 72MHz from clock source crystal 8MHz
	SRS 2: Setting for LPUART1. Pin PTC6, Pin PTC7
	SRS 2-1: Baud rate: 38400, 8-bits data, even parity, 1-bit stop.
	SRS 2-2: UART clock is SPLL Div2
	SRS 3: Setting for SPI using Pin E0, Pin E1, Pin E2, Pin E6
	SRS 4: After power on, display the time: 18-00-00 (date: 01.01.1991), the LED Green status
	is OFF
	SRS 5: Setting date, time, alarm by UART1 serial communication.
	SRS 6: Select mode display via the button
	Press Button 1
	SRS 6-1: Display the date
	SRS 6-2: Display the time
	SRS 6-3: Display the alarm
	Press Button 2
	Decrease bright of LED 7 SEG which 5 level from maximum to off the Led
	SRS 7: When alarm occurred, the LED Green blink with period 0.5 (s) in alarm time 10 (s). In
	alarm time, if pressed any button, the LED Green is OFF immediately.
*/
	
/* <------------------- MO TA CAC BUOC THUC HIEN ------------------------->
SRS 1: Clock core 72MHz from clock source crystal 8MHz:
**** Setting SCG following to required of SRS 1 ****
- Use PLL to have multiplier ==> 8 MHz(crystal)*18 (multi) =144, 
==> Create: CORE_CLK = 144/2= 72MHz, BUS_CLK= CORE_CLK/2=36MHz,FLASH_CLK= 72/3=24MHz and SPLL_DIV2=72/4=18MHz.

SRS 2 and SRS 4: Setting for LPUART1:
-	Setting LPUART1 following to required of SRS 2 and SRS 4.
- SRS 2-1: Baud rate: 38400, 8-bits data, even parity, 1-bit stop.
- SRS 2-2: UART clock is SPLL Div2.
- SBR=26 (0x1a): baud divisor = 18M/38400/18 =~26. (select SPLL_CKL= 18MHz)
- OSR=17 (0x11): Over sampling ratio = 17+1=18.

SRS 3: Setting for SPI using Pin E0, Pin E1, Pin E2, Pin E6:
- Mentioned in main(void)

SRS 5: Setting date, time, alarm by UART1 serial communication.
****************************************************************************************************
****************************************************************************************************
- **** Instructions for users (LPUART)****					----						**** Instructions for users (LPUART)****				

------ Setting Date _e.g: D20.12.2023
------ Setting Time _e.g: T18.25.21
------ Setting Alarm_e.g: A10.30.00

!!!Note: - If Wrong Format, will not process received string from UART.
****************************************************************************************************
****************************************************************************************************

SRS 6: Select mode display via the button: 
- Mentioned in PORTC_IRQHandler()
**Press Button 1:
- Switch 1(PORTC_PIN 12): Use a variable has name is (static)uint32_t state_day_or_hour to manage DISPLAY MODE
-- when press 1 time: state_day_or_time = (state_day_or_time+1)%3 ==> 0: display TIME; 1: display DATE; 2:display ALARM
**Press Button 2:
- Switch 2(PORTC_PIN 13): Use to decrease bright of LED 7 SEG which 5 level from maximum to off the Led
- Use uint32_t intensity_val to manage INTENSITY of Led
-- when press 1 time: intensity_val = (intensity_val+1)%5 ==> 4: turn off led all

SRS 7: When alarm occurred, the LED Green blink with period 0.5 (s) in alarm time 10 (s). In
 alarm time, if pressed any button, the LED Green is OFF immediately.
 - Use a uint8_t wakwup_alarm : when alarm occurred (wakeup_alarm =1) and if press any switch, wakeup_alarm =0 and 
 the LED Green is OFF immediately. (mentioned in PORTC_IRQHandler())
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "port.h"
#include "gpio.h"
#include "pcc.h"
#include "common.h"
#include "nvic.h"
#include "delay.h"
#include "systick.h"
#include "scg.h"
#include "lpuart.h"
#include "lpit.h"
#include "lpspi.h"
/******************* PORT USE ********************/
//#define PORT_USE	6
//#define HW_TIMER 	0
#define ASM_MINI_PRO 1
/******************* PORT USE ********************/

#define GET_BIT_AT_OFFSET(reg,offset) (((reg)>>(offset))&1)
#define SET_BIT_AT_OFFSET(reg, offset) ((reg)|(1<<(offset)))
#define GET_VALUE_AT_OFFSET(reg, offset) (((reg)>>(offset)) & 1u)
#define LED_BLUE  (1<<0)   	// PTD0
#define LED_RED   (1<<15)  	// PTD15
#define LED_GREEN (1<<16)  	// PTD16
#define SW2      	(1<<12)   // PTC12
#define SW3      	(1<<13)   // PTC13
#define LED_ON		"LEDON"
#define LED_OFF		"LEDOFF"

/*-------------------------------------------- FUNCTION PROCESS -----------------------------------------*/

void PORTA_IRQHandler(void);
void PORTB_IRQHandler(void);
void PORTC_IRQHandler(void);
void PORTD_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void PORT_init(void);
void PORT_init_LPSPI(void);
void WDOG_disable(void);
void PORT_C_switch_PIN12_13(void);
void LPSPI_init(void);
void PORT_D_GREEN_LED(void);
void process_Normal_state(void);
void process_NOT_Normal_state(void);
uint8_t isLeapYear(uint16_t year_pro); 
void process_UART(uint8_t state_var);

static volatile uint32_t state_day_or_hour =0;  /*0b: hour-minute-second*/
static volatile uint32_t normal_state=1;
/* Declare Variable*/
	static volatile uint8_t second=0;
	static volatile uint8_t minute=0;
	static volatile uint8_t hour=18;
	static volatile uint8_t day=1;
	static volatile uint8_t month =1;
	static volatile uint16_t year =1991;
	/* Alarm:*/	
	static volatile uint8_t second_alarm =5;
	static volatile uint8_t minute_alarm =0;
	static volatile uint8_t hour_alarm =0;
	static volatile uint8_t wakeup_alarm=0;				/* Turn off alarm*/
	/* Adjust*/
	
	/*--------------------------------*/
	static volatile uint8_t daysInMonth;
	static volatile char rxBuffer[255]; 					/* Array chua chuoi ki tu duoc gui ve tu UART */
	static volatile uint8_t rxIndex = 0;
	static volatile uint8_t Comlete_display =0;
	static volatile uint8_t intensity_val=4;
	static volatile uint8_t LPIT_timer_count=0;
	static volatile uint32_t char_count=0;
	
int main(void) {
	/* Setting for INTERRUPT*/
	nvic_enable_interrupt(IRQn_PORTC);
	nvic_enable_interrupt(IRQn_LPUART1_RxTx);	
	nvic_enable_interrupt(IRQn_LPIT0_Ch0);
	/*----------- Setting for SCG -------------*/
	scg_spll_config();
	/*-----------------------------------------*/
	PORT_init();							/* Setting for LPUART1. Pin PTC6, Pin PTC7*/
	PORT_init_LPSPI();				/* Setting for SPI using Pin E0, Pin E1, Pin E2, Pin E6*/
	PORT_D_GREEN_LED(); 			/* Setting for the LED Green status is OFF*/
	LPSPI_init();							/* Setting for LPSPI0*/
	LPUART1_init_MOCK();			/* Setting for LPUART1. SRS 2-1: Baud rate: 38400, 8-bits data, even parity, 1-bit stop.*/
	LPIT_init_MOCK();					/* Setting for LPIT. Create a time counter for ALARM, blink 0,5s  */		
	
	PORT_C_switch_PIN12_13();
	
	/*------------ Setting LPSPI --------------*/
	LPSPI0_transmit_mode_16bits(0xc, 0x01);	 /* Shutdown mode: 1b: Normal Operation*/
	
	LPSPI0_transmit_mode_16bits(0xb, 0x07);	 /* Scan Limit mode:  Display digits 0 1 2 3 4 5 6 7 */
	
	LPSPI0_transmit_mode_16bits(0x9, 0x00);	 /* No Decode Mode: Code B decode for digits 7->0*/
	
	LPSPI0_transmit_mode_16bits(0xa, 0x0f);  /* Intensity: Do sang full*/
	
	LPSPI0_transmit_mode_16bits(0xf, 0x00);	 /* Display Test: led 7 doan o dang not bright*/
	
	/* Setting date, time, alarm by UART1 serial communication.*/
	LPUART1_transmit_string("Instructions for users\r\n");
	LPUART1_transmit_string("Setting Date 	_e.g: D20.12.2023\r\n");
	LPUART1_transmit_string("Setting Time 	_e.g: T18.25.21\r\n");
	LPUART1_transmit_string("Setting Alarm	_e.g: A10.30.00\r\n");
	
	while(1){
		/*******************************************************************/
		/**********vvvv************ PROCESS UART ********vvvv***************/
		uint8_t state_var=0;
		process_UART(state_var);
			
		/*---------^^^^--------------- End UART ---------^^^^---------------*/
			
		/*********vvvv****** DISPLAY: DATE-TIME-ALARM *****vvvv**************/
		/********************************************************************/
		/* !!!Note: normal_state ==1, LED_SPI is in turn off led mode and avoid display mode (turn on led mode)*/
		if(state_day_or_hour  ==0 && normal_state ==1){ 									/* hour-minute-second*/
			LPSPI0_hour_m_s(hour, minute, second);
		}
		else if(state_day_or_hour ==1 && normal_state ==1)	{						  /* day.month.year*/
			LPSPI0_year_m_d(day, month, year);
		}else if(state_day_or_hour ==2 && normal_state ==1){
			LPSPI0_hour_m_s(hour_alarm, minute_alarm, second_alarm);				/* ALARM: hour-minute-second*/
		}	
		/*******************************************************************/	
		/************************* PROCESS_LED_SPI *************************/	
	
		process_Normal_state();							/* Process_led: day->month->year; second->minute->hour*/
		
		/*******************************************************************/		
																				/* Chay nhu binh thuong*/
		if(second_alarm == second && minute_alarm== minute && hour_alarm == hour){
				wakeup_alarm=0;									/* Reset wakeup_alarm to 0*/
				LPIT->TCTRL0.FIELD.T_EN =1u;		/* Enable LPIT, start count on 0*/
			}else{}
		delay_ms(1000);											/* SysTick: Use CORE_CLK to create delay 1s*/																		
			
	}
}	
/*------------------------------------- END MAIN() -------------------------------------*/
/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
void PORT_init(void){
	PCC->PCC_PORTC.FIELD.CGC =1u;				/* Enable clock for PORTC */
	PORT_C->PORT_PCR[6].FIELD.MUX =2u;	/* Port C6: MUX = ALT2,UART1 TX */
	PORT_C->PORT_PCR[7].FIELD.MUX =2u;	/* Port C7: MUX = ALT2,UART1 RX */
}
void WDOG_disable(void){
}
/*------------------------------------------------------------------------------*/
void PORT_D_GREEN_LED(void){
	PCC->PCC_PORTD.FIELD.CGC =1u;
	PORT_D->PORT_PCR[16].FIELD.MUX=1u;
	GPIO_D->PDDR.FIELD.P16 =1u;
	GPIO_D->PSOR.FIELD.P16 =1u;
}
/*------------------------------------------------------------------------------*/
void LPUART1_RxTx_IRQHandler(void){
	
	char receive;
	receive = LPUART1_receive_char();
	rxBuffer[rxIndex]= receive;
	rxIndex++;	
}
/*------------------------------------------------------------------------------*/
void LPIT0_Ch0_IRQHandler(void){
	/**/
	while(LPIT->MSR.FIELD.TIF0 == 0){}
		LPIT->MSR.FIELD.TIF0=1;
	if(second_alarm == second && minute_alarm== minute && hour_alarm == hour){
		LPIT_timer_count=1;
	}
	if(LPIT_timer_count>=1 && LPIT_timer_count<=20){
		GPIO_D->PTOR.FIELD.P16=1;
		LPIT_timer_count++;
		if(wakeup_alarm==1){
			GPIO_D->PSOR.FIELD.P16 =1;
			LPIT->TCTRL0.FIELD.T_EN		=	0u;
			LPIT_timer_count=0;
		}
	}else{}
		
	if(LPIT_timer_count==21){
		GPIO_D->PSOR.FIELD.P16 =1;
		LPIT->TCTRL0.FIELD.T_EN		=	0u;
		LPIT_timer_count=0;
		}	
		
	
} 
/*------------------------------------------------------------------------------*/
void PORTC_IRQHandler(void){
	if(PORT_C->PORT_PCR[12].FIELD.ISF ==1){
		wakeup_alarm =1;
		state_day_or_hour=(state_day_or_hour+1)%3;
		PORT_C->PORT_PCR[12].FIELD.ISF=1;
	}
	if(PORT_C->PORT_PCR[13].FIELD.ISF ==1){
		wakeup_alarm=1;
		intensity_val =(intensity_val+1)%5;
		if(intensity_val ==3){
			normal_state =0;
			Comlete_display=1;
		}
		else if(intensity_val ==4){
			if(Comlete_display==1){
					if(state_day_or_hour  ==0){ 																			/* hour-minute-second*/
						LPSPI0_hour_m_s(hour, minute, second);
					}
					else if(state_day_or_hour ==1)	{						  										/* day.month.year*/
						LPSPI0_year_m_d(day, month, year);
					}
					else if(state_day_or_hour ==2){
						LPSPI0_hour_m_s(hour_alarm, minute_alarm, second_alarm);				/* ALARM: hour-minute-second*/
					}else{}	
					Comlete_display=0;
					normal_state=1;
			}else{}
		}
		else{
			normal_state=1;
		}
		/************************* Intensity_led ****************************/
		LPSPI0_Intensity_led(intensity_val);
		PORT_C->PORT_PCR[13].FIELD.ISF=1;
	}
}
/*------------------------------------------------------------------------------*/
void PORT_C_switch_PIN12_13(void){
	
	PCC->PCC_PORTC.FIELD.CGC=1;
	PORT_C->PORT_PCR[12].FIELD.MUX=1;
	PORT_C->PORT_PCR[13].FIELD.MUX=1;
	GPIO_D->PDDR.FIELD.P12=0;
	GPIO_D->PDDR.FIELD.P13=0;
	PORT_C->PORT_PCR[12].FIELD.IRQC=9u;
	PORT_C->PORT_PCR[13].FIELD.IRQC=9u;
}
/*------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
void PORT_init_LPSPI(void){
	PCC->PCC_PORTE.FIELD.CGC=1u;			/* Enable clock for PORTE */

	PORT_E->PORT_PCR[0].FIELD.MUX=2u; 	/* Port E0: MUX = ALT2, LPSPI1_SCK */
	PORT_E->PORT_PCR[1].FIELD.MUX=2u;  	/* Port E1: MUX = ALT2, LPSPI1_SIN */
	PORT_E->PORT_PCR[2].FIELD.MUX=2u;  	/* Port E2: MUX = ALT2, LPSPI1_SOUT */
	PORT_E->PORT_PCR[6].FIELD.MUX=2u; 	/* Port E6: MUX = ALT2, LPSPI1_PCS2 */
}
/*------------------------------------------------------------------------------*/
uint8_t isLeapYear(uint16_t year_pro){																/* Setting - LeapYear*/
	return (year_pro % 400 == 0) || ((year_pro % 100 != 0) && (year_pro % 4 == 0));
}
/*------------------------------------------------------------------------------*/
void process_Normal_state(void){
	second++;
				 if(second == 60) {
							 minute += 1;
							 second = 0;
					 }else{}
				 if(minute == 60) {
							 hour += 1;
							 minute = 0;
					 }else{} 
				 if(hour == 24) {
							 day++;
							 hour = 0;
							 minute = 0;
							 second = 0;
					 }else{}
				/*---- LeapYear -----*/
					if (month == 2) {
            daysInMonth = isLeapYear(year) ? 29 : 28;
					} else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
					} else {
            daysInMonth = 31;
					}
					if (day > daysInMonth) {
            day = 1;
            month++;      
						if (month > 12) {
								month = 1;
								year++;
								}
          }
}
void process_NOT_Normal_state(void){
	second++;
	if(second == 60) {
							 minute += 1;
							 second = 0;
					 }else{}
				 if(minute == 60) {
							 hour += 1;
							 minute = 0;
					 }else{} 
				 if(hour == 24) {
							 day++;
							 hour = 0;
							 minute = 0;
							 second = 0;
					 }else{}
							
        if (month == 2) {
            daysInMonth = isLeapYear(year) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }
				
        if (day > daysInMonth) {
            day = 1;
            month++;      
						if (month > 12) {
								month = 1;
								year++;
								}
        }
}
void process_UART(uint8_t state_var){
	if(LPUART1->STAT.FIELD.IDLE ==1){
				LPUART1->STAT.FIELD.IDLE =1;
				for(volatile uint32_t i =0; i <= (sizeof(rxBuffer)); i++){
					if((rxBuffer[i] !='A') && (rxBuffer[i] != 'D') && (rxBuffer[i] != 'T') && (rxBuffer[i] != '.') && (rxBuffer[i]< '0') && (rxBuffer[i] >'9') ) {
						//LPUART1_transmit_string("Wrong format\r\n");
						rxIndex =0;
						memset(rxBuffer, 0, sizeof(rxBuffer));					
						state_var =1; 						/* Don't need to set next step */
						break;
					}
				}
				/*---- Next setting with state_var==0 ----*/
				if(state_var ==0){
					
				char char_01, char_02, char_03, char_04=0;
				uint32_t num01, num02, num03;				
				int result = sscanf(rxBuffer, "%c%d%c%d%c%d%c",&char_01, &num01, &char_02, &num02, &char_03, &num03, &char_04);
					for(volatile uint32_t i =0; i < (sizeof(rxBuffer)); i++){
						
						if(rxBuffer[i] <'0' || rxBuffer[i] > '9' ){
							char_count++;
						}else{}						
					}
					/*-------------------------------*/
					/*-------------------------------*/
					if((result != 6) || char_02 !='.'|| char_03 !='.' || (char_01 !='A' && char_01 !='D' && char_01 !='T')||(char_04 >0)) {/* if Fault format */
						//LPUART1_transmit_string("Wrong format_02\r\n");
						rxIndex =0;
						memset(rxBuffer, 0, sizeof(rxBuffer));
					}
					/*------------------------------------------------------------------*/
					/*------------------------------------------------------------------*/
					else{
						if(char_01 == 'T')
							{
								if(num01>=24 || num02>=60 || num03 >=60){
								}else{
								hour 	 = num01;				
								minute = num02;
								second = num03;
								}
							}
							/*------------------------------------------------------------------*/
							else if(char_01 == 'D'){
										if(num02 >12 || num01>31 ) {}
												else {
													if(num02==2) {
														uint32_t day_temp = isLeapYear(num03)?1:0;
														if(day_temp==1 && num01>29) {}
														else if(day_temp ==0 && num01 >28) {}
														else {
															day		=num01;
															month	=num02;
															year	=num03;
														}
													} else if(num02 == 4 || num02 == 6 || num02 == 9 || num02 == 11) {
														if(num01 >30) {}
														else {
															day		=num01;
															month	=num02;
															year	=num03;
														}
													} else if(num02 ==1 || num02==3 || num02==5|| num02==7|| num02==8|| num02==10|| num02==12 ) {
														if(num01>31) {}
														else {
															day	=num01;
															month	=num02;
															year	=num03;
														}
													} else {}
												}
								}
							/*------------------------------------------------------------------*/																							
							else if(char_01 == 'A'){
									if(num01>=24 || num02>=60 || num03 >=60){
										}else{
										hour_alarm 	 = num01;				
										minute_alarm = num02;
										second_alarm = num03;
								}
							
							}else{} 					/* End of if(char_01 == 'T')*/
						}		
					}											/* End of if(state_var==0)*/
							rxIndex=0;
							memset(rxBuffer, 0, sizeof(rxBuffer));
			}
}
