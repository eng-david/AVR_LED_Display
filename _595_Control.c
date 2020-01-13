/*
 * _595_Control.c
 *
 * Created: 14/02/2018 20:25:51
 *  Author: DAVID
 */ 

#include "_595_Control.h"

void write_595(char data, unsigned char indice)		//SETA UM BIT NOS REGISTRADORES
{
	if (data & (0x01<<indice))		set_bit(PORTD,DATA);
	else							reset_bit(PORTD,DATA);
	shift_595();
}

void shift_595(){
	set_bit(PORTD,SHIFT);
	reset_bit(PORTD,SHIFT);
}
void query_595()
{
	set_bit(PORTD,QUERY);
	reset_bit(PORTD,QUERY);
}
