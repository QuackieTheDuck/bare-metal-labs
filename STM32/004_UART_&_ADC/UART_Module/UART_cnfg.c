#include <HRM.h>
#include <stdint.h>
#include "stm32f0xx.h"

void UART_setup (){
    // Disable USART since some registers can be modified only if UE=0
    USART1->CR1 &= ~(HRM_USART_CR1_UE);

    //USART_CR1
    USART1->CR1 &= ~(HRM_USART_CR1_M0 | HRM_USART_CR1_M1);
    USART1->CR1 &= ~(HRM_USART_CR1_OVER8);
    USART1->CR1 &= ~(HRM_USART_CR1_PCE);
    USART1->CR1 |= (HRM_USART_CR1_TE);

    //USART_CR2
    USART1->CR2 &= ~(HRM_USART_CR2_ABREN);
    USART1->CR2 &= ~(HRM_USART_CR2_MSBFIRST);
    USART1->CR2 &= ~(HRM_USART_CR2_DATAINV);
    USART1->CR2 &= ~(HRM_USART_CR2_TXINV);
    USART1->CR2 &= ~(HRM_USART_CR2_SWAP);
    USART1->CR2 &= ~(HRM_USART_CR2_STOP_0 | HRM_USART_CR2_STOP_1);

    //USART_BRR
    USART1->BRR = HRM_USART_BRR_USARTDIV;

    // Enable USART
    USART1->CR1 |= (HRM_USART_CR1_UE);
}

// USART_ICR
// USART_ISR