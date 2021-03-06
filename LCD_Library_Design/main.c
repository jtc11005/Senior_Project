#include <stdint.h>
#include "stm32l1xx.h"

void sysclk_Configure(void);
void io_Configure(void);
void pb_Configure(void);
void timer4_Configure(void);

int main(void)
{

	/* SYSTEM CLOCK CONFIGURE */
	sysclk_Configure();
		
	/* I/O CONFIGURATION */
	io_Configure();
	
	/* PUSH BUTTON INTERRUPT CONFIGURE */
	pb_Configure();
	
	/* TIMER 4 CONFIGURATION */
	timer4_Configure();
	
	while(1);
}

void EXTI0_IRQHandler(void) {

	// stuff to do in interrupt
	
	// CLEAR INTERRUPT
	EXTI->PR |= EXTI_PR_PR0;
}
	
	/* SYSTEM CLOCK CONFIGURE */
void sysclk_Configure(void){
	
	// ENABLE HSI
	RCC->CR |= RCC_CR_HSION;
	
	// WAIT FOR HSI
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);

	// SELECT HSI AS SYSTEM CLOCK
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	
	// WAIT FOR HSI TO BE SELECTED
	while ((RCC->CFGR & RCC_CFGR_SWS) == !RCC_CFGR_SWS_HSI);
}
	
	/* I/O CONFIGURATION */
void io_Configure(void) {
	// ENABLE GPIO A CLOCK
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
}

	/* PUSH BUTTON INTERRUPT CONFIGURE */
void pb_Configure(void) {
	// UNMASK INTERRUPT FOR EXTI 0, PUSH BUTTON
	EXTI->IMR |= EXTI_IMR_MR0;
	// SET INTERRUPT FOR RISING EDGE
	EXTI->RTSR |= EXTI_RTSR_TR0;
	// ENABLE PUSH BUTTON INTERRUPT
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
	
	// SET INTERRUPT PRIORITY
	NVIC->IP[6] |= (NVIC_IPR0_PRI_0 & 1);
}
	
	/* TIMER 4 CONFIGURATION */
void timer4_Configure(void){
	
	// ENABLE TIMER 4 CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	// TIMER 4 PRESCALER BASED OFF 16MHZ HSI
	TIM4->PSC |= 0;
	
	// AUTO RELOAD REGISTER
	TIM4->ARR &= ~TIM_ARR_ARR;
	TIM4->ARR |= -1;
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 1
	TIM4->CCMR1 &= ~(TIM_CCMR1_OC1M);
	TIM4->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 2
	TIM4->CCMR1 &= ~(TIM_CCMR1_OC2M);
	TIM4->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	
	// ENABLE AUTO RELAOD
	TIM4->CR1 |= TIM_CR1_ARPE;
	
	// ENABLE CHANNEL 1 OUTPUT
	TIM4->CCER |= TIM_CCER_CC1E;
	
	// ENABLE CHANNEL 2 OUTPUT
	TIM4->CCER |= TIM_CCER_CC2E;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 1
	TIM4->CCR1 |= 0;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 2
	TIM4->CCR2 |= 0;
	
	//ENABLE TIMER
	TIM4->CR1 |= TIM_CR1_CEN;
	
}	
