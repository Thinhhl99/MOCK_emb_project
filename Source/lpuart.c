#include "lpuart.h"
#include "main.h"
#include "lpit.h"
void LPUART1_init(void){
	PCC->PCC_LPUART1.FIELD.CGC =0u;		/* Ensure clk disabled for config */
	PCC->PCC_LPUART1.FIELD.PCS =0x3;	/* Clock Src= 3 (FIRCDIV2_CLK) */
	PCC->PCC_LPUART1.FIELD.CGC =1u;		/* Enable clock for LPUART1 regs */
	
	LPUART1->BAUD.REG = 0x0900007d;		/* Initialize for 9600 baud, 1 stop: */
																		/* SBR=125 (0x1F4): baud divisor = 48M/9600/10 = 500 */
																		/* OSR=9: Over sampling ratio = 9+1=10 */
																		/* SBNS=0: One stop bit */
																		/* BOTHEDGE=0: receiver samples only on rising edge */
																		/* M10=0: Rx and Tx use 7 to 9 bit data characters */
																		/* RESYNCDIS=0: Resync during rec'd data word supported */
																		/* LBKDIE, RXEDGIE=0: interrupts disable */
																		/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
																		/* MAEN1, MAEN2, MATCFG=0: Match disabled */
	
	LPUART1->CTRL.REG = 0x000C0000;		/* Enable transmitter & receiver, no parity, 8 bit char: */
																		/* RE=1: Receiver enabled */
																		/* TE=1: Transmitter enabled */
																		/* PE,PT=0: No hw parity generation or checking */
																		/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
																		/* DOZEEN=0: LPUART enabled in Doze mode */
																		/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
																		/* TxDIR=0: TxD pin is input if in single-wire mode */
																		/* TXINV=0: TRansmit data not inverted */
																		/* RWU,WAKE=0: normal operation; rcvr not in statndby */
																		/* IDLCFG=0: one idle character */
																		/* ILT=0: Idle char bit count starts after start bit */
																		/* SBK=0: Normal transmitter operation - no break char */
																		/* LOOPS,RSRC=0: no loop back */
}

void LPUART1_init_interrupt(void){
	PCC->PCC_LPUART1.FIELD.CGC =0u;		/* Ensure clk disabled for config */
	PCC->PCC_LPUART1.FIELD.PCS =0x3;	/* Clock Src= 3 (FIRCDIV2_CLK) */
	PCC->PCC_LPUART1.FIELD.CGC =1u;		/* Enable clock for LPUART1 regs */
	
	LPUART1->BAUD.REG = 0x0900007d;		/* Initialize for 9600 baud, 1 stop: */
																		/* SBR=125 (0x1F4): baud divisor = 48M/9600/10 = 500 */
																		/* OSR=9: Over sampling ratio = 9+1=10 */
																		/* SBNS=0: One stop bit */
																		/* BOTHEDGE=0: receiver samples only on rising edge */
																		/* M10=0: Rx and Tx use 7 to 9 bit data characters */
																		/* RESYNCDIS=0: Resync during rec'd data word supported */
																		/* LBKDIE, RXEDGIE=0: interrupts disable */
																		/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
																		/* MAEN1, MAEN2, MATCFG=0: Match disabled */
	
	LPUART1->CTRL.REG = 0x000C0000;		/* Enable transmitter & receiver, no parity, 8 bit char: */
																		/* RE=1: Receiver enabled */
																		/* TE=1: Transmitter enabled */
																		/* PE,PT=0: No hw parity generation or checking */
																		/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
																		/* DOZEEN=0: LPUART enabled in Doze mode */
																		/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
																		/* TxDIR=0: TxD pin is input if in single-wire mode */
																		/* TXINV=0: TRansmit data not inverted */
																		/* RWU,WAKE=0: normal operation; rcvr not in statndby */
																		/* IDLCFG=0: one idle character */
																		/* ILT=0: Idle char bit count starts after start bit */
																		/* SBK=0: Normal transmitter operation - no break char */
																		/* LOOPS,RSRC=0: no loop back */
	LPUART1->CTRL.FIELD.RIE = 1;
}

void LPUART1_init_MOCK(void){
	PCC->PCC_LPUART1.FIELD.CGC =0u;		/* Ensure clk disabled for config */
	PCC->PCC_LPUART1.FIELD.PCS =6u;		/* Clock Src= 3 (SPLLDIV2_CLK) */
	PCC->PCC_LPUART1.FIELD.CGC =1u;		/* Enable clock for LPUART1 regs */
	
	LPUART1->BAUD.REG = 0x1100001a;		/* Initialize for 38400 baud, 1 stop: */
																		/* SBR=26 (0x1a): baud divisor = 18M/38400/18 =~26*/
																		/* OSR=17 (0x11): Over sampling ratio = 17+1=18 */
																		/* SBNS=0: One stop bit */
																		/* BOTHEDGE=0: receiver samples only on rising edge */
																		/* M10=0: Rx and Tx use 7 to 9 bit data characters */
																		/* RESYNCDIS=0: Resync during rec'd data word supported */
																		/* LBKDIE, RXEDGIE=0: interrupts disable */
																		/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
																		/* MAEN1, MAEN2, MATCFG=0: Match disabled */ 
	
	LPUART1->CTRL.REG = 0x000C0010;		/* Enable transmitter & receiver, no parity, 8 bit char: */
																		/* RE=1: Receiver enabled */
																		/* TE=1: Transmitter enabled */
																		/* PE,PT=0: No hw parity generation or checking */
																		/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
																		/* DOZEEN=0: LPUART enabled in Doze mode */
																		/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
																		/* TxDIR=0: TxD pin is input if in single-wire mode */
																		/* TXINV=0: TRansmit data not inverted */
																		/* RWU,WAKE=0: normal operation; rcvr not in statndby */
																		/* IDLCFG=0: one idle character */
																		/* ILT=0: Idle char bit count starts after start bit */
																		/* SBK=0: Normal transmitter operation - no break char */
																		/* LOOPS,RSRC=0: no loop back */
	 LPUART1->CTRL.FIELD.RIE = 1;											
}
void LPUART1_init_ASM(void){
	PCC->PCC_LPUART1.FIELD.CGC =0u;		/* Ensure clk disabled for config */
	PCC->PCC_LPUART1.FIELD.PCS =0x3;	/* Clock Src= 3 (FIRCDIV2_CLK) */
	PCC->PCC_LPUART1.FIELD.CGC =1u;		/* Enable clock for LPUART1 regs */
	
	LPUART1->BAUD.REG = 0x18000019;		/* Initialize for 19200 baud, 1 stop: */
																		/* SBR=25 (0x19): baud divisor = 12M/19200/25 = 25 */
																		/* OSR=9: Over sampling ratio = 24+1=25 */
																		/* SBNS=0: One stop bit */
																		/* BOTHEDGE=0: receiver samples only on rising edge */
																		/* M10=0: Rx and Tx use 7 to 9 bit data characters */
																		/* RESYNCDIS=0: Resync during rec'd data word supported */
																		/* LBKDIE, RXEDGIE=0: interrupts disable */
																		/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
																		/* MAEN1, MAEN2, MATCFG=0: Match disabled */
	
	LPUART1->CTRL.REG = 0x000C0000;		/* Enable transmitter & receiver, no parity, 8 bit char: */
																		/* RE=1: Receiver enabled */
																		/* TE=1: Transmitter enabled */
																		/* PE,PT=0: No hw parity generation or checking */
																		/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
																		/* DOZEEN=0: LPUART enabled in Doze mode */
																		/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
																		/* TxDIR=0: TxD pin is input if in single-wire mode */
																		/* TXINV=0: TRansmit data not inverted */
																		/* RWU,WAKE=0: normal operation; rcvr not in statndby */
																		/* IDLCFG=0: one idle character */
																		/* ILT=0: Idle char bit count starts after start bit */
																		/* SBK=0: Normal transmitter operation - no break char */
																		/* LOOPS,RSRC=0: no loop back */
	LPUART1->CTRL.FIELD.RIE = 1;
}
void LPUART1_transmit_char(char send){		/* Function to Transmit single Char */
	//while(LPUART1->STAT.FIELD.TDRE ==1){}		/* Wait for transmit buffer to be empty */
	//LPUART1->DATA.FIELD.RxTx = send;				/* Send data */
	
	while(LPUART1->STAT.FIELD.TDRE == 0){}
		LPUART1->DATA.FIELD.RxTx = send;

}

void LPUART1_transmit_string(char data_string[]){ 	/* Function to Transmit whole string */
	uint32_t i=0;
	while(data_string[i] != '\0'){										/* Send chars one at a time */
		LPUART1_transmit_char(data_string[i]);					
		i++;
	}
}

char LPUART1_receive_char(void){					/* Function to Receive single Char */
	char receive;
	while(LPUART1->STAT.FIELD.RDRF == 0){}	/* Wait for received buffer to be full */
	receive = LPUART1->DATA.FIELD.RxTx;			/* Read received data*/   // CHUA FIX
	return receive;
}

void LPUART1_receive_and_echo_char(void){	/* Function to echo received char back */
	char send = LPUART1_receive_char();			/* Receive Char */
	LPUART1_transmit_char(send); 						/* Transmit same char back to the sender */
	//LPUART1_transmit_char('\n'); 							/* New line */
}
