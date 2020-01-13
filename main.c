/*
 * Projeto COSMOS Alpha.c
 *	Neste Projeto o conteudo do display sera gerado a partir de dados armazenados em EEPROM provenientes de comunica��o SERIAL
 *  
 * Created: 11/02/2018 23:48:27
 * Author : DAVID
 */ 

#include "Definitions.h"

//CARACTERES. 
PROGMEM const unsigned char IMAGES[39][5]  = {		//IMAGES[DIGITO][LINHA]   
	    {
		0b00001110,
		0b00011001,		 //0	
		0b00010011,
		0b00001110			
	    },{
		0b00010000,
		0b00010010,
		0b00011111,     //1
		0b00010000		
		},{
		0b00010010,
		0b00011001,		//2
		0b00010101,
		0b00010010	
		},{
		0b00010001,
		0b00010101,		//3
		0b00010101,
		0b00001010
		},{
		0b00000011,
		0b00000100,		//4
		0b00000100,
		0b00011111
		},{
		0b00010111,
		0b00010101,		//5
		0b00010101,
		0b00001001
	    },{
		0b00001110,
		0b00010101,		//6
		0b00010100,
		0b00001000
		},{
		0b00010001,
		0b00001001,		//7
		0b00000101,
		0b00000011
		},{
		0b00001010,
		0b00010101,		//8
		0b00010101,
		0b00001010
		},{
		0b00000010,
		0b00000101,		//9
		0b00000101,
		0b00011111
		},{
		0b00001010		//:		
		},{
		0b00000001,
		0b00000000		//VAZIO		
		},{		
		0b00011110,
		0b00001001,		//A
		0b00001001,
		0b00011110
		},{
		0b00011111,
		0b00010101,		//B
		0b00010101,
		0b00001010		
		},{
		0b00001110,
		0b00010001,		//C
		0b00010001,
		0b00010001
		},{
		0b00011111,
		0b00010001,		//D
		0b00010001,
		0b00001110
		},{
		0b00011111,
		0b00010101,		//E
		0b00010101,
		0b00010001
		},{
		0b00011111,
		0b00000101,		//F
		0b00000101,
		0b00000101
		},{
		0b00011111,
		0b00010001,		//G
		0b00010101,
		0b00001101
		},{
		0b00011111,
		0b00000100,		//H
		0b00000100,
		0b00011111
		},{		
		0b00010001,
		0b00011111,		//I
		0b00010001
		},{
		0b00001001,
		0b00010001,		//J
		0b00001111,
		0b00000001
		},{
		0b00011111,
		0b00000100,		//K
		0b00001100,
		0b00010011
		},{
		0b00011111,
		0b00010000,		//L
		0b00010000,
		0b00011000
		},{
		0b00011111,
		0b00000010,		//M
		0b00000100,
		0b00000010,
		0b00011111
		},{
		0b00011111,
		0b00000010,		//N
		0b00000100,
		0b00001000,
		0b00011111
		},{
		0b00001110,
		0b00010001,		//O
		0b00010001,
		0b00001110
		},{
		0b00011111,
		0b00000101,		//P
		0b00000101,
		0b00000010
		},{
		0b00011111,
		0b00010001,		//Q
		0b00011001,
		0b00011111,
		0b00010000
		},{
		0b00011111,
		0b00000101,		//R
		0b00001101,
		0b00010010
		},{
		0b00010110,
		0b00010101,		//S
		0b00010101,
		0b00011001
		},{
		0b00000011,
		0b00000001,		//T
		0b00011111,
		0b00000001,
		0b00000011
		},{
		0b00001111,
		0b00010000,		//U
		0b00010000,
		0b00001111
		},{
		0b00000111,
		0b00001000,		//V
		0b00010000,
		0b00001000,
		0b00000111		
		},{
		0b00001111,
		0b00010000,		//W
		0b00001110,
		0b00010000,
		0b00001111
		},{
		0b00010001,
		0b00001010,		//X
		0b00000100,
		0b00001010,
		0b00010001
		},{
		0b00000011,
		0b00011100,		//Y
		0b00000010,
		0b00000001
		},{
		0b00011001,
		0b00010101,		//Z
		0b00010011,
		0b00010001
		},{
		0b10000000,
		0b10000000		//ESPA�O	
		}
};


char STARTUP[7] = {0x43, 0x4F, 0x53, 0x4D, 0x4F, 0x53, KEYBOARD_ENTER} ;	//MENSAGEM INICIAL
char BUFFER[BUFFER_SIZE];

//-----------------------------------------------------

//VARIAVEIS GLOBAIS

volatile char var_flags					= 0x00;
volatile unsigned int buffer_data_size	= 0x00;		//UTILIZADA POR ANIMA��O TIPO2
volatile unsigned int  eeprom_address	= 0x00;		//UTILIZADA PELA INTERRUP�AO SERIAL
volatile unsigned char animation2		= 0x00;		//VARIAVEL UTILIZADA POR TIMER1
volatile unsigned char line				= 0x00;		//VARIAVEL UTILIZADA POR TIMER0
volatile unsigned char tmr2_aux         = 0x00;

//-----------------------------------------------------

//FUN��ES AUXILIARES

void re_buffer(char *data);										//ATUALIZA CONTEUDO DE BUFFER
																
void display(char *data, unsigned char anim2, unsigned char linha);					
																//ATUALIZA DISPLAY COM CONTEUDO INDICADO
																//DEVE SER CHAMADA PERIODICAMENTE COM INCREMENTO DO PARAMETRO 'LINHA' PARA MULTIPLEXA��O																
																//PARAMETRO 01: DADOS A SEREM ENVIADOS A DISPLAY
																//PARAMETRO 02: DESLOCAMENTO HORIZONTAL
																//PARAMETRO 03: LINHA A SER TRATADA
																
void setup();													//CONFIGURA FLAGS SALVAS EM EEPROM

	
//-----------------------------------------------------


ISR(TIMER0_OVF_vect)	//RESPONSAVEL POR CHAMAR A FUN��O 'DISPLAY'
{	
	display(BUFFER, animation2, line);	
	line ++;
	if(line >= DISP_LINES)
		line = 0x00;	
}

ISR(TIMER1_OVF_vect)	//RESPONSAVEL POR: ANIMA��O TIPO 2
{
	//CASO VALOR DE animation2 FOR 0, O DISPLAY ESTAR� EXIBINDO EM SUA ULTIMA COLUNA O CONDEUDO, OU SEJA O DISPLAY NUNCA FICAR� VAZIO.
	//PARA CENTRALIZAR O TEXTO O VALOR DE animation2 DEVE SER DISP_ROWS-1
	
	TCNT1L = 0XEE;										//INICIALIZA TIMER1 EM 34286
	TCNT1H = 0X85;										//...	
	
	if (buffer_data_size>DISP_ROWS)						//O CONTEUDO DO TEXTO � MAIOR QUE O DISPLAY?
	{													//SIM, EXECUTA ANIMA��O TIPO 2
		animation2 ++;
		if (animation2 >= (buffer_data_size+DISP_ROWS)-1)	//TEXTO ROLOU COMPLETAMENTE?
		{
			animation2 = 0x00;							//RESETA
		}
	}
	
	else
	{													//N�O?			
		animation2  = DISP_ROWS-1;						//CENTRALIZA TEXTO
		TIMSK1 = 0X00;									//TIMER1 NAO SE FAZ NECESSARIO AT� PROXIMO REBUFFER
	}
	
}//INTERRUP�AO TIMER1

ISR(TIMER2_OVF_vect)				//RESPONSAVEL POR STARTUP
{
	tmr2_aux++;						//INCREMENTA VARIAVEL AUXILIAR	
	if (tmr2_aux == 0x64)			//AUXILIAR IGUAL A 100?
	{	
		re_buffer(CALL_EEPROM);		//GERA CONTEUDO DE EEPROM EM BUFFER
		TIMSK2 = 0X00;				//DESLIGA TIMER2
	}
	
}	

ISR(USART_RX_vect)
{	
	unsigned char dado_recebido		= 0x00;					
	unsigned char settings		    = 0x00;
				
	if (!SERIAL_RX_CHECK_ERROR())												//CASO NAO EXISTA ERRO REGISTRADO TRATA DADO
	{
		dado_recebido = SERIAL_RX();											//LE DADO DA SERIAL E SALVA NA VARIAVEL
	
		if (dado_recebido == KEYBOARD_UNDERLINE)								//CARACTERE DE CONTROLE DETECTADO?
		{
			SERIAL_TX(dado_recebido);											//INDICA CONFIGURA��O AO USUARIO
			settings = EEPROM_Read(999);										//CARREGA A VARIAVEL COM OS VALORES DE CONFIGURA��O EXISTENTE
			dado_recebido = SERIAL_RX();										//LE QUAL A CONFIGURA��O DESEJADA
			SERIAL_TX(dado_recebido);											//RETORNA AO USUARIO
		
			switch(dado_recebido)												//LA�O VERIFICA QUAL TECLA FOI PRESSIONADA
			{
				case KEYBOARD_I:												//TECLA |I| PRESSIONADA?
					invert_bit(settings,7);										//BIT DE INVERS�O
					break;														//SAI DO LA�O SWITCH

				case KEYBOARD_S:												//TECLA |S| PRESSIONADA?
					invert_bit(settings,6);										//BIT DE VELOCIDADE						
					break;														//SAI DO LA�O SWITCH
			
				case KEYBOARD_O:												//TECLA |O| PRESSIONADA?_MODO SLEEP					
					TURN_OFF_DISP();												
					TIMSK1 = 0X00;												//DESLIGA TIMER1 (RESPONSAVEL POR ANIMA��ES)
					TIMSK0 = 0x00;												//DESLIGA TIMER0 (RESPONSAVEL POR DISPLAY)
					break;
			
				case KEYBOARD_1:												//TECLA |1| PRESSIONADA?_RETORNA DO MODO SLEEP		
					animation2  = 0;											//RESETA ANIMA�AO TIPO2		
					TIMSK1 = 0X01;												//ATIVA TIMER1 (RESPONSAVEL POR ANIMA��ES)
					TIMSK0 = 0x01;												//ATIVA TIMER0 (RESPONSAVEL POR DISPLAY)
					break;
				
				default:														//OUTRO CARACTER PRESSIONADO?
					break;														//SAI DO LA�O SWITCH
			}
			
			EEPROM_Update(999,settings);										//SALVA AS EDI��ES EM EEPROM
			setup();															//CONFIGURA FLAGS
		
		}		

		else if(dado_recebido == KEYBOARD_LF){}									//PREVINE PROBLEMAS COM ALGUNS MONITORES SERIAL

		else																	//CARACTER DE TRATAMENTO NORMAL?
		{
			EEPROM_Update(eeprom_address,dado_recebido);						//ATUALIZA DADO			
			SERIAL_TX(EEPROM_Read(eeprom_address));								//RETORNA COM O VALOR SALVO EM EEPROM, SERVE PARA CONFERENCIA DE CORRUP�AO DE DADOS
			eeprom_address ++;													//INCREMENTA INDERE�O
			
			if ((eeprom_address == BUFF_DATA_LIMIT) | (dado_recebido == KEYBOARD_ENTER))	//ATINGIU O LIMITE DESTINADO A CARACTERES
			{																				//OU USUARIO PRESSIONOU |ENTER|
				EEPROM_Update(eeprom_address,KEYBOARD_ENTER);								//INCERE CARACTERE DE FIM
				eeprom_address = 0X00;														//RESETA VARIAVEL DE ENDERE�O
				re_buffer(CALL_EEPROM);														//ATUALIZA CONTEUDO DE BUFFER
				SERIAL_Write("OK");
			}
		}	
	}									
}//INTERRUP�AO USART_RX

int main(void)
{		 
	//PORTC DRIVER DE TRANSISTORES
	PORTC = 0b00000000;		//INICIA PORTD
	DDRC  = 0b11111111;		//DEFINE IOs
	
	PORTD = 0b00000000;		//INICIA PORTD
	DDRD  = 0b00111000;		//DEFINE IOs
	
	//DDRB  = 0b11111111;		//DEFINE IOs
	//PORTB = 0b00000000;		//INICIA PORTB 
	
	cli();			//DESABILITA AS INTERRUP�OES _ RECOMENDADO PELO FABRICANTE	
	
		// --- TIMER0 -> RESPONSAVEL POR CHAMADA DE FUNCAO 'DISPLAY' ---
		TCCR0B = 0X04;	//TIMER0 PRESCALER 256
		TIMSK0 = 0X01;	//HABILITADO
		// ------
		
		// --- TIMER1 -> RESPONSAVEL POR ANIMA��ES ---
		//TCCR1B = 0X05;	//PRESCALER INICIALIZADO EM setup()	
		TIMSK1 = 0X01;		//HABILITA A INTERRUPCAO POR OVERFLOW DO TIMER1	
		// ------
		
		// --- TIMER2 -> RESPONSAVEL POR STARTUP ---
		TCCR2B = 0X07;		//PRESCALER 1024
		TIMSK2 = 0X01;		//HABILITA A INTERRUPCAO POR OVERFLOW DO TIMER2
		// ------
		
	setup();										//SETA FLAGS DE SETTINGS COM CONTEUDO SALVO EM EEPROM
	SERIAL_Init();									//INICIALIZA COMUNICA�AO SERIAL COM INTERRUP�AO PARA RECEP��O
	re_buffer(STARTUP);								//ADICIONA MENSAGEM DE INICIALIZA��O A BUFFER
		
	sei();											//HABILITA AS INTERRUP��ES
	
    while (1)										//LOOP INFINITO
    {	
		
	}//loop			
	
}//main

void re_buffer(char *data)	//FUN�AO RESPONSAVEL POR ALIMENTAR A VARIAVEL BUFFER 
{
	//VARIAVEIS LOCAIS	
	unsigned char caracter		= KEYBOARD_ENTER;		//CARACTERE A SER TRATADO
	unsigned char chr_size;								//TAMANHO DO CARACTERE
	unsigned int  buffer_index	= 0x00;					//INDICE DA VARIAVEL BUFFER
	unsigned int  data_index	= 0x00;					//INDICE DA EEPROM
		 
	
	 while(1)											//LOOP PREENCHE 'BUFFER' COM CONTEUDO DE PARAMETRO 'DATA'
	{			
					
		if(data == CALL_EEPROM)							//CHAMADA DE EEPROM?
			caracter = EEPROM_Read(data_index);			//CARACTER RECEBE CONTEUDO DE EEPROM
		else											//SE NAO...
			caracter = *(data+data_index);				//CARACTER RECEBE CONTEUDO DO PARAMETRO 'data'
	
		if (caracter == KEYBOARD_ENTER)					//INDICA��O DE FIM?
			break;										//SAI DO LA�O WHILE
							
		
		// --- BLOCO PARA CONVERS�O ANCII ---
		if((caracter > 47) & (caracter < 58))		
			caracter = caracter - 48;
		
		else if ((caracter > 64) & (caracter < 91))		
			caracter = caracter - 53;		
			
		else				
			caracter = 38;		
		
		// --- FIM BLOCO CONVERS�O ANSCII ---
		
		
		// --- BLOCO CONTAR TAMANHO DO CARACTER ---
		chr_size = 0x00;
		while (pgm_read_byte(&IMAGES[caracter][chr_size]) != 0x00)	
		{
			chr_size++;				
			if (chr_size > 0x05)		//NECESSARIO PARA CARACTERES GRANDES, EX: M, N, W ...
			{
				chr_size = 0x05;		//TAMANHO MAXIMO DOS CARACTERES
				break;					//SAI DO LA�O while
			}
		}
		// --- FIM BLOCO CONTAR TAMANHO DO CARACTER ---
				
				
		for(unsigned char i=0x00; i < chr_size; i++)		//ALIMENTA VARIAVEL BUFFER RESPEIRANDO O TAMANHO DO CARACTERE
		{
			BUFFER[buffer_index] = pgm_read_byte(&IMAGES[caracter][i]);			
			buffer_index++;
		}
				
		BUFFER[buffer_index] = 0x00;				//INSERE ESPA�O ENTRE CARACTERES			
		buffer_index++;								//INCREMENTA O CONTADOR AUXILIAR			
		data_index++;								//INCREMENTA O CONTADOR AUXILIAR	
		
		if((data_index > BUFF_DATA_LIMIT) ||(buffer_index>BUFFER_SIZE-DISP_ROWS))			//CONDI��O DE ERRO, CASO A LEITURA CHEGUE A LIMITE ESTIPULADO
			/*
				LIMITE 1: LIMITE DA EEPROM
				LIMITE 2: LIMITE DO BUFFER, CONSIDERANDO ESPA�O PARA O FIM NA ANIMA��O TIPO 2
			*/
			break;
					
	}
		
	for (unsigned char i = buffer_index; i<BUFFER_SIZE; i++)	//PREENCHE O CONTEUDO RESTANTE COM ESPA�O EM BRANCO
		BUFFER[i] = 0x00;
	
	TIMSK1 = 0X01;												//CERTIFICA-SE DE ATIVAR TIMER1
	buffer_data_size = buffer_index -1;							//RETORNA O NUMERO DE BYTES DE DADOS EM 'buffer' MENOS O ULTIMO ESPA�O
	
}//re_buffer

void display(char *data, unsigned char anim2, unsigned char linha)		//FUN�AO RESPONSAVEL POR ENVIAR O CONTEUDO DE BUFFER AO DISPLAY, DEVE SER EXECUTADA PERIODICAMENTE PARA MULTIPLEXACAO
{
	//VARIAVEIS LOCAIS		
	unsigned char i = 0x00;							//VARIAVEL AUXILIAR
	
		
	// --- BLOCO PARA DADOS (CARACTERES) ---
	if(DISP_ROWS>anim2)	//PROCESSO INICIAL DE ANIMA��O TIPO2 QUANDO OS CARACTERES CHEGAM DO LADO DIREITO E PREENCHEM COMPLETAMENTE O DISPLAY
	{					// DISPLAY: [____<-XXXX]
	
		for(i=anim2; i != 0xFF; i--)			//LA�O RESPONSAVEL POR CONTROLAR OS BITS INDIVIDUAIS DOS CARACTERES
			write_595(*(data+i),linha);				
			
		for (i=0x01;i<DISP_ROWS-anim2;i++)		//LA�O COMPLEMENTA ANIMA�AO COM ESPA�O INICIAL VAZIO 
			write_595(0X00,0);
	}			
	
	else	//EXECUTADO QUANDO CARACTERES SE DESLOCAM PARA ESQUERDA
	{		//DISPLAY: [XXXXXXXX] (TOTALMENTE PREENCHIDO)
		
		for(i=DISP_ROWS; i > 0x00; i--)				//LA�O RESPONSAVEL POR CONTROLAR OS BITS INDIVIDUAIS DOS CARACTERES
			write_595(*(data+(i+(anim2-DISP_ROWS))),linha);	//LEMBRAR QUE 'anim2' PUSSUI NO MINIMO VALOR IGUAL A 'DISP_ROWS'			
	}
	// --- FIM BLOCO PARA DADOS (CARACTERES) ---
		
		
	// --- BLOCO PARA LIMITA�AO FISICA ---	
	for (i=0x00;i<0x04;i++)						//4 BITS FLUTUANTES
		write_595(0X00,0);
	// --- FIM BLOCO PARA LIMITA�AO FISICA ---
		
	/*	DESATIVADO POIS O ATMEGA VAI DRIVEAR OS TRANSISTORES COM OS PROPRIOS PINOS
	// --- BLOCO PARA LINHAS ---
	for (i=0x00;i<0x08;i++)						//ESTE LA�O PREENCHE O REGISTRADOR RESPONSAVEL PELAS LINHAS
		write_595((0b10000000 >> linha),i);
	// --- FIM BLOCO PARA LINHAS --- 
	*/	
	
	PORTC = (0b00000001 << linha);		
	query_595();								//QUERY PARA LINHA ATUAL
				
	
}//display()

void setup()
{
	unsigned char settings = EEPROM_Read(999);
		
	// --- BLOCO CONTROLE DE VELOCIDADE DE ANIMA�AO TIPO 2 ---
	// CONSIDERA-SE AQUI QUE A INTERRUP�AO GLOBAL ESTEJA DESABILITADA
	if(test_bit(settings,6))
	TCCR1B = 0X03;			//AJUSTA PRESCALER DO TIMER RESPONSAVEL PELA ANIMA�AO
	else
	TCCR1B = 0X04;
	// --- BLOCO CONTROLE DE VELOCIDADE DE ANIMA�AO TIPO 2 ---	
	
}