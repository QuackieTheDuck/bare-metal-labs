#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L
#define BUFFER_LEN 32

// virtual register for storing flags

typedef struct{
    uint8_t flag0 : 1;
    uint8_t diode_mode : 1;
    uint8_t do_calc : 1;
    uint8_t ADC_read_complete : 1;
    uint8_t flag4 : 1;
    uint8_t flag5 : 1;
    uint8_t flag6 : 1;
    uint8_t flag7 : 1;
}virtual_registry;

volatile virtual_registry FLAGS;

// Circular buffer initialization
static volatile uint8_t HEAD = 0;
static volatile uint8_t TAIL = 0;
static volatile uint8_t Tx_Buffer[BUFFER_LEN];
volatile uint16_t ADC_val = 0;

// pin setup
void setup(){
    // Pins configuration
    DDRB |= (1 << 5);
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
    // ISR configuration
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);
    // UART configuration
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00));
    UCSR0C &= ~(1 << USBS0);
    UCSR0C &= ~((1 << UPM01) | (1 << UPM00));
    UCSR0B |= (1 << TXEN0);
    UCSR0B &= ~(1 << RXEN0);
    // ADC configuration
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADIE);
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    ADCSRA |= (1 << ADATE);
    ADCSRA |= (1 << ADSC);
    ADCSRB &= ~(1 << ACME);
    ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
    DIDR0 |= (1 << ADC0D);
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << ADLAR);
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));  // Alternatively ADMUX &= ~(0b00001111) or (0x0F)
    sei();
}

// defining send to buffer function
void Send_to_Tx_Buffer(uint16_t ADC_val){
    UCSR0B &= ~(1 << UDRIE0);
    int next_head;
    // ADCL
    next_head = (HEAD + 1) & (BUFFER_LEN - 1);
    if (next_head == TAIL){
        TAIL = (next_head + 1) & (BUFFER_LEN - 1);
    }
    Tx_Buffer[HEAD] = (uint8_t)(ADC_val & 0xFF);
    HEAD = next_head;
    // ADCH
    next_head = (HEAD + 1) & (BUFFER_LEN - 1);
    if (next_head == TAIL){
        TAIL = (next_head + 1) & (BUFFER_LEN - 1);
    }
    Tx_Buffer[HEAD] = (uint8_t)(ADC_val >> 8);
    HEAD = next_head;
    UCSR0B |= (1 << UDRIE0);
}

// Button 
ISR(INT0_vect){
    FLAGS.diode_mode ^= 1;
    FLAGS.do_calc = 1;
}

// UART
ISR(USART_UDRE_vect){
    if(TAIL != HEAD){
    uint8_t data;
    data = Tx_Buffer[TAIL];
    UDR0 = data;
    TAIL = (TAIL + 1) % BUFFER_LEN;
    } else if (TAIL == HEAD){
        UCSR0B &= ~(1 << UDRIE0);
    }

}

// ADC
ISR(ADC_vect){
    ADC_val = ADC;
    FLAGS.ADC_read_complete = 1;
}

int main(){
    setup();

    uint16_t diode_freq;

    while (1){
        if (FLAGS.ADC_read_complete){
            Send_to_Tx_Buffer(ADC_val);
            FLAGS.ADC_read_complete = 0;
        }
        if ( FLAGS.diode_mode == 0){
            if(FLAGS.do_calc){
                diode_freq = 500 + (ADC_val << 2);
                FLAGS.do_calc = 0;
            }
            PORTB ^= (1 << 5);
            for (uint16_t i = 0; i <  diode_freq; i++ ){
                _delay_ms(1);
            }
        } else if (FLAGS.diode_mode == 1){
            PORTB ^= (1 << 5);
            _delay_ms(500);
        }
    }
}

// obserwed binary transmission of values from 0 to ~1000 which means the uart raporting is properly implemented

// transmission could be better and whole program could be optimalised more

// aware of certain flaws of this program and much richer with knowledge i've decided to move on to the stm32 and maybe someday i'll return to the arduino to do a little show off