#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "IO_Macros.h"
#include <util/delay.h>

#define greenLedPin  PB1 // Pin 9. Green LED - High Level
#define yellowLedPin PB2 // Pin 10. Yellow LED - Medium Level
#define redLedPin PB3 // Pin 11. Red LED - Low Level
#define depthSensorPin PC0 // Pin A0

void setup() {
	//led output pin setup
    DDRB |= (1 << greenLedPin); 
	DDRB |= (1 << yellowLedPin); 
	DDRB |= (1 << redLedPin); 
	//setup ADC
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX |= (1 << REFS0);
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

//convert reading from depth sensor with ADC and return int value
uint16_t readDepthSensor() {
    ADMUX = (ADMUX & 0xF0) | (depthSensorPin & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

int main(void) {
    setup();
    
    while (1) {
        uint16_t sensorValue = readDepthSensor();
        if(sensorValue < 400) {
			//low water level
            PORTB |= (1 << redLedPin);
			PORTB &= ~(1 << greenLedPin);
			PORTB &= ~(1 << yellowLedPin);
        } else if(sensorValue < 600){
			//medium level
			PORTB |= (1 << yellowLedPin);
			PORTB &= ~(1 << greenLedPin);
			PORTB &= ~(1 << redLedPin);
		} else{
			//high level
			PORTB |= (1 << greenLedPin);
			PORTB &= ~(1 << yellowLedPin);
			PORTB &= ~(1 << redLedPin);
		}
        
        my_delay_ms(100);
    }

}



