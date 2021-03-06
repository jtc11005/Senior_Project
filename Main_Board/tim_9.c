#include "tim_9.h"

#define AR_9 800 //auto reload value
#define PSC_9 0 // prescaler

void tim_9_gpio_init(void){
	
	/* CONFIGURE PWM PINS */
	/*
		PORT E PINS 5 AND 6 WILL BE CONFIGURED
		AS PUSH PULL, ALTERNATE FUNCTION FOR
		TIMER 9 AND NO PULL UP/PULL DOWN.
	*/
	
	// ENABLE GPIOE CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	
	/* SET AS PUSH PULL */
	
	// PE5
	GPIOE->OTYPER &= ~(1 << 5*1);
	
	// PE6
	GPIOE->OTYPER &= ~(1 << 6*1);
	
	/* SET AS ALTERNATE FUNCTION */
	
	// PE5
	GPIOE->MODER &= ~(3 << 5*2);
	GPIOE->MODER |= (2 << 5*2);
	
	// PE6
	GPIOE->MODER &= ~(3 << 6*2);
	GPIOE->MODER |= (2 << 6*2);
	
	/* SET AF AS TIM 9 */
	
	// PE5
	GPIOE->AFR[0] &= ~(0xF << 5*4);
	GPIOE->AFR[0] |= (3 << 5*4);
	
	// PE6
	GPIOE->AFR[0] &= ~(0xF << 6*4);
	GPIOE->AFR[0] |= (3 << 6*4);
	
	/* SET AS NO PULL-UP PULL-DOWN */
	
	//PE5
	GPIOE->PUPDR &= ~(3 << 5*2);
	
	//PE6
	GPIOE->PUPDR &= ~(3 << 6*2);
	
	/* CONFIGURE DIGITAL IO PINS */
	/*
		PORT E PINS 3 AND 4 WILL SERVE AS THE
		LOW SIDE H-BRIDGE CONTROLS FOR THE 
		TIMER 9 PWM CHANNELS.
		
		THEY ARE CONFIGURED AS PUSH PULL, GENERAL
		OUTPUT AND NO PULL-UP/PULL-DOWN.
	*/
	
	// PORTE CLOCK WAS ENABLED EARLIER
	
	/* SET AS GENERAL PURPOSE OUTPUT */
	
	// PE3
	GPIOE->MODER &= ~(2 << 3*2);
	GPIOE->MODER |= (1<< 3*2);
	
	// PE4
	GPIOE->MODER &= ~(2 << 4*2);
	GPIOE->MODER |= (1 << 4*2);
	
	/* SET AS PUSH-PULL */
	
	// PE3
	GPIOE->OTYPER &= ~(1 << 3*1);
	
	// PE4
	GPIOE->OTYPER &= ~(1 << 4*1);
	
	/* SET AS NO PULL-UP/PULL-DOWN */
	
	// PE3
	GPIOE->PUPDR &= ~(2 << 3*2);
	
	// PE4
	GPIOE->PUPDR &= ~(2 << 4*2);
	
}

void tim_9_config(void){
	
	// ENABLE TIMER 5 CLOCK
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	
	// TIMER 9 PRESCALER FOR 20KHz FREQ
	TIM9->PSC &= ~TIM_PSC_PSC;
	TIM9->PSC |= PSC_9;
	
	// AUTO RELOAD REGISTER
	TIM9->ARR &= ~TIM_ARR_ARR;
	TIM9->ARR |= AR_9;
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 1
	TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M);
	TIM9->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
	
	// CONFIGURE PWM MODE TO MODE 1 CHANNEL 2
	TIM9->CCMR1 &= ~(TIM_CCMR1_OC2M);
	TIM9->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	
	// ENABLE AUTO RELOAD
	TIM9->CR1 |= TIM_CR1_ARPE;
	
	// ENABLE CHANNEL 1 OUTPUT
	TIM9->CCER |= TIM_CCER_CC1E;
	
	// ENABLE CHANNEL 2 OUTPUT
	TIM9->CCER |= TIM_CCER_CC2E;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 1
	TIM9->CCR1 |= 0;
	
	// PRELOAD CAPTURE COMPARE VALUE FOR CHANNEL 2
	TIM9->CCR2 |= 0;
	
	// ENABLE TIMER
	TIM9->CR1 |= TIM_CR1_CEN;
	
}
