#include "adc_2.h"

void adc_2_gpio_init(void) {
	
	/* CONFIGURE INPUT PINS */
	/*
		PORT B PINS 0 AND 1, AND PORT C PINS 0 AND
		1 ARE USED FOR ADC CHANNELS 8, 9, 10 AND 11.
		THEY ARE CONFIGURED AS ANALOG MODE,
		NO PULL-UP/PULL-DOWN.
	*/
	
	// ENABLE PORT B CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// ENABLE PORT C CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	/* SET AS ANALOG */
	
	// PB0
	GPIOB->MODER |= (3 << 0*2);
	
	// PB1
	GPIOB->MODER |= (3 << 1*2);
	
	// PC0
	GPIOC->MODER |= (3 << 0*2);
	
	// PC1
	GPIOC->MODER |= (3 << 1*2);
	
	/* SET AS NO PULL-UP/PULL-DOWN */
	
	// PB0
	GPIOB->PUPDR &= ~(3 << 0*2);
	
	// PB1
	GPIOB->PUPDR &= ~(3 << 1*2);
	
	// PC0
	GPIOC->PUPDR &= ~(3 << 0*2);
	
	// PC1
	GPIOC->PUPDR &= ~(3 << 1*2);
	
}

void adc_2_config(void) {
	
	/*
		ADC_2 WILL SAMPLE FROM FOUR SOURCES,
		CHANNELS 8, 9, 10 AND 11. THE ADC WILL NOT USE SCAN
		MODE, CHANNELS MUST BE SELECTED MANUALLY
		BY CONFIGURING WHICH CHANNEL THE ADC SAMPLES
		FROM USING THE SQR3 REGISTER. CHANNEL 8 WILL
		BE THE INITIAL CHANNEL SELECTED
	*/
		
	// ENABLE ADC
	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	
	// DISABLE CONVERSION
	ADC2->CR2 &= ~ADC_CR2_ADON;
	
	// CONFIGURE REGULAR CHANNEL SEQUENCE LENGTH TO 1 CONVERSION
	ADC2->SQR1 &= ~ADC_SQR1_L;
	
	// SELECT CHANNEL 6 AS FIRST AND ONLY CONVERSION
	ADC2->SQR3 |= 8;
	
	// SELECT 144 CYCLES PER SAMPLE FOR CONVERSION
	ADC2->SMPR1 |= (6 << 12);
	
	// ENABLE END OF CONVERSION INTERRUPT
	ADC2->CR1 |= ADC_CR1_EOCIE;
	
	// ENABLE ADC
	ADC2->CR2 |= ADC_CR2_ADON;
	
}


