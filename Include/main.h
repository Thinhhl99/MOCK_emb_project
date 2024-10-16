#ifndef __MAIN_H__
#define __MAIN_H__
#include "pcc.h"
#include "port.h"
#include "gpio.h"

#define SET_BIT_AT_OFFSET(reg, offset) ((reg)|(1<<(offset)))
#define CLEAR_BIT_AT_OFFSET(reg, offset) ((reg) &~ (1<< (offset)))
#define GET_BIT_AT_OFFSET(reg,offset) (((reg)>>(offset))&1)
// handle the optimize -O0 checking for main argument
__asm(".global __ARM_use_no_argv");



#endif /* !__MAIN_H__ */
