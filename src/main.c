#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"
//-----------------------------------------------------

s16 readX,readY; //_JOYupdateMouse(); Coordenadas absolutas del puntero raton


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
	} else {	//KLog("NTSC-224");
		ScreenY=27;
		ScreTile8=0;
	}	
	ScreenTY=8+(ScreenY*8);//224/240
	ScreenMY=ScreenTY/2;//112/120
	fixAlturaY=-24-ScreTile8;//-24/-32
	
	/*strclr(charbim);
	
	u16 i=random();
	KLog_U1("i:",i);
	decabin(i);
	KLog(charbim);
	
	drawNumberAsHex(i);*/
	
	//--------------------------------------
	JoyType=JOY_getJoypadType(JOY_1);
	
	CursorON=FALSE;
	padraton=JOY_getPortType(PORT_2);
	if(padraton==PORT_TYPE_MOUSE) JOY_setSupport(PORT_2, JOY_SUPPORT_MOUSE);
	if(padraton==PORT_TYPE_MOUSE || padraton==PORT_TYPE_PAD) CursorON=TRUE; 
	
	
	JOY_setEventHandler(&inputHandler);
	
	TITUTLO();
	
	VDP_setWindowVPos(1,ScreenY);// 27max vertical Windows
	VDP_setTextPlane(WINDOW);//Textos "normales SGDK" se pintan en Window es temporal
	PAL_setColors(0,palette_black,64,CPU);//para iniciacion Debug
	old_musica=0;
	
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
	
	if(joy==JOY_1){	//PORT 1
		BUTTONS[1]=changed & BUTTON_UP;
		BUTTONS[2]=changed & BUTTON_DOWN;
		BUTTONS[3]=changed & BUTTON_LEFT;
		BUTTONS[4]=changed & BUTTON_RIGHT;
		
		BUTTONS[5]=changed & BUTTON_A;
		BUTTONS[6]=changed & BUTTON_B;
		BUTTONS[7]=changed & BUTTON_C;
	
		BUTTONS[8]=changed & BUTTON_START;
		if(JoyType==JOY_TYPE_PAD6){
			BUTTONS[9]=changed & BUTTON_X;
			BUTTONS[10]=changed & BUTTON_Y;
			BUTTONS[11]=changed & BUTTON_Z;
			BUTTONS[12]=changed & BUTTON_MODE;
		}
	}else { //PORT 2
		
		if(padraton==PORT_TYPE_PAD){
			BUTTONS[13]=changed & BUTTON_UP;
			BUTTONS[14]=changed & BUTTON_DOWN;
			BUTTONS[15]=changed & BUTTON_LEFT;
			BUTTONS[16]=changed & BUTTON_RIGHT;
		}
		
		BUTTONS[17]=changed & BUTTON_A;//Boton Central
		BUTTONS[18]=changed & BUTTON_B;//Boton Izquiero
		BUTTONS[19]=changed & BUTTON_C;//Boton Derecho
	}
	
}

/* Bug Hunt - https://github.com/moon-watcher/BugHuntMD
 * @CODE:        	 =>  Mun             | Twitter: @MoonWatcherMD
 * @CODE-ASSISTANT:	 =>  Jack Nolddor    | Twitter: @nolddor, Mail to: 
*/
void _JOYsetXY ( s16 x, s16 y )
{   
	readedX = JOY_readJoypadX(JOY_2);
	readedY = JOY_readJoypadY(JOY_2);
	
	readX=readY=0;
	
    joypos.x = x;
    joypos.y = y;
	
	SPR_setPosition(cursorsp,x,y);
}

void _JOYupdateMouse ()
{
	if(padraton==PORT_TYPE_MOUSE){
		readX = JOY_readJoypadX(JOY_2);
		readY = JOY_readJoypadY(JOY_2);	
	}else{
		//BUG Solo en emulador GENS! No funciona los diagonales!
		//usando un Gamepad!! teclado si funciona!
		if(BUTTONS[13]) readY-=2;
		else if(BUTTONS[14]) readY+=2;
		
		if(BUTTONS[15]) readX-=2;
		else if(BUTTONS[16]) readX+=2;
	}
	
   joypos.x -= readedX - readX;
   joypos.y -= readedY - readY;
   
   if(joypos.x<0)joypos.x=0;
   else if(joypos.x>319)joypos.x=319;
   
   if(joypos.y<0)joypos.y=0;
   else if(joypos.y>ScreenTY-1)joypos.y=ScreenTY-1;
   
   readedX = readX;
   readedY = readY;
   
   SPR_setPosition(cursorsp,joypos.x,joypos.y);
}



/*
char charbim[16] = {0};
char *ptr = charbim;

void decabin (u16 n) {
	//Sik#7563
	for (int i = 0; i < 16; i++) {
		// *ptr++ = (n & 0x8000) ? '1' : '0';
		*ptr++ = '0' + (n >> 15);
		n <<= 1;
	}
}

void drawNumberAsHex(u16 number) {
  char buffer[16] = {0};
  intToHex(number, buffer, 8);
  KLog(buffer);
}
*/


