
#ifndef _ZONE_JUGPRI_H_
#define _ZONE_JUGPRI_H_

#include "genesis.h"//OBLIGATORIO! [[SGDK]]

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



//https://github.com/diegomtassis/yamd-library/blob/master/src/fwk/commons.c#L40
u8 randomInRangeU8(u8 lower, u8 higher) {
	return lower + random() % (higher + 1 - lower);
}

//https://github.com/diegomtassis/yamd-library/blob/master/src/fwk/commons.c#L40
u16 randU16(u16 lower, u16 higher) {
	return lower + random() % (higher + 1 - lower);
}

void VDP_drawInt(s32 valor,u8 ceros,u8 x, u8 y){
	intToStr(valor,char_salida,ceros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawText(char_salida,x,y);
}


/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activo)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void inputHandler(u16 joy, u16 state, u16 changed){
    BUTTONS[0]=changed;
	
	BUTTONS[1]=changed & BUTTON_UP;
	BUTTONS[2]=changed & BUTTON_DOWN;
	BUTTONS[3]=changed & BUTTON_LEFT;
	BUTTONS[4]=changed & BUTTON_RIGHT;
	
	BUTTONS[5]=changed & BUTTON_A;
	BUTTONS[6]=changed & BUTTON_B;
	BUTTONS[7]=changed & BUTTON_C;
	BUTTONS[8]=changed & BUTTON_START;
	
}
//------------------------------------------------------------------------------------------

#endif
