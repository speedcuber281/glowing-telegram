/*
 * telemetre.c
 *
 * Created: 08/05/2023 21:44:58
 *  Author: axelb
 */ 

#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/io.h>
#include "telemetre.h"
#include "usart.h"

//variables 
volatile double pulse_start;
volatile double pulse_end;
volatile int pulse_completed = 0;

void Init(void)
{
	//On initialise la broche trigger comme sortie
	DDR_TRIGGER |= (1<<BROCHE_TRIGGER);
	PORT_TRIGGER &= ~(1<<BROCHE_TRIGGER);
	
	//On initialise la broche echo comme entrée
	DDR_ECHO &= ~(1<<BROCHE_ECHO);
	PORT_ECHO &= ~(1<<BROCHE_ECHO);
	
	//On configure l'interruption externe INT0 pour détecter le changement de niveau sur la broche echo
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC00);
	
	//On configure le timer1 pour mesurer les durées d'impulsion
	TIMSK1 |= (1<<ICIE1);
	TCCR1B |= (1<<CS10);
	
	//On active les interruptions globales
	sei();
}

//Fonction qui permet de créer un délai de 10us avec le timer2
void delay_10us(void)
{
	TCCR2A |= (1<<WGM21);
	OCR2A = 25;
	TCCR2B |= (1<<CS21);
	while ((TIFR2 & (1<<OCF2A)) == 0);
	TIFR2 = (1<<OCF2A);
}

//Envoie une impulsion de 10us sur la broche trigger
void pulse(void)
{
	PORT_TRIGGER |= (1<<BROCHE_TRIGGER);
	delay_10us();
	PORT_TRIGGER &= ~(1<<BROCHE_TRIGGER);
}

double calcul_distance(void)
{
	//calcule la durée de l'impulsion en ms
	double pulse_duration = pulse_end - pulse_start;
	//calcule la distance en centimètre
	double distance = (pulse_duration * 0.000340) / 2;
	return distance;
}

// Gestionnaire d'interruption pour l'interruption externe INT0
ISR(INT0_vect)
{
	//sauvegarde le temps de début d'impulsion
	if (pulse_completed == 0)
	{
		pulse_start = ICR1;
	}
	//sauvegarde le temps de fin d'impulsion
	else
	{
		pulse_end = ICR1;
	}
	
	//Inverse le drapeau de fin d'impulsion
	pulse_completed = !pulse_completed;
}

// Gestionnaire d'interruption pour l'interruption de capture d'entrée du Timer1
ISR(TIMER1_CAPT_vect)
{
	//sauvegarde le temps de début d'impulsion
	if (pulse_completed == 0)
	{
		pulse_start = ICR1;
	}
	
	//sauvegarde le temps de fin d'impulsion
	else
	{
		pulse_end = ICR1;
	}
	
	//Inverse le drapeau de fin d'impulsion
	pulse_completed = !pulse_completed;
}
