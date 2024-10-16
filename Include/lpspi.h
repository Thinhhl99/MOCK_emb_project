#ifndef __S32K144_LPSPI_H__
#define __S32K144_LPSPI_H__
#include <stdint.h>
#include "common.h"

typedef union{
	uint32_t REG;
	struct{
		RO uint32_t FEATURE			:		16;
		RO uint32_t MINOR				:		8;
		RO uint32_t MAJOR				:		8;
	}FIELD;
}LPSPI_VERID_t;

typedef union{
	uint32_t REG;
	struct{
		RO uint32_t TXFIFO			:			8;
		RO uint32_t RXFIFO			:			8;
		RO uint32_t res					: 		16;
		
	}FIELD;
}LPSPI_PARAM_t;

typedef union{
	uint32_t REG;
	struct {
		RW uint32_t MEN			:		1;
		RW uint32_t RST			:		1;
		RW uint32_t DOZEN		:		1;
		RW uint32_t DBGEN		:		1;
		RO uint32_t res01		:		4;
		RW uint32_t RTF			:		1;
		RW uint32_t RRF			:		1;
		RO uint32_t res02		:		22;
	}FIELD;
}LPSPI_CR_t;

typedef union{
	uint32_t REG;
	struct{
		RO uint32_t TDF			:1;
		RO uint32_t RDF			:1;
		RO uint32_t res00		:6;
		RW uint32_t WCF			:1;
		RW uint32_t FCF			:1;
		RW uint32_t TCF			:1;
		RW uint32_t TEF			:1;
		RW uint32_t REF			:1;
		RW uint32_t DMF			:1;
		RO uint32_t res01		:10;
		RO uint32_t MBF			:1;
		RO uint32_t res03		:7;
	}FIELD;
}LPSPI_SR_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t TDIE		:1;
		RW uint32_t RDIR		:1;
		RO uint32_t res00		:6;
		RW uint32_t WCIE		:1;
		RW uint32_t FCIE		:1;
		RW uint32_t TCIE		:1;
		RW uint32_t TEIE		:1;
		RW uint32_t REIE		:1;
		RW uint32_t DMIE		:1;
		RO uint32_t res02		:18;
	}FIELD;
}LPSPI_IER_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t TDDE		:1;
		RW uint32_t RDDE		:1;
		RO uint32_t res00		:30;
	}FIELD;
}LPSPI_DER_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t HREN			:1;
		RW uint32_t HRPOL			:1;
		RW uint32_t HRSEL			:1;
		RO uint32_t res00			:5;
		RW uint32_t CIRFIFO		:1;
		RW uint32_t RDMO			:1;
		RO uint32_t res02			:22;
	}FIELD;
}LPSPI_CFGR0_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t MASTER			:1;
		RW uint32_t SAMPLE			:1;
		RW uint32_t AUTOPCS			:1;
		RW uint32_t NOSTALL			:1;
		RO uint32_t res00				:4;
		RW uint32_t PCSPOL			:4;
		RO uint32_t res01				:4;
		RW uint32_t MATCFG			:3;
		RO uint32_t res02				:5;
		RW uint32_t PINCFG			:2;
		RW uint32_t OUTCFG			:1;
		RW uint32_t PCSCFG			:1;
		RO uint32_t res03				:4;
	}FIELD;
}LPSPI_CFGR1_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t MATCH_n:32;
	}FIELD;
}LPSPI_DMR_n_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t SCKDIV	:8;
		RW uint32_t DBT			:8;
		RW uint32_t PCSSCK	:8;
		RW uint32_t SCKPCS	:8;
	}FIELD;
}LPSPI_CCR_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t TXWATER	:2;
		RO uint32_t RES00		:14;
		RW uint32_t RXWATER	:2;
		RO uint32_t RES01		:14;
	}FIELD;
}LPSPI_FCR_t;

typedef union{
	RW uint32_t REG;
	struct{
		RO uint32_t TXCOUNT		:3;
		RO uint32_t RES00			:13;
		RO uint32_t RXCOUNT		:3;
		RO uint32_t RES01			:13;
	}FIELD;
}LPSPI_FSR_t;

typedef union{
	RW uint32_t REG;
	struct{
		RW uint32_t FRAMESZ		:12;
		RO uint32_t RES01			:4;
		RW uint32_t WIDTH			:2;
		RW uint32_t TXMSK			:1;
		RW uint32_t RXMSK			:1;
		RW uint32_t CONTC			:1;
		RW uint32_t CONT			:1;
		RW uint32_t BYSW			:1;
		RW uint32_t LSBF			:1;
		RW uint32_t PCS				:2;
		RO uint32_t RES02			:1;
		RW uint32_t PRESCALE	:3;
		RW uint32_t CPHA			:1;
		RW uint32_t CPOL			:1;
	}FIELD;
}LPSPI_TCR_t;

typedef union{
	uint32_t REG;
	struct{
		RW uint32_t DATA		:32;		
	}FIELD;
}LPSPI_TDR_t;

typedef union{
	RW uint32_t REG;
	struct{
		RO uint32_t SOF				:1;	
		RO uint32_t RXEMPTY		:1;	
		RO uint32_t RES00			:30;	
	}FIELD;
}LPSPI_RSR_t;

typedef union{
	RW uint32_t REG;
	struct{
		RO uint32_t DATA			:32;	
	}FIELD;
}LPSPI_RDR_t;

typedef struct{
	IO LPSPI_VERID_t 		VERID;
	IO LPSPI_PARAM_t 		PARAM;
	IO RO	uint32_t 			RES00[2];
	IO LPSPI_CR_t 			CR;
	IO LPSPI_SR_t 			SR;
	IO LPSPI_IER_t		 	IER;
	IO LPSPI_DER_t 			DER;
	IO LPSPI_CFGR0_t	 	CFGR0;
	IO LPSPI_CFGR1_t 		CFGR1;
	IO RO	uint32_t 			RES01[2];
	IO LPSPI_DMR_n_t 		DMR0;
	IO LPSPI_DMR_n_t 		DMR1;
	IO RO	uint32_t 			RES02[2];
	IO LPSPI_CCR_t 			CCR;
	IO RO	uint32_t 			RES03[5];
	IO LPSPI_FCR_t 			FCR;
	IO LPSPI_FSR_t 			FSR;
	IO LPSPI_TCR_t 			TCR;
	IO LPSPI_TDR_t 			TDR;
	IO RO	uint32_t 			RES04[2];
	IO LPSPI_RSR_t 			RSR;
	IO LPSPI_RDR_t 			RDR;
	
	
}LPSPI_t;

#define LPSPI0_BASE				(0x4002C000)
#define LPSPI1_BASE				(0x4002D000)
#define LPSPI2_BASE				(0x4002E000)

#define LPSPI0						((LPSPI_t*)LPSPI0_BASE)
#define LPSPI1						((LPSPI_t*)LPSPI1_BASE)
#define LPSPI2						((LPSPI_t*)LPSPI2_BASE)

/*-----------------    -------------------------*/
void LPSPI_init(void);
void LPSPI1_transmit_16bits(uint16_t tx_16bits);
uint16_t LPSPI1_receive_16bits(void);
void LPSPI0_transmit_mode_16bits(uint8_t address, uint8_t data);
void LPSPI0_hour_m_s(uint8_t hour, uint8_t minute, uint8_t second);
void LPSPI0_year_m_d(uint8_t day, uint8_t month, uint16_t year);
uint8_t process_number_led(uint8_t number);
uint8_t process_number_led_DP(uint8_t number);
void LPSPI0_Intensity_led(uint8_t intensity_led);
#endif /* LPSPI.h*/
