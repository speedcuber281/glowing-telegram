/*
 * projet_telemetre.c
 *
 * Created: 18/05/2023 16:12:15
 * Author : axelb
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "usart.h"
#include "telemetre.h"

static FILE mystdout = FDEV_SETUP_STREAM (USART_Transmit, NULL, _FDEV_SETUP_WRITE);

//variable liée au télémetre
extern int pulse_completed;

int main(void)
{
	USART_Init(51);
	stdout = &mystdout;
	Init();
	while (1)
	{
		pulse();
		while (!pulse_completed);
		double distance = calcul_distance();
		if (distance <= 0.0 || distance > Dmax)
		{
			printf("Erreur de mesure \r\n");
		}
		else
		{
			printf("Distance: %f cm\r\n",distance);
		}
		pulse_completed = 0;
	}
}
