#ifndef HRM_H_
#define HRM_H_

/*=============================================================*/
/*                  Hardware Registers Mapping                 */
/*=============================================================*/

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
#define HRM_USART_BAUDRATE      115200UL  // USART Baudrate
#define HRM_SYSTEM_CORE_CLOCK   8000000UL  // System core clock 
#define HRM_USART_BRR_USARTDIV     ((HRM_SYSTEM_CORE_CLOCK + HRM_USART_BAUDRATE/2) / HRM_USART_BAUDRATE)  // USARTDIV value

//==============================================================


//================== ADC CONFIGURATION =========================

// --- AHB peripheral clock enable register (RCC_AHBENR) ---
#define HRM_RCC_AHBENR_DMAEN

// --- APB peripherial clock enable register 2 (RCC_APB2ENR) ---
#define HRM_RCC_APB2ENR_USART1EN
#define HRM_RCC_APB2ENR_ADCEN

// --- ADC control register (ADC_CR) --- // Here i need to add some bits since calibration is required everytime after reset.  ADCAL ADDIS
#define HRM_ADC_CR_ADSTART      (1 << 2)  // ADC start conversion command
#define HRM_ADC_CR_ADEN         (1 << 0)  // ADC enable
#define HRM_ADC_CR_
#define HRM_ADC_CR_

// --- ADC configuration register 1 (ADC_CFGR1) ---
#define HRM_ADC_CFGR1_AWDEN     (1 << 23)  // Analog watchdog enable 
#define HRM_ADC_CFGR1_DISCEN    (1 << )
#define HRM_ADC_CFGR1_WAIT      (1 << 14)  // Wait conversion mode
#define HRM_ADC_CFGR1_CONT      (1 << )
#define HRM_ADC_CFGR1_OVRMOD    (1 << )
#define HRM_ADC_CFGR1_ALIGN     (1 << )
#define HRM_ADC_CFGR1_RES_0     (1 << )
#define HRM_ADC_CFGR1_RES_1     (1 << )
#define HRM_ADC_CFGR1_DMACFG    (1 << )
#define HRM_ADC_CFGR1_DMAEN     (1 << )

// --- ADC sampling time register (ADC_SMPR) ---
#define HRM_ADC_SMPR_SMP_0      (1 << )
#define HRM_ADC_SMPR_SMP_1      (1 << )
#define HRM_ADC_SMPR_SMP_2      (1 << )

// --- ADC channel selection register (ADC_CHSELR) ---
#define HRM_ADC_CHSELR_0        (1 << 0)  // Channel 0 selection

// --- ADC common configuration register (ADC_CCR) ---
#define HRM_ADC_CCR_VREFEN      (1 << 22)  // V_refinit enable

// need to map dr address

#endif /* HRM_H_ */