#include <stdint.h>
#include "stm32f0xx.h"
#include "ADC_cnfg.h"
#include "UART_cnfg.h"
#include "HRM.h"

// in use: ADC1/0 D13 and UART communication 
// IMPORTANT! first setup clocks and used pins then setup USART and ADC

void setup(){

}

int main(){
    setup();
    ADC_setup();
    UART_setup();
    
}