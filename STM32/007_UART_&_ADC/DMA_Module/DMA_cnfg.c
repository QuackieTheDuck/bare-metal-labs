#include <HRM.h>

void DMA_setup(){
    // Need to disable a DMA to configure some bits
    DMA->CCR1 &= ~(HRM_DMA_CCR1_EN);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_EN);
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) != 0 && (DMA->CCR2 & HRM_DMA_CCR2_EN) != 0)){
        _NOP()
    }

    // DMA_CCR1 from ADC to MEM
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MEM2MEM);
    DMA->CCR1 |= HRM_DMA_CCR1_PL_0;
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PL_1); // priority high
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MSIZE_0);
    DMA->CCR1 |= HRM_DMA_CCR1_MSIZE_1;  // 16 bits, whole data at once
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PSIZE_0);
    DMA->CCR1 |= HRM_DMA_CCR1_PSIZE_1;
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MINC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PINC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_CIRC);
    DMA->CCR1 &= ~(HRM_DMA_CCR1_DIR);
    DMA->CCR1 |= HRM_DMA_CCR1_TEIE;
    DMA->CCR1 |= HRM_DMA_CCR1_TCIE;

    // DMA_CCR2 from MEM to UART
    DMA->CCR2 &= ~(HRM_DMA_CCR2_MEM2MEM);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_PL_0);
    DMA->CCR2 |= HRM_DMA_CCR2_PL_1; //priority medium
    // since the data is transfered from 16bit mem variable in 8 bit chunks - two transfers, 8bit each
    DMA->CCR2 &= ~(HRM_DMA_CCR2_MSIZE_0);
    DMA->CCR2 =| HRM_DMA_CCR2_MSIZE_1;
    DMA->CCR2 &= ~( HRM_DMA_CCR2_PSIZE_0 | HRM_DMA_CCR2_PSIZE_1 );
    DMA->CCR2 |= HRM_DMA_CCR2_MINC;
    DMA->CCR2 &= ~(HRM_DMA_CCR2_PINC);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_CIRC);
    DMA->CCR2 |= HRM_DMA_CCR2_DIR;
    DMA->CCR2 |= HRM_DMA_CCR2_TEIE;
    DMA->CCR2 |= HRM_DMA_CCR2_TCIE;

    // DMA_CNDTR1

    // DMA_CNDTR2

    // DMA_CPAR1

    // DMA_CPAR2

}