/*
 * telemetre.h
 *
 * Created: 08/05/2023 21:45:09
 *  Author: axelb
 */ 


#ifndef TELEMETRE_H_
#define TELEMETRE_H_


/* Définition */

//Distance max que l'on veux mesurer 
#define Dmax 400

//TRIGGER
#define DDR_TRIGGER DDRD
#define PORT_TRIGGER PORTD
#define BROCHE_TRIGGER PORTD2

//ECHO
#define DDR_ECHO DDRD
#define PORT_ECHO PORTD
#define BROCHE_ECHO PORTD3

//prototypes 
void Init(void);
void pulse(void);
double calcul_distance(void);
void delay_10us(void);

#endif /* TELEMETRE_H_ */