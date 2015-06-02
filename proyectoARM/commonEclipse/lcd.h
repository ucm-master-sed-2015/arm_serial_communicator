/*-------------------------------------------------------------------
**
**  Fichero:
**    lcd.h  10/5/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Contiene las definiciones de los prototipos de funciones
**    para el acceso al lcd de la placa de prototipado S3CEV40  
**
**  Notas de diseño:
**
**-----------------------------------------------------------------*/

#ifndef __LCD_H__
#define __LCD_H__

#include "common_types.h"
#include "s3c44b0x.h"
#include "s3cev40.h"

#define LCD_WIDTH   (320)
#define LCD_HEIGHT  (240)

#define LCD_BUFFER_SIZE    (LCD_WIDTH*LCD_HEIGHT/2) // en bytes con 2 pixels/byte

#define BLACK       (0xf)
#define WHITE       (0x0)
#define LIGHTGRAY   (0x5)
#define DARKGRAY    (0xa)
    
#define LCD_OFF     (1)
#define LCD_ON      (0)

/*
** Configura el controlador de lcd según los siguientes parámetros 
**   Resolución: 320x240
**   Modo de barrido: 4 bit single scan
**   Modo del lcd: 16 niveles de gris
**   Paletas de color: no
**   Frecuencia de refresco: 120 Hz
**   Self-refresh: desactivado
**   Polaridad de señales de sincronismo: normal
**   Conmutación de VM: en cada frame
**   Anchura del blanking horizontal: mínima
**   Retardo y anchura de pulso de sincronismo horizontal: mínimos
**   Valores de dithering: por defecto
** Inicializa el estado del lcd y lo apaga
*/
void lcd_init( void );

/* 
** Enciende el lcd
*/
void lcd_on( void );

/* 
** Apaga el lcd
*/
void lcd_off( void );

/*
** Devuelve el estado (LCD_ON/LCD_OFF) del lcd
*/
uint8 lcd_status( void );

/*
** Borra el lcd
*/
void lcd_clear( void );

/*
 ** Borra media lcd
 */
void lcd_half_clear( void );

void lcd_mini_clear( void );

void lcd_mini_down_clear( void );

/*
** Pone el pixel (x,y) en el color indicado
*/
void lcd_putpixel( uint16 x, uint16 y, uint8 color);

/*
** Devuelve el color al que está el pixel (x,y)
*/
uint8 lcd_getpixel( uint16 x, uint16 y );

/*
** Dibuja una línea horizontal desde el pixel (xleft,y) hasta el pixel (xright,y) del color y grosor indicados
*/
void lcd_draw_hline( uint16 xleft, uint16 xright, uint16 y, uint8 color, uint16 width );

/*
** Dibuja una línea vertical desde el pixel (x,yup) hasta el pixel (x,ydown) del color y grosor indicados
*/
void lcd_draw_vline( uint16 yup, uint16 ydown, uint16 x, uint8 color, uint16 width );

/*
** Dibuja un rectángulo cuya esquina superior izquierda está en el pixel (xleft,yup) y cuya esquina inferior está en el píxel (xright, ydown) del color y grosor indicados
*/
void lcd_draw_box( uint16 xleft, uint16 yup, uint16 xright, uint16 ydown, uint8 color, uint16 width );

/*
** Usando una fuente 8x16, escribe un caracter a partir del pixel (x,y) en el color indicado
*/
void lcd_putchar( uint16 x, uint16 y, uint8 color, char ch );

/*
** Usando una fuente 8x16, escribe una cadena a partir del pixel (x,y) en el color indicado
*/
void lcd_puts( uint16 x, uint16 y, uint8 color, char *s );

/*
** Usando una fuente 8x16, escribe texto formateado a partir del pixel (x,y) en el color indicado
*/
uint32 lcd_printf( uint16 x, uint16 y, uint8 color, const char *fmt, ... );

/*
** Usando una fuente 8x16, escribe un caracter a doble tamaño a partir del pixel (x,y) en el color indicado
*/
void lcd_putchar_x2( uint16 x, uint16 y, uint8 color, char ch );

/*
** Usando una fuente 8x16, escribe una cadena a doble tamaño a partir del pixel (x,y) en el color indicado
*/
void lcd_puts_x2( uint16 x, uint16 y, uint8 color, char *s );

/*
** Usando una fuente 8x16, escribe texto formateado a doble tamaño a partir del pixel (x,y) en el color indicado
*/
uint32 lcd_printf_x2( uint16 x, uint16 y, uint8 color, const char *fmt, ... );

#endif 
