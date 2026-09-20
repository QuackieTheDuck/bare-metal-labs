#include "Map.h"
#include "stm32f0xx.h"

void usart_cnfg(){
    
    // Must by written only if USART in disabled UE=0
    USART2->CR1 &= ~(Map_USART2_CR1_M0);
    USART2->CR1 &= ~(Map_USART2_CR1_M1);
    USART2->CR1 &= ~(Map_USART2_CR1_OVER8);
    USART2->CR1 &= ~(Map_USART2_CR1_PCE);
    USART2->CR2 &= ~(Map_USART2_CR2_MSBFIRST);

    // Not specified if USART must be disabled
    USART2->CR1 &= ~(Map_USART2_CR1_RTOIE);
    USART2->CR1 &= ~(Map_USART2_CR1_CMIE);
    USART2->CR1 &= ~(Map_USART2_CR1_MME);
    USART2->CR1 &= ~(Map_USART2_CR1_TXEIE);
    USART2->CR1 |= Map_USART2_CR1_TCIE;
    USART2->CR1 |= Map_USART2_CR1_TE;
    USART2->CR2 &= ~(Map_USART2_CR2_ABREN);

    
}