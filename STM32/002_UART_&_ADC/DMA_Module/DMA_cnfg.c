#include <HRM.h>
#include <stdint.h>
#include "stm32f0xx.h"

void DMA_setup(volatile uint16_t *DMA_data){

    // Need to disable a DMA to configure some bits
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_EN);
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_EN);
    while ((DMA1_Channel1->CCR & HRM_DMA_CCR1_EN) != 0 || (DMA1_Channel2->CCR & HRM_DMA_CCR2_EN) != 0){
        __NOP();
    }

    // DMA_CCR1 from ADC to MEM
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_MEM2MEM);
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_PL_0);
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_PL_1; // priority high
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_MSIZE_0;
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_MSIZE_1);  // 16 bits, whole data at once
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_PSIZE_0;
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_PSIZE_1);
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_MINC);
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_PINC);
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_CIRC);
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_DIR);
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_TEIE;
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_TCIE;

    // DMA_CCR2 from MEM to UART
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_MEM2MEM);
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_PL_0;
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_PL_1); //priority medium
    // since the data is transfered from 16bit mem variable in 8 bit chunks - two transfers, 8bit each
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_MSIZE_0 | HRM_DMA_CCR2_MSIZE_1);
    DMA1_Channel2->CCR &= ~( HRM_DMA_CCR2_PSIZE_0 | HRM_DMA_CCR2_PSIZE_1 );
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_MINC;
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_PINC);
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_CIRC);
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_DIR;
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_TEIE;
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_TCIE;

    // DMA_CPAR1
    DMA1_Channel1->CPAR = HRM_DMA_CPAR1_VALUE;

    // DMA_CPAR2
    DMA1_Channel2->CPAR = HRM_DMA_CPAR2_VALUE;

    // DMA_CMAR1
    DMA1_Channel1->CMAR = (uint32_t)DMA_data;

    // DMA_CMAR2
    DMA1_Channel2->CMAR = (uint32_t)DMA_data;

    // DMA enable
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_EN;
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_EN;
    while ((DMA1_Channel1->CCR & HRM_DMA_CCR1_EN) == 0 || (DMA1_Channel2->CCR & HRM_DMA_CCR2_EN) == 0){
        __NOP();
    }

}

void trigger_DMA1 (){
    // Reseting flags, setting counter etc for DMA channel 1

    // Disable DMA channel 1
    DMA1_Channel1->CCR &= ~(HRM_DMA_CCR1_EN);
    while ((DMA1_Channel1->CCR & HRM_DMA_CCR1_EN) != 0 ){
        __NOP();
    }

    // DMA_CNDTR1
    DMA1_Channel1->CNDTR = HRM_DMA_CNDTR1_VALUE;

    // Clearing flags for DMA channel 1
    DMA1->IFCR |= HRM_DMA_IFCR_CGIF1;

    // Enabling DMA channel 1
    DMA1_Channel1->CCR |= HRM_DMA_CCR1_EN;
    while ((DMA1_Channel1->CCR & HRM_DMA_CCR1_EN) == 0 ){
        __NOP();
    }


}

void trigger_DMA2 (){
    // Reseting flags, setting counter etc for DMA channel 2

    // Disabling DMA channel 2
    DMA1_Channel2->CCR &= ~(HRM_DMA_CCR2_EN);
    while ((DMA1_Channel2->CCR & HRM_DMA_CCR2_EN) != 0){
        __NOP();
    }

    // DMA_CNDTR2
    DMA1_Channel2->CNDTR = HRM_DMA_CNDTR2_VALUE;

    // Clearing flags for DMA channel 2
    DMA1->IFCR |= HRM_DMA_IFCR_CGIF2;

    // Enabling DMA channel 2
    DMA1_Channel2->CCR |= HRM_DMA_CCR2_EN;
    while ((DMA1_Channel2->CCR & HRM_DMA_CCR2_EN) == 0){
        __NOP();
    }

}