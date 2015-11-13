#include "tim_13.h"

void tim_13_config(void){
	
	// ENABLE TIMER 13 CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
	
	// TIMER 13 PRESCALER FOR 20KHz FREQ
	TIM13->PSC &= ~TIM_PSC_PSC;
	TIM13->PSC |= 0;
	
	// AUTO RELOAD REGISTER
	TIM13->ARR &= ~TIM_ARR_ARR;
	TIM13->ARR |= 0-320;
	
	// ENABLE AUTO RELOAD
	TIM13->CR1 |= TIM_CR1_ARPE;
	
	// ENABLE UPDATE EVENT INTERRUPT
	TIM13->DIER |= TIM_DIER_UIE;
	
	// ENABLE INTERRUPT
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 1);
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	
	// ENABLE TIMER
	TIM13->CR1 |= TIM_CR1_CEN;
	
}