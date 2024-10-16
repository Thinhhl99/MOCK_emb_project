#ifndef __S32K144_LPUART_H__
#define __S32K144_LPUART_H__
#include <stdint.h>
#include "common.h"

typedef union {
	uint32_t REG;
	struct{
		RW	uint32_t SBR					: 13;
		RW	uint32_t SBNS					: 1;
		RW	uint32_t RXEDGIE			: 1;
		RW	uint32_t LBKDIE				: 1;
		RW	uint32_t RESYNCDIS 		: 1;
		RW	uint32_t BOTHEDGE			: 1;
		RW	uint32_t MATCFG				: 2;
		RW	uint32_t RIDMAE				:	1;
		RW	uint32_t DRMAE				:	1;
		RO 	uint32_t res01				: 1;
		RW	uint32_t TDMAE				: 1;
		RW	uint32_t OSR					: 5;
		RW	uint32_t M10					: 1;
		RW	uint32_t MAEN2				: 1;
		RW	uint32_t MAEN1				: 1;
		
	}FIELD;
}BAUD_REG_t;
typedef union{
	uint32_t REG;
	struct {
		RW	uint32_t PT			:1;
		RW	uint32_t PE			:1;
		RW	uint32_t ILT		:1;
		RW	uint32_t WAKE		:1;
		RW	uint32_t M			:1;
		RW	uint32_t RSRC		:1;
		RW	uint32_t DOZEEN	:1;
		RW	uint32_t LOOPS	:1;
		RW	uint32_t IDLECFG:3;
		RW	uint32_t M7			:1;
		RO	uint32_t RES01	:2;
		RW	uint32_t MA2IE	:1;
		RW	uint32_t MA1IE	:1;
		RW	uint32_t SBK		:1;
		RW	uint32_t RWU		:1;
		RW	uint32_t RE			:1;
		RW	uint32_t TE			:1;
		RW	uint32_t ILIE		:1;
		RW	uint32_t RIE		:1;
		RW	uint32_t TCIE		:1;
		RW	uint32_t TIE		:1;
		RW	uint32_t PEIE		:1;
		RW	uint32_t FEIE		:1;
		RW	uint32_t NEIE		:1;
		RW	uint32_t ORIE		:1;
		RW	uint32_t TXINV	:1;
		RW	uint32_t TXDIR	:1;
		RW	uint32_t R9T8		:1;
		RW	uint32_t R8T9		:1;
		
	}FIELD;
}LPUART_CTRL_t;

typedef union{
	uint32_t REG;
	struct{
		RO	uint32_t RES01			:14;
		RW	uint32_t MA2F				:1;
		RW	uint32_t MA1F				:1;
		RW	uint32_t PF					:1;
		RW	uint32_t PE					:1;
		RW	uint32_t NF					:1;
		RW	uint32_t OR					:1;
		RW	uint32_t IDLE				:1;
		RO	uint32_t RDRF				:1;
		RO	uint32_t TC					:1;
		RO	uint32_t TDRE				:1;
		RO	uint32_t RAF				:1;
		RW	uint32_t LBKDE			:1;
		RW	uint32_t BRK13			:1;
		RW	uint32_t RWUID			:1;
		RW	uint32_t RXINV			:1;
		RW	uint32_t MSBF				:1;
		RW	uint32_t RXEDGIF		:1;
		RW	uint32_t LBKDIF			:1;
	}FIELD;
}STAT_REG_t;

typedef union{
	uint32_t REG;
	struct{
		RW	uint32_t RxTx		:8; //DATA: 0->7
		RW	uint32_t R8T8		:1;
		RW	uint32_t R9T9		:1;
		RO	uint32_t RES01	:1;
		RO	uint32_t IDLINE	:1;
		RO	uint32_t RXEMPT	:1;
		RW	uint32_t FIRETSC:1;
		RO	uint32_t PARITYE:1;
		RO	uint32_t NOISY	:1;
		RO	uint32_t RES02	:16;
	}FIELD;
}DATA_REG_t;
typedef struct{
	IO RW uint32_t 			VERID;			//Version ID Register (VERID)
	IO RW uint32_t 			PARAM;			//Parameter Register (PARAM)
	IO RW uint32_t 			GLOBAL;			//LPUART Global Register (GLOBAL)
	IO RW uint32_t 			PINCFG;			//LPUART Pin Configuration Register (PINCFG)
	IO RW BAUD_REG_t		BAUD;				//LPUART Baud Rate Register (BAUD)
	IO STAT_REG_t 			STAT;				//LPUART Status Register (STAT)
	IO LPUART_CTRL_t		CTRL;				//LPUART Control Register (CTRL)
	IO DATA_REG_t 			DATA;				//LPUART Data Register (DATA)
	IO RW uint32_t 			MATCH;			//LPUART Match Address Register (MATCH)
	IO RW uint32_t 			MODIR;			//LPUART Modem IrDA Register (MODIR)
	IO RW uint32_t 			FIFO;				//LPUART FIFO Register (FIFO)
	IO RW uint32_t 			WATER;			//LPUART Watermark Register (WATER)
	
}LPUART_t;
#define 	LPUART1_BASE			(0x4006b000)
#define 	LPUART1		((LPUART_t *) LPUART1_BASE)

void LPUART1_init(void);
void LPUART1_init_ASM(void);
void LPUART1_init_MOCK(void);
void LPUART1_init_interrupt(void);
void LPUART1_transmit_string(char data_string[]);
void LPUART1_transmit_char(char send);
char LPUART1_receive_char(void);
void LPUART1_receive_and_echo_char(void);
void LPUART1_receive_string(void);

#endif
