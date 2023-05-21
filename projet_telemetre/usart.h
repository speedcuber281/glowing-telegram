/*
 * Usart.h
 *
 * Created: 29/04/2023 15:35:33
 *  Author: brunaud10
 */ 


#ifndef USART_H_
#define USART_H_

/* Prototypes */
void USART_Init( unsigned int baudrate );
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );

#endif /* USART_H_ */