#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );

volatile uint16_t counter = 0;

int main(void) {
    DDRD |= (1 << PIND2); // Set PD2 (pin 2) as output for triggering the ultrasonic sensor
    DDRD &= ~(1 << PIND3); // Set PD3 (pin 3) as input for receiving echo from the ultrasonic sensor
    USART_Init(MYUBRR); // Initialize USART
    sei(); // Enable global interrupts

    while (1) {
        PORTD |= (1 << PIND2); // Send 10us pulse to trigger ultrasonic sensor
        _delay_us(10);
        PORTD &= ~(1 << PIND2);

        // Wait for the echo signal
        while (!(PIND & (1 << PIND3))) {}

        // Measure the pulse duration
        counter = 0;
        while (PIND & (1 << PIND3)) {
            _delay_us(1);
            counter++;
        }

        // Calculate distance in centimeters
        // Formula: Distance in cm = (Duration of high level pulse * Speed of sound) / (2 * 10^4)
        uint16_t distance = (counter * 0.034) / 2;

        // Print distance to serial monitor
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Distance: %d cm\r\n", distance);
        for (uint8_t i = 0; buffer[i] != '\0'; i++) {
            USART_Transmit(buffer[i]);
        }

        _delay_ms(500); // Wait for 500ms before next measurement
    }

    return 0;
}

void USART_Init( unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format: 8data, 1stop bit
    UCSR0C = (3<<UCSZ00);
}

void USART_Transmit( unsigned char data ) {
    // Wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );
    // Put data into buffer, sends the data
    UDR0 = data;
}
