#include "Cosmos_USART.h" 

//unsigned int baud_aux = BAUD_AUX;

void SERIAL_Init()	//INICIALIZA MODULO SERIAL
{	
	UBRR0H = (unsigned char)(BAUD_AUX) >> 8;		//AJUSTA BAUDRATE
	UBRR0L = (unsigned char)(BAUD_AUX);	
	UCSR0A = 0;										//DESATIVA VELOCIDADE DUPLA
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);		//ATIVA TRANSMISSAO E RECEPCAO E INTERRUPCAO PARA RECEPCAO
	UCSR0C = (1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);	//MODO: ASSINCRONO / 8 DATA BITS / 1 STOP BIT / PARIDADE PAR (EVEN)
	//UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);				//MODO: ASSINCRONO / 8 DATA BITS / 1 STOP BIT 
}

void SERIAL_TX(unsigned char dado)	//ENVIA DADO CHAR
{
	while (!( UCSR0A & (1<<UDRE0)) );			//ESPERA ESVAZIAR BUFFER
	UDR0 = dado;								//ENVIA DADO
}

unsigned char SERIAL_Avaliable()	//VERIFICA SE EXISTE NOVO DADO DISPONIVEL PARA LEITURA
{
	if (UCSR0A & (1<<RXC0)) return 1;
	else					return 0;	
}

unsigned char SERIAL_RX_CHECK_ERROR()	//VERIFICA SE OCORREU ALGUM ERRO NA RECEPCAO DE DADOS
{										//PARA MAIORES DETALHES VERIFICAR REGISTRADOR 'UCSR0A' bits 2, 3 e 4.
	unsigned char trash;
	
	if(UCSR0A & 0b00011100)						//HOUVE ERRO DE RECEPCAO
	{
		while(UCSR0A & (1<<RXC0))				//FAZ COM QUE O HARDWARE LIMPE OS BITS DE ERRO
		{
			trash = UDR0; 
		}
		UCSR0A = 0X00;							//REDUNDANCIA
		return 0x01;							//CASO POSITIVO RETORNA 1
	}
	else
		return 0x00;							//CASO NAO HAJA ERRO RETORNA 0
}

unsigned char SERIAL_RX()	//RETORNA DADO DISPONIVEL EM SERIAL
{
	while (!(UCSR0A & (1<<RXC0)));				//ESPERA A RECEPCAO DE DADOS
	return UDR0;								//RETORNA DADO RECEBIDO
}


void SERIAL_Write(char *c)						//ENVIA UMA STRING
{
	for (; *c!=0;c++) SERIAL_TX(*c); 
}

void SERIAL_Write_Flash(const char *c)			//ENVIA STRING A PARTIR DA MEMORIA FLASH
{
	for (;pgm_read_byte(c)!=0;c++) SERIAL_TX(pgm_read_byte(c)); 
}


void IntToStr(unsigned int valor, unsigned char *disp)		//CONVERTE UM INT PARA VETOR CHAR CORRESPONDENTE ASCII _ NAO UTILIZADO NESTE PROJETO
{
	do
	{
		*disp = (valor%10) + 48; 
		valor /=10;    
		disp++;
		
	} while (valor!=0); 
}