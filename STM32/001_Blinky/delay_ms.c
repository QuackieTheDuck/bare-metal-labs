#include <stdint.h>
#include "delay_ms.h"
#include "stm32f0xx.h"

void delay_setup(void){
	RCC->APB1ENR |= (1 << 4);
	TIM6->CR1 |= (1 << 7);
	TIM6->PSC = 7;
	TIM6->ARR = 999;
	TIM6->CR1 |= (1 << 0);
}

void delay_ms(uint16_t time){
	delay_setup();
	for (int i=0; i < time; i++){
		while (!(TIM6->SR & (1 << 0))){
		}
		TIM6->SR &= ~(1 << 0);
	}
}
