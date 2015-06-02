#ifndef __UART_H__
#define __UART_H__
/*--- definicion de constantes ---*/
#define LF_char 0x0A /* Caracter de salto de linea */
#define CR_char 0x0D /* Caracter de retorno de carro */
/*--- prototipos de funciones ---*/
void Uart_Init(int baud);
void Uart_Config(void);
void Uart_TxEmpty(void);
char Uart_Getch(void);
char* Uart_Getstring(void);	// No creo que funcione...
void Uart_SendByte(int data);
void Uart_SendString(char *pt);
void Uart_Printf(char *fmt,...);
#endif /* __UART_H__ */
