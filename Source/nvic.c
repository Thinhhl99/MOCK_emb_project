#include<nvic.h>
#include<main.h>
void nvic_enable_interrupt(IRQn_t irq_id){
	NVIC->NVIC_ISER[irq_id/32]= SET_BIT_AT_OFFSET(NVIC->NVIC_ISER[irq_id/32], irq_id%32);
	//NVIC->ISER[irq_id/32] = SET_BIT_AT_OFFSET(NVIC->ISER[irq_id/32],irq_id%32);
}
void nvic_disable_interrupt(IRQn_t irq_id){
	NVIC->NVIC_ICER[irq_id/32]= SET_BIT_AT_OFFSET(NVIC->NVIC_ICER[irq_id/32], irq_id%32);
	//NVIC->ICER[irq_id/32] = SET_BIT_AT_OFFSET(NVIC->ICER[irq_id/32],irq_id%32);
}

void nvic_set_priority(IRQn_t irq_id){
	NVIC->NVIC_IPR[irq_id/4]=SET_BIT_AT_OFFSET(NVIC->NVIC_IPR[irq_id/4], (irq_id%4)* 8);
	
}
void nvic_clear_pending(IRQn_t irq_id){
	NVIC->NVIC_ICPR[irq_id/32]= SET_BIT_AT_OFFSET(NVIC->NVIC_ICPR[irq_id],irq_id%32);
	//NVIC->ICPR[irq_id/32] = SET_BIT_AT_OFFSET(NVIC->ICPR[irq_id/32],irq_id%32);
}
void nvic_set_pending(IRQn_t irq_id){
	NVIC->NVIC_ISPR[irq_id/32]= SET_BIT_AT_OFFSET(NVIC->NVIC_ISPR[irq_id/32], irq_id%32);
	//NVIC->ISPR[irq_id/32]= SET_BIT_AT_OFFSET(NVIC->ISPR[irq_id/32], irq_id%32);
}
