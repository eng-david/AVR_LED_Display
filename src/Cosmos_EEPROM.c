/*
 * Cosmos_EEPROM.c
 *
 * Created: 14/02/2018 20:18:26
 *  Author: DAVID
 */ 

#include "Cosmos_EEPROM.h"

void EEPROM_Write(unsigned int address, unsigned char data)
{
	while(EECR & (1<<EEPE));	//espera completar um escrita previa
	EEAR = address;				//carrega o endereco para a escrita
	EEDR = data;				//carrega o dado a ser escrito
	EECR |= (1<<EEMPE);			//escreve um logico em EEMPE
	EECR |= (1<<EEPE);			//inicia a escrita ativando EEPE
	_delay_ms(5);				//DELAY RECOMENDADO AO ESCREVER EM EEPROM
}

unsigned char EEPROM_Read(unsigned int address)
{
	while(EECR & (1<<EEPE));	//espera completar um escrita previa
	EEAR = address;				//escreve o endereco de leitura
	EECR |= (1<<EERE);			//inicia a leitura ativando EERE
	return EEDR;				//retorna o valor lido do registrador de dados
}

void EEPROM_Update(unsigned int address, unsigned char data)
{
	if (EEPROM_Read(address) != data)	//APENAS ATUALIZA EEPROM SE O ENTERECO CONTIVER UM DADO DIFERENTE
	EEPROM_Write(address,data);			//ATUALIZA DADO
}

