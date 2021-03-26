#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/

//----------------------------
#include "../inc/global.h"
//-----------------------------------------------------


//Definiciones de las funciones---------------------------------------------------
static void inputHandler(u16,u16,u16);

/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void main(){	
	
	//--------------------------------------
	JOY_setEventHandler(&inputHandler);
	
	TITUTLO();
	
	ZoneMap();
	
}




//https://github.com/diegomtassis/yamd-library/blob/master/src/fwk/commons.c#L40
u8 randU8(u8 lower, u8 higher) {
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
