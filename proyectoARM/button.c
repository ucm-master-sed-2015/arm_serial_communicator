/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol = 0;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
extern void D8Led_symbol(int value);

int identifier;

void button_init(void)
{
	rPCONG = 0x0fff;    // PONER LOS BOTONES COMO ENTRADA (bits 12, 13, 14 y 15 - pines 6 y 7)
}

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND |= 0xf; // Escribir los 4 bits a uno

	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = 0x3ffffff; // Escribir los 26 bits a uno

	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0; // Poner todos los bits a cero (todas a IRQ)

	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON |= ~0x0; // Poner todos los bits a 1
	rINTCON = ~0x6; // Poner los bits 1 y 2 a cero

	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	// Todo a 1 menos el bit 26 (global) y el bit 21 (Eint4567)
	rINTMSK &= ~(BIT_GLOBAL | BIT_EINT4567);

	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567 = (unsigned) Eint4567_ISR;

/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	rPCONG = 0xffff; // PONER LOS BOTONES COMO INTERRUPCION (bits 12, 13, 14 y 15 - pines 6 y 7)

	//Habilita las resistencias de pull-up
	rPUPG &= 0x3f; // Poner a 0 los bits 6 y 7

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	// EINT6 (bits 30 y 29) y EINT7 (bits 26 y 25)
	// Flanco de bajada = 01
	rEXTINT &= ((0 << 30) | (0 << 26));
	rEXTINT |= ((1 << 29) | (1 << 25));

/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND |= 0xf;
	rI_ISPC = 0x3ffffff;

	identifier = 0;

}


int which_int;
void Eint4567_ISR(void)
{

	// Identificar la interrupcion
	which_int = rEXTINTPND;

	// Actualizar simbolo
	switch (which_int) {
		case 0x4:
			if(identifier < 15) {
				identifier++;
			}
			break;
		case 0x8:
			if ( identifier > 0 ){
				identifier--;
			}
			break;
	}

	D8Led_symbol(identifier);

	// espera 100ms para evitar rebotes
	DelayMs(100);

	// borra los bits en EXTINTPND  
	rEXTINTPND |= 0xf;

	rI_ISPC |= BIT_EINT4567;
}


