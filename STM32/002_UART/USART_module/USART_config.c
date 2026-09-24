#include "Map.h"
#include "stm32f0xx.h"

void usart_cnfg(){
    
    // Must by written only if USART in disabled UE=0
    USART2->CR1 &= ~(Map_USART2_CR1_M0);
    USART2->CR1 &= ~(Map_USART2_CR1_M1);
    USART2->CR1 &= ~(Map_USART2_CR1_OVER8);
    USART2->CR1 &= ~(Map_USART2_CR1_PCE);

    USART2->CR2 &= ~(Map_USART2_CR2_MSBFIRST);
    USART2->CR2 &= ~(Map_USART2_CR2_DATAINV);
    USART2->CR2 &= ~(Map_USART2_CR2_TXINV);
    USART2->CR2 &= ~(Map_USART2_CR2_SWAP);
    USART2->CR2 &= ~(Map_USART2_CR2_STOP0 | Map_USART2_CR2_STOP1);
    USART2->CR2 &= ~(Map_USART2_CR2_CLKEN);

    USART2->CR3 $= ~(Map_USRAT2_CR3_DEM);
    USART2->CR3 &= ~(Map_USART2_CR3_DDRE);
    USART2->CR3 |= Map_USART2_CR3_OVRDIS;
    USART2->CR3 |= Map_USART2_CR3_ONEBIT;
    USART2->CR3 &= ~(Map_USART2_CR3_CTSE);
    USART2->CR3 &= ~(Map_USART2_CR3_RTSE);
    USART2->CR3 &= ~(Map_USART2_CR3_HDSEL);

    USART2->BRR = Map_USART2_BRR_USARTDIV;


    // Not specified if USART must be disabled
    USART2->CR1 &= ~(Map_USART2_CR1_RTOIE);
    USART2->CR1 &= ~(Map_USART2_CR1_CMIE);
    USART2->CR1 &= ~(Map_USART2_CR1_MME);
    USART2->CR1 &= ~(Map_USART2_CR1_TXEIE);
    USART2->CR1 &= ~(Map_USART2_CR1_TCIE);      // Only to create a PoW
    USART2->CR1 |= Map_USART2_CR1_TE;

    USART2->CR2 &= ~(Map_USART2_CR2_ABREN);

    USART2->CR3 &= ~(Map_USART2_CR3_CTSIE);

    USART2->CR3 |= Map_USART2_CR3_DMAT;
    USART2->CR3 |= Map_USART2_CR3_DMAR;
    USART2->CR3 &= ~(Map_USART2_CR3_EIE);

}