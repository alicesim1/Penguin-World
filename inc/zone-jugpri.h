#ifndef _ZONE_JUGPRI_H_
#define _ZONE_JUGPRI_H_

//------------------------------------------------------------------------------------------
#include "../res/basicos.h"

//-----------------------------------------------
u16 ind;

u8 randomInRangeU8(u8,u8);
u16 randU16(u16,u16);

char char_salida[16]; //Cadena de 16 caracteres(para rellenar o vaciar) No se debe superar!
void VDP_drawInt(s32,u8,u8,u8);

//Manejador de entrada
u16 BUTTONS[9];
void inputHandler(u16,u16,u16);


void ZoneMap();


#endif
