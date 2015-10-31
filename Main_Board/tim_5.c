#include "tim_5.h"

#define AR_5 4800 //auto reload value
#define PSC_5 0 // prescaler


void tim_5_gpio_init(void){
	
	/* CONFIGURE PWM PINS */
	/*
		PORT A PINS 0, 1, 2, AND 3 WILL BE CONFIGURED
		AS PUSH PULL, ALTERNATE FUNCTION FOR TIMER 5
		AND NO PULL UP PULL DOWN.
	*/
	
	// ENABLE GPIOA CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	/* SET AS PUSH PULL */
	
	// PA0
	GPIOA->OTYPER &= ~(1 << 0*1);
	
	// PA1
	GPIOA->OTYPER &= ~(1 << 1*1);
	
	// PA2
	GPIOA->OTYPER &= ~(1 << 2*1);
	
	// PA3
	GPIOA->OTYPER &= ~(1 << 3*1);
	
	/* SET AS ALTERNATE FUNCTION */
	
	// PA0
	GPIOA->MODER &= ~(3 << 0*2);
	GPIOA->MODER |= (2 << 0*2);
	
	// PA1
	GPIOA->MODER &= ~(3 << 1*2);
	GPIOA->MODER |= (2 << 1*2);
	
	// PA2
	GPIOA->MODER &= ~(3 << 2*2);
	GPIOA->MODER |= (2 << 2*2);
	
	// PA3
	GPIOA->MODER &= ~(3 << 3*2);
	GPIOA->MODER |= (2 << 3*2);
	
	/* SET AF AS TIM 5*/
	
	// PA0
	GPIOA->AFR[0] &= ~(0xF << 0*4);
	GPIOA->AFR[0] |= (2 << 0*4);
	
	// PA1
	GPIOA->AFR[0] &= ~(0xF << 1*4);
	GPIOA->AFR[0] |= (2 << 1*4);
	
	// PA2
	GPIOA->AFR[0] &= ~(0xF << 2*4);
	GPIOA->AFR[0] |= (2 << 2*4);
	
	// PA3
	GPIOA->AFR[0] &= ~(0xF << 3*4);
	GPIOA->AFR[0] |= (2 << 3*4);
	
	/* SET AS NO PULL-UP PULL-DOWN */
	
	// PA0
	GPIOA->PUPDR &= ~(3 << 0*2);
	
	// PA1
	GPIOA->PUPDR &= ~(3 << 1*2);
	
	// PA2
	GPIOA->PUPDR &= ~(3 << 2*2);
	
	// PA3
	GPIOA->PUPDR &= ~(3 << 3*2);
	
	/* CONFIGURE DIGITAL IO PINS */	
	/*
		PORT E PINS 7, 8, 9 AND 10 WILL SERVE
		AS THE LOW SIDE CONTROL FOR THE CORRESPONDING
		PWM PINS.
		
		THEY ARE CONFIGURED AS PUSH PULL, GENERAL PURPOSE
		OUTPUT AND NO PULL UP/PULL DOWN.
	*/
	
	// ENABLE GPIOE CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	
	/* SET AS GENERAL PURPOSE OUTPUT */
	
	// PE7
	GPIOE->MODER &= ~(2 << 7*2);
	GPIOE->MODER |= (1 << 7*2);
	
	// PE8
	GPIOE->MODER &= ~(2 << 8*2);
	GPIOE->MODER |= (1 << 8*2);
	
	// PE9
	GPIOE->MODER &= ~(2 << 9*2);
	GPIOE->MODER |= (1 << 9*2);
	
	// PE10
	GPIOE->MODER &= ~(2 << 10*2);
	GPIOE->MODER |= (1 << 10*2);
	
	/* SET AS PUSH-PULL */
	
	// PE7
	GPIOE->OTYPER &= ~(1 << 7*1);
	
	// PE8
	GPIOE->OTYPER &= ~(1 << 8*1);
	
	// PE9
	GPIOE->OTYPER &= ~(1 << 9*1);
	
	// PE10
	GPIOE->OTYPER &= ~(1 << 10*1);
	
	/* SET AS NO PULL UP/PULL DOWN */
	
	// PE7
	GPIOE->PUPDR &= ~(2 << 7*2);
	
	// PE8
	GPIOE->PUPDR &= ~(2 << 8*2);
	
	// PE9
	GPIOE->PUPDR &= ~(2 << 9*2);
	
	// PE10
	GPIOE->PUPDR &= ~(2 << 10*2);
	
}

	/* TIMER 5 CONFIGURATION */
void TIM_5_init(void){
	
	// ENABLE TIMER 5 CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	
	// TIMER 5 PRESCALER FOR 20KHz FREQ
	TIM5->PSC &= ~TIM_PSC_PSC;
	TIM5->PSC |= PSC_5;
	
	// AUTO RELOAD REGISTER
	TIM5->ARR &= ~TIM_ARR_ARR;
	TIM5->ARR |= AR_5;
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 1
	TIM5->CCMR1 &= ~(TIM_CCMR1_OC1M);
	TIM5->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 2
	TIM5->CCMR1 &= ~(TIM_CCMR1_OC2M);
	TIM5->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 3
	TIM5->CCMR1 &= ~(TIM_CCMR2_OC3M);
	TIM5->CCMR1 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 4
	TIM5->CCMR1 &= ~(TIM_CCMR2_OC4M);
	TIM5->CCMR1 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);
	
	// ENABLE AUTO RELAOD
	TIM5->CR1 |= TIM_CR1_ARPE;
	
	// ENABLE CHANNEL 1 OUTPUT
	TIM5->CCER |= TIM_CCER_CC1E;
	
	// ENABLE CHANNEL 2 OUTPUT
	TIM5->CCER |= TIM_CCER_CC2E;
	
	// ENABLE CHANNEL 3 OUTPUT
	TIM5->CCER |= TIM_CCER_CC3E;
	
	// ENABLE CHANNEL 4 OUTPUT
	TIM5->CCER |= TIM_CCER_CC4E;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 1
	TIM5->CCR1 |= 0;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 2
	TIM5->CCR2 |= 0;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 3
	TIM5->CCR3 |= 0;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 4
	TIM5->CCR4 |= 0;
	
	// ENABLE TIMER
	TIM5->CR1 |= TIM_CR1_CEN;
	
}	