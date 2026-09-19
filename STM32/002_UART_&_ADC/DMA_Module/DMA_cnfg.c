#include <HRM.h>

void DMA_setup(volatile uint16_t *DMA_data){

    // Need to disable a DMA to configure some bits
    DMA->CCR1 &= ~(HRM_DMA_CCR1_EN);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_EN);
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) != 0 || (DMA->CCR2 & HRM_DMA_CCR2_EN) != 0){
        __NOP();
    }

    // DMA_CCR1 from ADC to MEM
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MEM2MEM);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PL_0);
    DMA->CCR1 |= HRM_DMA_CCR1_PL_1; // priority high
    DMA->CCR1 |= HRM_DMA_CCR1_MSIZE_0;
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MSIZE_1);  // 16 bits, whole data at once
    DMA->CCR1 |= HRM_DMA_CCR1_PSIZE_0;
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PSIZE_1);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MINC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PINC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_CIRC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_DIR);
    DMA->CCR1 |= HRM_DMA_CCR1_TEIE;
    DMA->CCR1 |= HRM_DMA_CCR1_TCIE;

    // DMA_CCR2 from MEM to UART
    DMA->CCR2 &= ~(HRM_DMA_CCR2_MEM2MEM);
    DMA->CCR2 |= HRM_DMA_CCR2_PL_0;
    DMA->CCR2 &= ~(HRM_DMA_CCR2_PL_1); //priority medium
    // since the data is transfered from 16bit mem variable in 8 bit chunks - two transfers, 8bit each
    DMA->CCR2 &= ~(HRM_DMA_CCR2_MSIZE_0 | HRM_DMA_CCR2_MSIZE_1);
    DMA->CCR2 &= ~( HRM_DMA_CCR2_PSIZE_0 | HRM_DMA_CCR2_PSIZE_1 );
    DMA->CCR2 |= HRM_DMA_CCR2_MINC;
    DMA->CCR2 &= ~(HRM_DMA_CCR2_PINC);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_CIRC);
    DMA->CCR2 |= HRM_DMA_CCR2_DIR;
    DMA->CCR2 |= HRM_DMA_CCR2_TEIE;
    DMA->CCR2 |= HRM_DMA_CCR2_TCIE;

    // DMA_CPAR1
    DMA->CPAR1 = HRM_DMA_CPAR1_VALUE;

    // DMA_CPAR2
    DMA->CPAR2 = HRM_DMA_CPAR2_VALUE;

    // DMA_CMAR1
    DMA->CMAR1 = (uint32_t)DMA_data;

    // DMA_CMAR2
    DMA->CMAR2 = (uint32_t)DMA_data;

    // DMA enable
    DMA->CCR1 |= HRM_DMA_CCR1_EN;
    DMA->CCR2 |= HRM_DMA_CCR2_EN;
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) == 0 || (DMA->CCR2 & HRM_DMA_CCR2_EN) == 0){
        __NOP();
    }

}

void trigger_DMA1 (){
    // Reseting flags, setting counter etc for DMA channel 1

    // Disable DMA channel 1
    DMA->CCR1 &= ~(HRM_DMA_CCR1_EN);
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) != 0 ){
        __NOP();
    }

    // DMA_CNDTR1
    DMA->CNDTR1 = HRM_DMA_CNDTR1_VALUE;

    // Clearing flags for DMA channel 1
    DMA->IFCR |= HRM_DMA_IFCR_CGIF1;

    // Enabling DMA channel 1
    DMA->CCR1 |= HRM_DMA_CCR1_EN;
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) == 0 ){
        __NOP();
    }


}

void trigger_DMA2 (){
    // Reseting flags, setting counter etc for DMA channel 2

    // Disabling DMA channel 2
    DMA->CCR2 &= ~(HRM_DMA_CCR2_EN);
    while ((DMA->CCR2 & HRM_DMA_CCR2_EN) != 0){
        __NOP();
    }

    // DMA_CNDTR2
    DMA->CNDTR2 = HRM_DMA_CNDTR2_VALUE;

    // Clearing flags for DMA channel 2
    DMA->IFCR |= HRM_DMA_IFCR_CGIF2;

    // Enabling DMA channel 2
    DMA->CCR2 |= HRM_DMA_CCR2_EN;
    while ((DMA->CCR2 & HRM_DMA_CCR2_EN) == 0){
        __NOP();
    }

}