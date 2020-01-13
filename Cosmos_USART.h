#ifndef COSMOS_USART_H 
#define COSMOS_USART_H

#include "Definitions.h"

#define BAUD_AUX F_CPU/16/BAUD-1 

//DESCRIÇÃO DETALHADA NO ARQUIVO .C

unsigned char SERIAL_Avaliable();
void SERIAL_Init();
void SERIAL_TX(unsigned char dado);
unsigned char SERIAL_RX_CHECK_ERROR();
unsigned char SERIAL_RX(); 
void SERIAL_Write(char *c);
void SERIAL_Write_Flash(const char *c); 
void IntToStr(unsigned int valor, unsigned char *disp);

#endif