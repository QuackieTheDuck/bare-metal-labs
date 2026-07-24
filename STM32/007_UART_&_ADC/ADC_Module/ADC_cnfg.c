#include <HRM.h>

void ADC_setup (){

    // ADC disable since it is required to turn it off to configure ADC
    ADC->CR &= ~(HRM_ADC_CR_ADEN);
    ADC->CR &= ~(HRM_ADC_CR_ADSTART);

    // ADC_CFGR1
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_AWDEN);
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_DISCEN);
    ADC->CFGR1 |= HRM_ADC_CFGR1_WAIT;
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_CONT);
    ADC->CFGR1 |= HRM_ADC_CFGR1_OVRMOD;
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_ALIGN);
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_RES_0 | HRM_ADC_CFGR1_RES_1);
    ADC->CFGR1 |= HRM_ADC_CFGR1_DMAEN;
    ADC->CFGR1 &= ~(HRM_ADC_CFGR1_DMACFG);

    // ADC_SMPR since the analog input will be simulated by potentiometer it is set to 111

    // ADC_CHSELR

    // ADC_CCR

    // Then do the calibration

    // ADC enable after all configuration processes are done
    ADC->CR |= HRM_ADC_CR_ADEN;
}