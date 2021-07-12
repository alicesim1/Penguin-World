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
void main(u16 hard){
	if(!hard){
		SYS_hardReset(); //si se hace Soft-Reset, probocamos limpieza total de la RAM!
		KLog("Soft RESET!");
	}
	
	if(IS_PALSYSTEM){	//KLog("PAL-240");
		VDP_setScreenHeight240();//29(30) tiles x8 (Solo para PAL = 50FPS) NTSC No puede usar este modo!
		ScreenY=29;
		ScreTile8=8;
		}
	else {	//KLog("NTSC-224");
		ScreenY=27;
		ScreTile8=0;
	}
	ScreenTY=8+(ScreenY*8);//224/240
	ScreenMY=ScreenTY/2;//112/120
	//--------------------------------------

	padtipo=JOY_getPortType(PORT_1);
	padraton=JOY_getPortType(PORT_2);
	if(padraton==PORT_TYPE_MOUSE) JOY_setSupport(PORT_2, JOY_SUPPORT_MOUSE);
	SYS_doVBlankProcess(); // Necesario para detecte el JoypadType
	pad6=JOY_getJoypadType(JOY_1);
	JOY_setEventHandler(&inputHandler);
	
	//TITUTLO();
	
	
	VDP_setWindowVPos(1,ScreenY-2);// 27max vertical Windows
	VDP_setTextPlane(WINDOW);//Textos "normales SGDK" se pintan en Window es temporal
	PAL_setColors(0,palette_black,64,CPU);//para iniciacion Debug
	
	ZoneMap();
	
}


//https://github.com/diegomtassis/yamd-library/blob/master/src/fwk/commons.c#L40
u8 randU8(u8 lower, u8 higher) {
	return lower + random() % (higher + 1 - lower);
}

//https://danibus.wordpress.com/2019/08/29/99-aventuras-en-megadrive-debug/
//PROBLEMAS DE CONVERSIÓN CON SPRINTF -> ¿Y si quiero usar variables de 32 bits?
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
		if(pad6==1){
			BUTTONS[9]=changed & BUTTON_X;
			BUTTONS[10]=changed & BUTTON_Y;
			BUTTONS[11]=changed & BUTTON_Z;
			BUTTONS[12]=changed & BUTTON_MODE;
		}
	}
	//necesario para que el mouse puerto 2 funcione los 3 botones
	BUTTONS[5]=changed & BUTTON_A;//Boton Central
	BUTTONS[6]=changed & BUTTON_B;//Boton Izquiero
	BUTTONS[7]=changed & BUTTON_C;//Boton Derecho
	
}

/* Bug Hunt - https://github.com/moon-watcher/BugHuntMD
 * @CODE:        	 =>  Mun             | Twitter: @MoonWatcherMD
 * @CODE-ASSISTANT:	 =>  Jack Nolddor    | Twitter: @nolddor, Mail to: 
*/
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
   else if(joypos.y>ScreenTY-1)joypos.y=ScreenTY-1;
   
   readedX = readX;
   readedY = readY;
}

