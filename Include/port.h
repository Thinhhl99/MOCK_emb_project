#ifndef __S32K144_PORT_H__
#define __S32K144_PORT_H__

#include <stdint.h>
#include "common.h"

typedef union {
	uint32_t REG;
	struct {
		RW uint32_t PS 		: 1;
		RW uint32_t PE 		: 1;
		RO uint32_t RES01 : 2;
		RW uint32_t PFE 	: 1;
		RO uint32_t RES02 : 1;
		RW uint32_t DES 	: 1;
		RO uint32_t RES03 : 1;
		RW uint32_t MUX 	: 3;
		RO uint32_t RES04 : 4;
		RW uint32_t LK 		: 1;
		RW uint32_t IRQC 	: 4;
		RO uint32_t RES05 : 4;
		RW uint32_t ISF 	: 1;
		RO uint32_t RES06 : 7;	
	} FIELD;
} S32K144_PORT_PIN_CONTROL_REG_t;

typedef struct {
	IO    S32K144_PORT_PIN_CONTROL_REG_t PORT_PCR[32];
	//-----------------------------
	IO RW uint32_t											PORT_GPCLR;
	IO RW uint32_t  										PORT_GPCHR;
	IO RW uint32_t											PORT_GICLR;
	const unsigned char									RES[16];
	IO RW	uint32_t											PORT_ISFR;
	const unsigned char									RES02[28];
	IO RW uint32_t 											PORT_DFER;
	IO RO uint32_t 											PORT_DFCR;
	IO RO uint32_t 											PORT_DFWR;
} PORT_t;


/* define port base addresss */
#define PORT_A_BASE             (0x40049000u)
#define PORT_B_BASE             (0x4004A000u)
#define PORT_C_BASE             (0x4004B000u)
#define PORT_D_BASE             (0x4004C000u)
#define PORT_E_BASE             (0x4004D000u)

#define PORT_A              ((PORT_t *) PORT_A_BASE)
#define PORT_B              ((PORT_t *) PORT_B_BASE)
#define PORT_C              ((PORT_t *) PORT_C_BASE)
#define PORT_D              ((PORT_t *) PORT_D_BASE)
#define PORT_E              ((PORT_t *) PORT_E_BASE)



#endif /* !__PORT_H__ */
