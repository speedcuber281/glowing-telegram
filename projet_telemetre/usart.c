/*
 * usart.c
 *
 * Created: 28/04/2023 14:49:53
 *  Author: brunaud10
 */ 

#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void USART_Init( unsigned int baudrate )
{
	/* Set the baud rate */
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;
	
	/* RAZ du registre de controle A	*/
	UCSR0A = 0x00 ;

	/* Enable UART receiver and transmitter */
	UCSR0B = ( ( 1 << RXEN0 ) | ( 1 << TXEN0 ) | (1<<RXCIE0));
	
	/* Set frame format: 8 data 2stop */
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
}

unsigned char USART_Receive( void )
{
	/* Wait for incomming data */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	
	/* Return the data */
	return UDR0;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) )
	;
	/* Start transmittion */
	UDR0 = data;
}