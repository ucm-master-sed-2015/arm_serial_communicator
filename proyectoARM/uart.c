/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "uart.h"
#include <stdarg.h>
/*--- implementacion de las funciones ---*/
void Uart_Init(int baud) {
	int i;
	/* UART0 */rULCON0 = 0x3; // modo normal, sin paridad, stop=1b, char=8b
	rUCON0 = 0x205; // tx=level, rx=edge, no timeout/error, normal, int/polling
	rUBRDIV0 = ((int) (MCLK / 16. / baud + 0.5) - 1); // formula div. frecuencia
	rUFCON0 = 0x0; // desactivar FIFO
	rUMCON0 = 0x0; // desactivar control de flujo
			/* UART1 */
	rULCON1 = 0x3; // modo normal, sin paridad, stop=1b, char=8b
	rUCON1 = 0x205; // tx=level, rx=edge, no timeout/error, normal, int/polling
	rUBRDIV1 = ((int) (MCLK / 16. / baud + 0.5) - 1); // formula div. frecuencia
	rUFCON1 = 0x0; // desactivar FIFO
	rUMCON1 = 0x0; // desactivar control de flujo
}
void Uart_Config(void) {
// si no se usan interrupciones, no es necesario hacer nada
}
inline void Uart_TxEmpty(void) {
	while (!(rUTRSTAT0 & 0x4))
		; // esperar a que el shifter de TX se vacie
}
char Uart_Getch(void) {
	while (!(rUTRSTAT0 & 0x1))
		; // esperar a que el buffer contenga datos
	return RdURXH0() ; // devolver el caracter (macro definida en 44b.h)
}
char* Uart_GetString(void) {
	char string_toReturn[60];
	int nChars = 0;
	int i = 0;
	for(i=0; i <= 60; i++){
		string_toReturn[i] = 'P';
	}
	while (!(rUTRSTAT0 & 0x1))
		; // esperar a que el buffer contenga datos
	while ( (RdURXH0() != '\r') && (nChars<60)){
		string_toReturn[nChars] = RdURXH0();
		nChars++;

		while (!(rUTRSTAT0 & 0x1))
				; // esperar a que el buffer contenga datos
	}
	char* toReturn = string_toReturn;
	return toReturn; // devolver el caracter (macro definida en 44b.h)
}
int Uart_GetInt(void) {
	while (!(rUTRSTAT0 & 0x1))
		; // esperar a que el buffer contenga datos
	return ( (int) RdURXH0() )  - 48;// devolver el caracter (macro definida en 44b.h)
	//return intRdURXH0() ; // devolver el caracter (macro definida en 44b.h)
}
void Uart_SendByte(int data) {
	char localBuf[2] = { '\0', '\0 '};
	if (data == '\n') {
		while (!(rUTRSTAT0 & 0x2))
			; // esperar a que THR se vacie
		WrUTXH0('\r'); // escribir retorno de carro (macro definida en 44b.h)
	}
	while (!(rUTRSTAT0 & 0x2))
		; // esperar a que THR se vacie
	WrUTXH0(data); // escribir data (macro definida en 44b.h)
}
void Uart_SendString(char *pt) {
	while (*pt) // mandar byte a byte hasta completar string
		Uart_SendByte(*pt++);
}
void Uart_Printf(char *fmt, ...) {
	va_list ap;
	char string[256];
	va_start(ap, fmt);
	vsprintf(string, fmt, ap);
	Uart_SendString(string);
	va_end(ap);
}
