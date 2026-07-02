
#define F_CPU 16000000L
#define MESSAGE "Click!"
#define MESS_LEN 6
#define BUFFER_LEN 32

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Defining global variables

typedef struct{
    uint8_t diode_mode : 1;
    uint8_t button_pressed : 1;
    uint8_t flag2 : 1;
    uint8_t flag3 : 1;
    uint8_t flag4 : 1;
    uint8_t flag5 : 1;
    uint8_t flag6 : 1;
    uint8_t flag7 : 1;
} virtual_registry;

volatile virtual_registry FLAGS;

static volatile uint8_t Tx_Buffer[BUFFER_LEN];
static volatile uint8_t head = 0;
static volatile uint8_t tail = 0;

// Setting up the registers

void setup(){
    DDRB = (1 << 5);
    DDRD &= ~(1 << 2);
    PORTD = (1 << 2);
    EICRA = (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK = (1 << INT0);
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C &= ~(1 << USBS0);
    UCSR0C &= ~((1 << UPM01) | (1 << UPM00));       // Not necessary since it is already 0, I made this for educational purpose only
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    sei();
}

// Buffer implemented in order maintain responsiveness of system

void Send_to_TX_Buffer(char* message){
    UCSR0B &= ~(1 << UDRIE0);
    int next_head;
    for (int i = 0; i < MESS_LEN; ++i){
        next_head = (head  + 1) % BUFFER_LEN;
        if (next_head == tail){
            tail = (tail + 1) % BUFFER_LEN;
        }
        Tx_Buffer[head] = MESSAGE[i];
        head = next_head;
    }
    UCSR0B |= (1 << UDRIE0);
}

// ISRs

ISR(INT0_vect){
    FLAGS.button_pressed = 1;
    FLAGS.diode_mode ^= 1;
}

ISR(USART_UDRE_vect){
if (head != tail){
    char data;
    data = Tx_Buffer[tail];
    UDR0 = data;
    tail = (tail +1) % BUFFER_LEN;
} else if (tail == head){
    UCSR0B &= ~(1 << UDRIE0);
}
}


int main(){
    setup();

    while(1){
        if (FLAGS.button_pressed) {
            Send_to_TX_Buffer(MESSAGE);
            FLAGS.button_pressed = 0;
        }
       if (FLAGS.diode_mode == 0){
            PORTB ^= (1 << 5);
            _delay_ms(100);
        }else if (FLAGS.diode_mode == 1){
            PORTB ^= (1 << 5);
            _delay_ms(1000);
        }
   }
}