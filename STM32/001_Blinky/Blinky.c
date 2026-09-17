#include <stdint.h>
#include "delay_ms.h"
#include "stm32f0xx.h"

void setup(){
	RCC->AHBENR |= (1 << 17);
	GPIOA->MODER &= ~((1 << 10) | (1 << 11));
	GPIOA->MODER |= (1 << 10);
	GPIOA->OTYPER &= ~(1 << 5);
	GPIOA->PUPDR &= ~((1 << 10) | (1 << 11));
}

int main(void)
{
	setup();
	delay_setup();
	while(1){
		GPIOA->ODR ^= (1 << 5);
		delay_ms(2000); // ms
	}
}