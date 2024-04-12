#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "IO_Macros.h"
#include <util/delay.h>

#define greenLedPin  PB1 // Pin 9. Green LED - High Level
#define yellowLedPin PB2 // Pin 10. Yellow LED - Medium Level
#define redLedPin PB3 // Pin 11. Red LED - Low Level
volatile int count;

ISR(INT0_vect)
{
    count = count + 1;
}

void setup() {
	count = 0;
}



/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int delay) 
{
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i < delay % 10; i++)
	{
		_delay_ms(1);
	}
}


int main(void) {
	EICRA &= ~3;  // clear existing flags
	EICRA |= 2;   // set flags (negative edge interrupt)
	EIMSK |= 1;   //enable interrupt
	sei();
    setup();
	while(1){
		int tempCount = count;
		float freq = tempCount/1;
		//q = (L/min)
		//senor range: 0.3 - 6 L/min
		float q = freq/98;
		if(q > 0.3){
			//low water speed
            PORTB |= (1 << redLedPin);
			PORTB &= ~(1 << greenLedPin);
			PORTB &= ~(1 << yellowLedPin);
		} else if(q > 3){
			//medium water speed
			PORTB |= (1 << yellowLedPin);
			PORTB &= ~(1 << greenLedPin);
			PORTB &= ~(1 << redLedPin);
		} else if(q > 5){
			//high water speed
			PORTB |= (1 << greenLedPin);
			PORTB &= ~(1 << yellowLedPin);
			PORTB &= ~(1 << redLedPin);
		} else{
			//water speed too low for sensor
			PORTB &= ~(1 << greenLedPin);
			PORTB &= ~(1 << yellowLedPin);
			PORTB &= ~(1 << redLedPin);
		}
		count = 0;
		_delay_ms(1000);
	}
}





