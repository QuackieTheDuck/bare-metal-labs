#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void setup(){
    DDRB |= (1 << 5);
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
    sei();
}

typedef struct {
    uint8_t flag0 : 1;
    uint8_t flag1 : 1;
    uint8_t flag2 : 1;
    uint8_t flag3 : 1;
    uint8_t flag4 : 1;
    uint8_t flag5 : 1;
    uint8_t flag6 : 1;
    uint8_t flag7 : 1;
} virtual_register;

volatile virtual_register FLAGS;

ISR(INT0_vect){
    if (FLAGS.flag0 == 1){
        FLAGS.flag0 = 0;
    }else if (FLAGS.flag0 == 0){
        FLAGS.flag0 = 1;
    }
}

int main(){
   setup();

   while(1){
    if (FLAGS.flag0 == 0){
        PORTB ^= (1 << 5);
        _delay_ms(100);
    }else if (FLAGS.flag0 == 1){
        PORTB ^= (1 << 5);
        _delay_ms(1000);
    }
   }
}