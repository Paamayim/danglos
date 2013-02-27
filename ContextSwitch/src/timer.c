#include <LPC17xx.h>
#include "timer.h"

volatile uint32_t g_timer = 0;

void timer_init()
{
	LPC_TIM_TypeDef  * pTimer = (LPC_TIM_TypeDef *)LPC_TIM0;
	pTimer->PR = 12499;
	pTimer->MR0 = 1;
	pTimer->MCR = 3;
	g_timer = 0;
	NVIC_EnableIRQ(TIMER0_IRQn);
	pTimer->TCR = 1;
}
__asm void TIMER0_IRQHandler(void)
{
	PRESERVE8
	IMPORT c_TIMER0_IRQHandler
	PUSH{r4-r11, lr}
	BL c_TIMER0_IRQHandler
	POP{r4-r11, pc}
} 

void c_TIMER0_IRQHandler(void)
{
	/* ack inttrupt, see section  21.6.1 on pg 493 of LPC17XX_UM */
	LPC_TIM0->IR = 1;  
	
	++g_timer;
}