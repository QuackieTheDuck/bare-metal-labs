#ifndef HRM_H_
#define HRM_H_

/*=============================================================*/
/*                  Hardware Registers Mapping                 */
/*=============================================================*/


//================= Reset and clock control (RCC) ==============

// --- Clock configuration register (RCC_CFGR) ---

// --- AHB peripheral clock enable register (RCC_AHBENR) ---
#define HRM_RCC_AHBENR_DMAEN    (1 << 0)  // DMA clock enable

// --- APB peripherial clock enable register 2 (RCC_APB2ENR) ---
#define HRM_RCC_APB2ENR_USART1EN    (1 << 14)  // USART1 clock enable
#define HRM_RCC_APB2ENR_ADCEN       (1 << 9)   // ADC interface clock enable

//==============================================================


//========================== GPIOA ============================ 

// ---  ---

// ---  ---

//=============================================================


//================= USART CONFIGURATION ========================

// --- USART Control Register 1 (USART_CR1) ---
#define HRM_USART_CR1_M0    (1 << 12)  // Word lenght bit 0
#define HRM_USART_CR1_M1    (1 << 28)  // Word lenght bit 1
#define HRM_USART_CR1_OVER8 (1 << 15)  // Oversampling mode
#define HRM_USART_CR1_PCE   (1 << 10)  // Parity control enable
#define HRM_USART_CR1_TE    (1 << 3)   // Transmitter enable
#define HRM_USART_CR1_UE    (1 << 0)   // USART enable

// --- USART Control Register 2 (USART_CR2) ---
#define HRM_USART_CR2_ABREN     (1 << 20)  // Auto baud rate enable
#define HRM_USART_CR2_MSBFIRST  (1 << 19)  // Most significant bit first
#define HRM_USART_CR2_DATAINV   (1 << 18)  // Binary data inversion
#define HRM_USART_CR2_TXINV     (1 << 17)  // TX active level inversion
#define HRM_USART_CR2_SWAP      (1 << 15)  // Swap TX with RX
#define HRM_USART_CR2_STOP_0    (1 << 12)  // STOP bit 0
#define HRM_USART_CR2_STOP_1    (1 << 13)  // STOP bit 1

// --- USART Baud rate register (USART_BRR) ---
#define HRM_USART_BAUDRATE      115200UL   // USART Baudrate
#define HRM_SYSTEM_CORE_CLOCK   8000000UL  // System core clock 
#define HRM_USART_BRR_USARTDIV     ((HRM_SYSTEM_CORE_CLOCK + HRM_USART_BAUDRATE/2) / HRM_USART_BAUDRATE)  // USARTDIV value

//==============================================================


//================== ADC CONFIGURATION =========================

// --- ADC interrupt and status register (ADC_ISR) ---
#define HRM_ADC_ISR_EOC     (1 << 2)   // End of conversion
#define HRM_ADC_ISR_ADRDY   (1 << 0)   // ADC ready
 
// --- ADC control register (ADC_CR) --- 
#define HRM_ADC_CR_ADSTART      (1 << 2)   // ADC start conversion command
#define HRM_ADC_CR_ADEN         (1 << 0)   // ADC enable
#define HRM_ADC_CR_ADCAL        (1U << 31)  // ADC calibration
#define HRM_ADC_CR_ADSTART      (1 << 2)   // ADC start conversion

// --- ADC configuration register 1 (ADC_CFGR1) ---
#define HRM_ADC_CFGR1_AWDEN     (1 << 23)  // Analog watchdog enable 
#define HRM_ADC_CFGR1_DISCEN    (1 << 16)  // Discontinous mode
#define HRM_ADC_CFGR1_WAIT      (1 << 14)  // Wait conversion mode
#define HRM_ADC_CFGR1_CONT      (1 << 13)  // Single/continous mode 
#define HRM_ADC_CFGR1_OVRMOD    (1 << 12)  // Overrun management mode 
#define HRM_ADC_CFGR1_ALIGN     (1 << 5)   // Data alignment
#define HRM_ADC_CFGR1_RES_0     (1 << 3)   // Data resolution bit 0
#define HRM_ADC_CFGR1_RES_1     (1 << 4)   // Data resolution bit 1
#define HRM_ADC_CFGR1_DMACFG    (1 << 1)   // Direct memory access configuration
#define HRM_ADC_CFGR1_DMAEN     (1 << 0)   // Direct memory access enable

// --- ADC sampling time register (ADC_SMPR) ---
#define HRM_ADC_SMPR_SMP_0      (1 << 0)  // Sampling time selection bit 0
#define HRM_ADC_SMPR_SMP_1      (1 << 1)  // Sampling time selection bit 1
#define HRM_ADC_SMPR_SMP_2      (1 << 2)  // Sampling time selection bit 2

// --- ADC channel selection register (ADC_CHSELR) ---
#define HRM_ADC_CHSELR_0        (1 << 0)  // ADC channel 0 selection

// --- ADC common configuration register (ADC_CCR) ---
#define HRM_ADC_CCR_VREFEN      (1 << 22)  // V_refinit enable

// --- ADC data registry (ADC_DR) ---
#define HRM_ADC_DR_DATA_MASK    (0xFFF)  // Mask used for data reading
#define HRM_ADC_DR_DATA_OFFSET  (0)      // Data offset

//=============================================================


//================== DMA configuration ========================

// --- DMA interrupt status registers (DMA_ISR) ---
#define HRM_DMA_ISR_TCIF1       (1 << 1)  // Transfer complete flag for channel 1
#define HRM_DMA_ISR_HTIF1       (1 << 2)  // Half transfer flag for channel 1
#define HRM_DMA_ISR_TEIF1       (1 << 3)  // Transfer error flag fo channel 1
#define HRM_DMA_ISR_TCIF2       (1 << 5)  // Transfer complete flag for channel 2
#define HRM_DMA_ISR_HTIF2       (1 << 6)  // Half transfer flag for channel 2
#define HRM_DMA_ISR_TEIF2       (1 << 7)  // Transfer error flag for channel 2

// --- DMA interrupt clear register (DMA_IFCR) ---
#define HRM_DMA_IFCR_CGIF1      (1 << 0)  // Global interrupt flag clear for channel 1
#define HRM_DMA_IFCR_CGIF2      (1 << 4)  // Global interrupt flag clear for channel 2

//--- DMA channel 1 configuration register (DMA_CCR1) ---
#define HRM_DMA_CCR1_MEM2MEM    (1 << 14)  // Memory-to-memory mode
#define HRM_DMA_CCR1_PL_0       (1 << 12)  // Priority level bit 0
#define HRM_DMA_CCR1_PL_1       (1 << 13)  // Priority level bit 1
#define HRM_DMA_CCR1_MSIZE_0    (1 << 10)  // Memory size bit 0
#define HRM_DMA_CCR1_MSIZE_1    (1 << 11)  // Memory size bit 1
#define HRM_DMA_CCR1_PSIZE_0    (1 << 8)  // Peripheral size bit 0
#define HRM_DMA_CCR1_PSIZE_1    (1 << 9)   // Peripheral size bit 1
#define HRM_DMA_CCR1_MINC       (1 << 7)   // Memory increment mode
#define HRM_DMA_CCR1_PINC       (1 << 6)   // Pheripheral increment  mode
#define HRM_DMA_CCR1_CIRC       (1 << 5)   // Circural mode
#define HRM_DMA_CCR1_DIR        (1 << 4)   // Data transfer direction
#define HRM_DMA_CCR1_TEIE       (1 << 3)   // Transfer error interrupt enable
#define HRM_DMA_CCR1_TCIE       (1 << 1)   // Transfer complete interrupt enable
#define HRM_DMA_CCR1_EN         (1 << 0)   // Channel enable

//--- DMA channel 2 configuration register (DMA_CCR2) ---
#define HRM_DMA_CCR2_MEM2MEM    (1 << 14)  // Memory-to-memory mode
#define HRM_DMA_CCR2_PL_0       (1 << 12)  // Priority level bit 0
#define HRM_DMA_CCR2_PL_1       (1 << 13)  // Priority level bit 1
#define HRM_DMA_CCR2_MSIZE_0    (1 << 10)  // Memory size bit 0
#define HRM_DMA_CCR2_MSIZE_1    (1 << 11)  // Memory size bit 1
#define HRM_DMA_CCR2_PSIZE_0    (1 << 8)   // Peripheral size bit 0
#define HRM_DMA_CCR2_PSIZE_1    (1 << 9)   // Peripheral size bit 1
#define HRM_DMA_CCR2_MINC       (1 << 7)   // Memory increment mode
#define HRM_DMA_CCR2_PINC       (1 << 6)   // Pheripheral increment mode
#define HRM_DMA_CCR2_CIRC       (1 << 5)   // Circural mode
#define HRM_DMA_CCR2_DIR        (1 << 4)   // Data transfer direction
#define HRM_DMA_CCR2_TEIE       (1 << 3)   // Transfer error interrupt enable
#define HRM_DMA_CCR2_TCIE       (1 << 1)   // Transfer complete interrupt enable
#define HRM_DMA_CCR2_EN         (1 << 0)   // Channel enable


//--- DMA channel 1 number of data to transfer register (DMA_CNDTR1) ---
#define HRM_DMA_CNDTR1_VALUE    (1)  // Number of data to transfer

//--- DMA channel 2 number of data to transfer register (DMA_CNDTR2) ---
#define HRM_DMA_CNDTR2_VALUE    (2)  // Number of data to transfer

//--- DMA channel 1 peripheral address register (DMA_CPAR1) ---
#define HRM_DMA_CPAR1           (0x40012440)  // An absolute address

//--- DMA channel 2 peripheral address register (DMA_CPAR2) ---
#define HRM_DMA_CPAR2           (0x40013828)  // An absolute address

//--- DMA channel selection register (DMA_CSELR) ---
#define HRM_DMA_CSELR_C1S_BIT_0     (1 << 0)  // 
#define HRM_DMA_CSELR_C2S_BIT_0     (1 << 4)  // 

//=============================================================


#endif /* HRM_H_ */