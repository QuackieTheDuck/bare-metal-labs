#include <HRM.h>

void DMA_setup(){
    // Need to disable a DMA to configure some bits
    DMA->CCR1 &= ~(HRM_DMA_CCR1_EN);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_EN);
    while ((DMA->CCR1 & HRM_DMA_CCR1_EN) != 0 && (DMA->CCR2 & HRM_DMA_CCR2_EN) != 0)){
        _NOP()
    }

    // DMA_CCR1
    DMA->CCR1 &= ~(HRM_DMA_CCR1_MEM2MEM);
    DMA->CCR1 |= HRM_DMA_CCR1_PL_0;
    DMA->CCR1 &= ~(HRM_DMA_CCR1_PL_1); // priority high
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1
    DMA->CCR1

    // DMA_CCR2
    DMA->CCR2 &= ~(HRM_DMA_CCR2_MEM2MEM);
    DMA->CCR2 &= ~(HRM_DMA_CCR2_PL_0);
    DMA->CCR2 |= HRM_DMA_CCR2_PL_1; //priority medium
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2
    DMA->CCR2

}