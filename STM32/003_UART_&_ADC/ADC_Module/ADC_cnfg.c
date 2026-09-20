#include <HRM.h>
#include <stdint.h>
#include "stm32f0xx.h"

void ADC_setup (){

    // ADC disable since it is required to turn it off to configure ADC
    ADC->CR |= 

    // ADC_CFGR1
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_AWDEN);
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_DISCEN);
    ADC1->CFGR1 |= HRM_ADC_CFGR1_WAIT;
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_CONT);
    ADC1->CFGR1 |= HRM_ADC_CFGR1_OVRMOD;
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_ALIGN);
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_RES_0 | HRM_ADC_CFGR1_RES_1);  // set to 12bit res
    ADC1->CFGR1 |= HRM_ADC_CFGR1_DMAEN;
    ADC1->CFGR1 &= ~(HRM_ADC_CFGR1_DMACFG);

    // ADC_SMPR since the analog input will be simulated by potentiometer it is set to 111
    ADC1->SMPR |= (HRM_ADC_SMPR_SMP_0 | HRM_ADC_SMPR_SMP_1 | HRM_ADC_SMPR_SMP_2);

    // ADC_CHSELR
    ADC1->CHSELR |= HRM_ADC_CHSELR_0;

    // ADC_CCR
    ADC->CCR &= ~(HRM_ADC_CCR_VREFEN);

    // ADC calibration
    ADC1->CR |= HRM_ADC_CR_ADCAL;
    while (( ADC1->CR & HRM_ADC_CR_ADCAL) != 0){
        __NOP();
    }

    // ADC enable
    ADC1->ISR |= HRM_ADC_ISR_ADRDY;
    ADC1->CR |= HRM_ADC_CR_ADEN;
    while ((ADC1->ISR & HRM_ADC_ISR_ADRDY) == 0){
        __NOP();
    }
}