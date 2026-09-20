#include <stdint.h>
#include "stm32f0xx.h"
#include "ADC_cnfg.h"
#include "UART_cnfg.h"
#include "HRM.h"
#include "DMA_cnfg.h"
#include "delay_ms.h"

// in use: ADC1/0 D13 and UART communication 
// IMPORTANT! first setup clocks and used pins then setup USART and ADC

// Setiing up clocks and GPIOA
void setup(){

    // clocks enable
    RCC->AHBENR |= HRM_RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= HRM_RCC_AHBENR_SRAMEN;
    RCC->AHBENR |= HRM_RCC_AHBENR_DMAEN;
    RCC->APB2ENR |= HRM_RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= HRM_RCC_APB2ENR_ADCEN;

    
}

// Global Variables

// DMA data variable 
static volatile uint16_t DMA_data = 0;

int main(){

    // Setup functions
    setup();
    delay_setup();
    ADC_setup();
    UART_setup();
    DMA_setup(&DMA_data);

    // "warm up" need to start the cycle 
    trigger_DMA1();
    ADC1->CR |= HRM_ADC_CR_ADSTART;

    while(1){
        // implement logic here
        // waiting for an adc
        // then sending it to the memory via dma1
        // from memory to uart via dma 2
        // repeat in cycle 

        if (DMA1->ISR & HRM_DMA_ISR_TCIF1){
            trigger_DMA2();
            // Clearing flags for DMA channel 1
            DMA1->IFCR |= HRM_DMA_IFCR_CGIF1;
        }
        if (DMA1->ISR & HRM_DMA_ISR_TCIF2){
            trigger_DMA1();
            // Clearing flags for DMA channel 2
            DMA1->IFCR |= HRM_DMA_IFCR_CGIF2;
            //GPIOA->ODR ^= (1 << 5);
            ADC1->CR |= HRM_ADC_CR_ADSTART;
        }
        GPIOA->ODR ^= (1 << 5);
        delay_ms(1000); 

    }
    
}