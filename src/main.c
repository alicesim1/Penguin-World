#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"
//-----------------------------------------------------

//Definiciones de las funciones---------------------------------------------------
static void inputHandler(u16,u16,u16);

/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void main(){
	
	//--------------------------------------
	
	
	padtipo=JOY_getPortType(PORT_1);//13 = 
	//padtipo=15;//NINGUNO
	//padtipo=13;//PAD3,6
	//padtipo=0;//MOUSE

	padraton=JOY_getPortType(PORT_2);
	if(padraton==PORT_TYPE_MOUSE) JOY_setSupport(PORT_2, JOY_SUPPORT_MOUSE); //3
	//padraton=15;//NINGUNO
	//padraton=13;//PAD3,6
	//padraton=3;//MOUSE
	
	SYS_doVBlankProcess(); // Renderizamos la pantalla
	
	pad6=JOY_getJoypadType(JOY_1);
	//0=3 botones
	//1=6 botones
	//15=NINGUNO
	
	JOY_setEventHandler(&inputHandler);
	
	//TITUTLO();
	
	ZoneMap();
	
}


void play_music(u8 indice){
	switch(indice){
		case 1:XGM_startPlay(M_titulo);break;
		case 2:XGM_startPlay(M_zone1);break;
		default: XGM_stopPlay();
	}
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
	
	if(joy==JOY_1){
		
		BUTTONS[1]=changed & BUTTON_UP;
		BUTTONS[2]=changed & BUTTON_DOWN;
		BUTTONS[3]=changed & BUTTON_LEFT;
		BUTTONS[4]=changed & BUTTON_RIGHT;
		
		BUTTONS[8]=changed & BUTTON_START;
		
		if(pad6==JOY_TYPE_PAD6){	
			BUTTONS[9]=changed & BUTTON_X;
			BUTTONS[10]=changed & BUTTON_Y;
			BUTTONS[11]=changed & BUTTON_Z;
			BUTTONS[12]=changed & BUTTON_MODE;
		}
	}
	
	BUTTONS[5]=changed & BUTTON_A;//Boton Central
	BUTTONS[6]=changed & BUTTON_B;//Boton Izquiero
	BUTTONS[7]=changed & BUTTON_C;//Boton Derecho
	
}


void _JOYsetXY ( s16 x, s16 y )
{
   
	readedX = JOY_readJoypadX(JOY_2);
	readedY = JOY_readJoypadY(JOY_2);
  
   joypos.x = x;
   joypos.y = y;
}


void _JOYupdateMouse ()
{
   s16 readX = JOY_readJoypadX(JOY_2);
   s16 readY = JOY_readJoypadY(JOY_2);
   
   joypos.x -= readedX - readX;
   joypos.y -= readedY - readY;
   
   if(joypos.x<0)joypos.x=0;
   else if(joypos.x>319)joypos.x=319;
   
   if(joypos.y<0)joypos.y=0;
   else if(joypos.y>223)joypos.y=223;
   
   readedX = readX;
   readedY = readY;
}

