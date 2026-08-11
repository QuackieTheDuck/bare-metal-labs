#include <stdint.h>
#include "stm32f0xx.h"
#include "ADC_cnfg.h"
#include "UART_cnfg.h"
#include "HRM.h"
#include "DMA_cnfg.h"

// in use: ADC1/0 D13 and UART communication 
// IMPORTANT! first setup clocks and used pins then setup USART and ADC

void setup(){

}

int main(){

    // DMA data variable 
    volatile uint16_t DMA_data = 0;

    // Setup functions
    setup();
    ADC_setup();
    UART_setup();
    DMA_setup();
    
}