/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"
#include "common_types.h"
/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
#define BLACK       (0xf)

extern void Uart_Printf(char *fmt, ...);
extern int identifier;
extern void lcd_left_clear(void);
extern uint32 lcd_printf(uint16 x, uint16 y, uint8 color, const char *fmt, ...);
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *) 0x06000000;
char key;
char msg[60];
int caracteres = 0;
int digitos = 0;
int pixelWord = 8;
/*--- Funciones externas ---*/
void D8Led_symbol(int value);
/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));

/*--- Codigo de las funciones ---*/

void keyboard_init() {

	/* Configurar el puerto G (si no lo estuviese ya) */
	// Establece la funcion de los pines (EINT0-7)
	rPCONG = ~0x0;

	// Habilita el "pull up" del puerto
	rPUPG = 0x0;

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT &= ~(0x1 << 6);
	rEXTINT |= (0x1 << 5);

	/* Establece la rutina de servicio para EINT1 */pISR_EINT1 =
			(unsigned) KeyboardInt;

	//
	/* Configurar controlador de interrupciones */
	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = ~0x0;

	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = ~0x0;

	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;

	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;

	/* Habilitar linea EINT1 */rINTMSK &= ~(BIT_EINT1);

	//
	/* Por precaucion, se vuelven a borrar los bits de EXTINTPND e INTPND correspondientes*/rI_ISPC =
			~0x0;
	rEXTINTPND = ~0x0;
}
void KeyboardInt(void) {
	/* Esperar trp mediante la funcion DelayMs()*/
	DelayMs(100);
	//
	/* Identificar la tecla */
	key = key_read();

	int i = 0;

	/* Si la tecla se ha identificado, visualizarla en el 8SEG*/
	if (key != '-1') {
		if (key == 'F') {
			// Tecla para enviar el mensaje
			//Uart_Printf("%d;%s\0", identifier, msg);
			Uart_Printf("%s\n", msg);

			lcd_left_clear();

			if (identifier == 0) {
				lcd_printf(20, 70, BLACK, "Broadcast");
				lcd_printf(20, 86, BLACK, "enviado");
			} else {
				lcd_printf(20, 70, BLACK, "Mensaje enviado");
				lcd_printf(20, 86, BLACK, "al maletin %d", identifier);
			}

			identifier = 0;
			caracteres = 0;
		} else {

			if (caracteres == 0) {
				for (i = 0; i < 60; i++) {
					msg[i] = 'P';
				}
				lcd_left_clear();
			}

			msg[caracteres] = key;

			printMSG(key);
			caracteres += 1;
		}

	}
	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while ((rPDATG & 0x2) == 0)
		;

	/* Esperar trd mediante la funcion Delay() */
	DelayMs(100);
	/* Borrar interrupción de teclado */rI_ISPC = ~0x0;
	rEXTINTPND = ~0x0;
}

int key_read() {
	char* value = -1;
	char temp;
	// Identificar la tecla mediante ''scanning''
	// Si la identificación falla la función debe devolver -1
	temp = *(keyboard_base + 0xfd) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
	case 0x7:
		value = '0';
		break;
	case 0xB:
		value = '1';
		break;
	case 0xD:
		value = '2';
		break;
	case 0xE:
		value = '3';
		break;
	}

	/*
	 * ESCRIBIR EL CÓDIGO CORRESPONDIENTE A LAS OTRAS FILAS Y COLUMNAS
	 */

	temp = *(keyboard_base + 0xfb) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
	case 0x7:
		value = '4';
		break;
	case 0xB:
		value = '5';
		break;
	case 0xD:
		value = '6';
		break;
	case 0xE:
		value = '7';
		break;
	}

	temp = *(keyboard_base + 0xf7) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
	case 0x7:
		value = '8';
		break;
	case 0xB:
		value = '9';
		break;
	case 0xD:
		value = 'A';
		break;
	case 0xE:
		value = 'B';
		break;
	}

	temp = *(keyboard_base + 0xef) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
	case 0x7:
		value = 'C';
		break;
	case 0xB:
		value = 'D';
		break;
	case 0xD:
		value = 'E';
		break;
	case 0xE:
		value = 'F';
		break;
	}

	return value;

}
void printMSG(char key_trans) {
	char* msg = "";
	int aux=(caracteres%9)+1;
	if(aux%9==0)
	{
		lcd_left_clear();
	}
	// Traducir el numero al string
	switch (key_trans) {
	case '0':
		msg = "Hola";
		break;
	case '1':
		msg = "Yo";
		break;
	case '2':
		msg = "bien";
		break;
	case '3':
		msg = "si";
		break;
	case '4':
		msg = "adios";
		break;
	case '5':
		msg = "tu";
		break;
	case '6':
		msg = "mal";
		break;
	case '7':
		msg = "no";
		break;
	case '8':
		msg = "mucho";
		break;
	case '9':
		msg = "comida";
		break;
	case 'A':
		msg = ",";
		break;
	case 'B':
		msg = "?";
		break;
	case 'C':
		msg = "poco";
		break;
	case 'D':
		msg = "bebida";
		break;
	case 'E':
		msg = "¿?";
		break;

	}

	// Nose porque ha pintado algo raruno
	lcd_printf(10, 30 + aux * 20, BLACK, "%s", msg);

}

