#ifndef Map_H_
#define Map_H_

/*=============================================================*/
/*                  Hardware Registers Mapping                 */
/*=============================================================*/


//================= Reset and clock control (RCC) ==============



//==============================================================


//================= USART2 CONFIGURATION ========================

//================= USART2 Control register 1 (USART1_CR1) ======
#define Map_USART2_CR1_M0       (1 << 12)   // Word lenght bit 0
#define Map_USART2_CR1_M1       (1 << 28)   // Word lenght bit 1
#define Map_USART2_CR1_RTOIE    (1 << 26)   // Reciever timeout interrupt enable
#define Map_USART2_CR1_OVER8    (1 << 15)   // Oversampling mode
#define Map_USART2_CR1_CMIE     (1 << 14)   // Character match interrupt enable
#define Map_USART2_CR1_MME      (1 << 13)   // Mute mode enable
#define Map_USART2_CR1_PCE      (1 << 10)   // Parity control enable
#define Map_USART2_CR1_TXEIE    (1 << 7)    // TX Data register empty interrupt enable
#define Map_USART2_CR1_TCIE     (1 << 6)    // Transmission complete interrupt enable
#define Map_USART2_CR1_TE       (1 << 3)    // Transmitter enable
#define Map_USART2_CR1_UE       (1 << 0)    // Uart enable

//================= USART2 Control register 2 (USART2_CR2) ======
#define Map_USART2_CR2_RTOEN    (1 << 23)   // Reciever timeout enable
#define Map_USART2_CR2_ABREN    (1 << 20)   // Auto baud rate enable
#define Map_USART2_CR2_MSBFIRST (1 << 19)   // MSB first
#define Map_USART2_CR2_DATAINV  (1 << 18)   // Data logic values inversion
#define Map_USART2_CR2_TXINV    (1 << 17)   // TX logic values inversion
#define Map_USART2_CR2_SWAP     (1 << 15)   // SWAP TX with RX
#define Map_USART2_CR2_STOP0    (1 << 12)   // STOP bit 0
#define Map_USART2_CR2_STOP1    (1 << 13)   // STOP bit 1
#define Map_USART2_CR2_CLKEN    (1 << 11)   // Clock enable (SWITCHES UART to USART!)

//================= USART Control register 3 (USART2_CR3)========
#define Map_USRAT2_CR3_DEM      (1 << 14)   // Driver enable mode
#define Map_USART2_CR3_DDRE     (1 << 13)   // DMA disbale on reception error 
#define Map_USART2_CR3_OVRDIS   (1 << 12)   // Overrun disable 
#define Map_USART2_CR3_ONEBIT   (1 << 11)   // One bit sample method
#define Map_USART2_CR3_CTSIE    (1 << 10)   // CTS interupt enable
#define Map_USART2_CR3_CTSE     (1 << 9)    // Clear to send enable
#define Map_USART2_CR3_RTSE     (1 << 8)    // Request to send enable 
#define Map_USART2_CR3_DMAT     (1 << 7)    // DMA enable transmitter
#define Map_USART2_CR3_DMAR     (1 << 6)    // DMA enable reciever
#define Map_USART2_CR3_HDSEL    (1 << 3)    // Half-dupplex mode selection
#define Map_USART2_CR3_EIE      (1 << 0)    // Error interrupt enable

//================ USART2 Baud rate register (USART2_BRR) =======
#define Map_USART2_BAUDRATE      115200UL   // USART Baudrate
#define Map_SYSTEM_CORE_CLOCK   8000000UL  // System core clock 
#define Map_USART2_BRR_USARTDIV     ((HRM_SYSTEM_CORE_CLOCK + HRM_USART_BAUDRATE/2) / HRM_USART_BAUDRATE)  // USARTDIV value

//====== USART2 interrupt and status register (USART2_ISR) ======
#define Map_USART2_ISR_TXE      (1 << 7)    // Transmission data register empty

//====== USART2 interrupt flag clear register (USART2_ICR) ======
#define Map_USART2_ICR_TCCF    (1 << 6)     // Transmission complete flag clear 

//===============================================================


#endif /* Map_H_ */