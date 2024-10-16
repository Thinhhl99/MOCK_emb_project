#ifndef __S32K144_DELAY_H__
#define __S32K144_DELAY_H__

#include<stdint.h>
void delay(void);
void delay_ms(unsigned int ms_second); //1000(ms) = 1 second
void delay_ms_(unsigned int ms_second, unsigned int fcore);
#endif //__delay___
