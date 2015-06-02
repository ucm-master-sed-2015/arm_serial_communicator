/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "lcd.h"

extern int identifier;

/*--- declaracion de funciones ---*/
int main(void);

/*--- variables globales ---*/

/*--- codigo de la funcion ---*/
int main(void) {

	identifier = 0;

	sys_init(); // inicializacion de la placa, interrupciones, puertos
	Eint4567_init(); // inicializacion de los botones
	lcd_init();
	keyboard_init();
	Uart_Init(115200); // inicializacion de la Uart
	Uart_Config(); // configuración de interrupciones y buffers

	// Por ahora este main espera que le llegue un entero por el serie
	// y cuando le llega hace un led switch

	D8Led_symbol(0);

	char* mensajeRecibido = "";
	char c[60];
	int numeroLeido = 0;

	lcd_on();

	lcd_draw_vline( 240, 0, 150, BLACK, 4);

	lcd_printf(40, 16, BLACK, "OUTBOX");

	lcd_printf(210, 16, BLACK, "INBOX");

	while (1) {
		// Intentar hacer un get string
		//mensajeRecibido = Uart_GetString();
		//char c = Uart_Getch();
		mensajeRecibido = Uart_GetString();
		int j = 0;
		for(j = 0; j <= 60; j++){
			c[j] = mensajeRecibido[j];
		}

		leds_switch();

		// Limpiar la parte de abajo de la pantalla
		lcd_right_clear();
		//translateMsg(mensajeRecibido);
		translateMsg(c);
	}
}

void translateMsg(char* mensajeRecibido){

	int i = 0;
	int aux=0;
	char* msg = "";

	char letra;

	while((mensajeRecibido[i] != 'P') ){
		if (i%10==0 && i!=0)
		{
			DelayMs(3000);
			aux=0;
			lcd_right_clear();
		}
		letra = mensajeRecibido[i];
		msg = "";

		switch (mensajeRecibido[i]) {
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
			case 'a':
				msg = ",";
				break;
			case 'b':
				msg = "?";
				break;
			case 'c':
				msg = "poco";
				break;
			case 'd':
				msg = "bebida";
				break;
			case 'e':
				msg = "¿?";
				break;

			}

			// Nose porque ha pintado algo raruno
			lcd_printf(174, 40 + aux * 20, BLACK, "%s", msg);
		i += 1;
		aux+=1;
	}
}

