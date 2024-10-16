#include "main.h"
#include "lpspi.h"


void LPSPI_init(void){
	PCC->PCC_LPSPI0.FIELD.CGC = 0u; /* Disable clock*/
	PCC->PCC_LPSPI0.FIELD.PCS = 6u; /* Select SPLLDIV2_CLK*/
	PCC->PCC_LPSPI0.FIELD.CGC = 1u; /* Enable clock*/
	
	/*---- Setting LPSPI ----*/
	//LPSPI0->TCR.FIELD.PRESCALE = 2u;/* Div by 1*2*/
	LPSPI0->CCR.FIELD.SCKDIV	 = 8u;/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) */
	//LPSPI0->TCR.FIELD.CPOL		 = 0u;
	//LPSPI0->TCR.FIELD.CPHA		 = 0u;
	//LPSPI0->TCR.FIELD.FRAMESZ	 = 15u;/* FRAMESZ=15: # bits in frame = 15+1=16 */
	//LPSPI0->TCR.FIELD.LSBF		 = 0u; /* LSBF=0: Data is transferred MSB first */
	//LPSPI0->TCR.FIELD.PCS			 = 2u; /* PCS=2: Transfer using PCS2 */
	
	LPSPI0->FCR.FIELD.RXWATER	 = 1u; /* RXWATER=1: Rx flags set when Rx FIFO >1 */
	LPSPI0->FCR.FIELD.TXWATER	 = 1u; /* TXWATER=1: Tx flags set when Tx FIFO <= 1 */
	LPSPI0->TCR.REG = 0x1200000f;
	LPSPI0->CFGR1.FIELD.NOSTALL= 1u;
	LPSPI0->CFGR1.FIELD.MASTER = 1u; /* MASTER=1: Master mode */
	LPSPI0->CR.FIELD.DBGEN		 = 1u; /* Debug Enable*/
	LPSPI0->CR.FIELD.MEN			 = 1u; /* 1b - Module is enabled*/

}
void LPSPI1_transmit_16bits(uint16_t send){
	while(LPSPI0->SR.FIELD.TDF == 0){}
		LPSPI0->TDR.FIELD.DATA =send;
		//LPSPI1->SR.FIELD.TDF =1;
		
}
uint16_t LPSPI1_receive_16bits(void){
	uint16_t receive =0;
	while(LPSPI0->SR.FIELD.RDF ==0){}
		receive = LPSPI0->RDR.FIELD.DATA;
		//LPSPI1->SR.FIELD.RDF =1;
		return receive;
}
void LPSPI0_transmit_mode_16bits(uint8_t address, uint8_t data){
	while(LPSPI0->SR.FIELD.TDF == 0){}	
		LPSPI0->TDR.REG = ((address<<8)|(data));
}
uint8_t process_number_led(uint8_t number){
	if(number ==0){
		return 0x7e;
	}
	else if(number ==1){
		return 0x30;
	}
	else if(number ==2){
		return 0x6d;
	}
	else if(number ==3){
		return 0x79;
	}
 	else if(number ==4){
		return 0x33;
	}
	else if(number ==5){
		return 0x5b;
	}
	else if(number ==6){
		return 0x5f;
	}
	else if(number ==7){
		return 0x70;
	} 
	else if(number ==8){
		return 0x7f;
	}
	else if(number ==9){
		return 0x7b;
	}
	else{} 	
}

uint8_t process_number_led_DP(uint8_t number){
	if(number ==0){
		return 0xfe;
	}
	else if(number ==1){
		return 0xb0;
	}
	else if(number ==2){
		return 0xed;
	}
	else if(number ==3){
		return 0xf9;
	}
 	else if(number ==4){
		return 0xb3;
	}
	else if(number ==5){
		return 0xdb;
	}
	else if(number ==6){
		return 0xdf;
	}
	else if(number ==7){
		return 0xf0;
	} 
	else if(number ==8){
		return 0xff;
	}
	else if(number ==9){
		return 0xfb;
	}
	else{} 	
}
void LPSPI0_hour_m_s(uint8_t hour, uint8_t minute, uint8_t second){
	uint8_t hour_div10 		= process_number_led(hour/10);
	uint8_t hour_mod10 		= process_number_led(hour%10);
	uint8_t minute_div10 	= process_number_led(minute/10);
	uint8_t minute_mode10 = process_number_led(minute%10);
	uint8_t second_div10 	= process_number_led(second/10);
	uint8_t second_mode10 = process_number_led(second%10);
	/* HOUR*/
	LPSPI0_transmit_mode_16bits(0x8, hour_div10);
	LPSPI0_transmit_mode_16bits(0x7, hour_mod10);
	/* MINUTE*/
	LPSPI0_transmit_mode_16bits(0x6, 0x1); 					/* '-'*/
	LPSPI0_transmit_mode_16bits(0x5, minute_div10);
	LPSPI0_transmit_mode_16bits(0x4, minute_mode10);
	/* SECOND*/
	LPSPI0_transmit_mode_16bits(0x3, 0x1);					/* '-'*/
	LPSPI0_transmit_mode_16bits(0x2, second_div10);
	LPSPI0_transmit_mode_16bits(0x1, second_mode10);
	
}
void LPSPI0_year_m_d(uint8_t day, uint8_t month, uint16_t year){
	uint8_t year_mod10 	= year%10;
	uint8_t year_mod100 = (year%100)/10;
	uint8_t year_mod1000 = (year%1000 )/100;
	uint8_t year_div1000 = year/1000;
	uint8_t month_div10 = process_number_led(month/10);
	uint8_t month_mod10 = process_number_led_DP(month%10);		//
	uint8_t day_div10  = process_number_led(day/10);
	uint8_t day_mod10	= process_number_led_DP(day%10);				//
	/* process variable name: year*/
	year_mod10 = process_number_led(year_mod10);
	year_mod100 = process_number_led(year_mod100);
	year_mod1000 = process_number_led(year_mod1000);
	year_div1000 = process_number_led(year_div1000);
	/* Setting led*/
	/* DAY*/
	LPSPI0_transmit_mode_16bits(0x8, day_div10);
	LPSPI0_transmit_mode_16bits(0x7, day_mod10);
	LPSPI0_transmit_mode_16bits(0x6, month_div10);
	LPSPI0_transmit_mode_16bits(0x5, month_mod10);
	LPSPI0_transmit_mode_16bits(0x4, year_div1000);
	LPSPI0_transmit_mode_16bits(0x3, year_mod1000);
	LPSPI0_transmit_mode_16bits(0x2, year_mod100);
	LPSPI0_transmit_mode_16bits(0x1, year_mod10);
	
}
void LPSPI0_Intensity_led(uint8_t intensity_led){
	if(intensity_led ==3){
		LPSPI0_transmit_mode_16bits(0x1, 0x00);
		LPSPI0_transmit_mode_16bits(0x2, 0x00);
		LPSPI0_transmit_mode_16bits(0x3, 0x00);
		LPSPI0_transmit_mode_16bits(0x4, 0x00);
		LPSPI0_transmit_mode_16bits(0x5, 0x00);
		LPSPI0_transmit_mode_16bits(0x6, 0x00);
		LPSPI0_transmit_mode_16bits(0x7, 0x00);
		LPSPI0_transmit_mode_16bits(0x8, 0x00);
	}
	else if (intensity_led ==2){
		LPSPI0_transmit_mode_16bits(0xa, 0x00);
	}
	else if (intensity_led ==1){
		LPSPI0_transmit_mode_16bits(0xa, 0x05);
	}
	else if (intensity_led ==0){
		LPSPI0_transmit_mode_16bits(0xa, 0x0a);
	}
	else if (intensity_led ==4){
		LPSPI0_transmit_mode_16bits(0xa, 0x0f);
	}
	else{}
}
