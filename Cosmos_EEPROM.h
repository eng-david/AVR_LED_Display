/*
 * Cosmos_EEPROM.h
 *
 * Created: 14/02/2018 20:18:04
 *  Author: DAVID
 *	
 */ 


#ifndef COSMOS_EEPROM_H_
#define COSMOS_EEPROM_H_

#include "Definitions.h"

//DESCRIÇÃO DETALHADA NO ARQUIVO .C

void EEPROM_Write(unsigned int address, unsigned char data);	//ESCREVE EM EEPROM
void EEPROM_Update(unsigned int address, unsigned char data);	//ATUALIZA DADO NO ENDEREÇO
unsigned char EEPROM_Read(unsigned int address);				//LE EEPROM


#endif /* COSMOS_EEPROM_H_ */