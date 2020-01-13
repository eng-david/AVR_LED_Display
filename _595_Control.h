/*
 * _595_Control.h
 *
 * Created: 14/02/2018 20:25:33
 *  Author: DAVID
 */ 


#ifndef _595_CONTROL_H_
#define _595_CONTROL_H_

#include "Definitions.h"

void write_595(char data, unsigned char indice);				//ENVIA DADOS AOS REGISTRADORES DE DESLOCAMENTO
																//PARAMETRO 01: DADO DE 8 BITS
																//PARAMETRO 02: BIT A SER ENVIADO AOS DESLOCADORES

void shift_595();												//Shift CI_74HC595
void query_595();												//Query CI_74HC595



#endif /* _595_CONTROL_H_ */