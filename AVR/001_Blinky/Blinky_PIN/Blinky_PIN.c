#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

int main(void){
  DDRB |= (1 << 5);
  while (1){
    PINB = (1 << 5);
    _delay_ms(1000);
  }
}