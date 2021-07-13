#ifndef _GLOBAL_H
#define _GLOBAL_H
//------------------------------------------------------------------------------------------
#include "../res/basicos.h"//fuente, pinguno jug, cursor,
//#include "../res/musica.h" //toda coleccion de musicas vgm
//-----------------------------------------------

u8 ScreenY;		//27/29
u8 ScreenMY;	//112/120
u8 ScreenTY;	//224/240
u8 ScreTile8; 	//0/8

u8 padtipo;		//JOY_getPortType(PORT_1);
u8 pad6;		//JOY_getJoypadType(JOY_1);
u8 padraton;	//JOY_getPortType(PORT_2);

u16 BUTTONS[20];
bool gat;

Sprite* cursorsp;
s16 readedX,readedY;
Vect2D_s16 joypos;
void _JOYsetXY ( s16 x, s16 y );
void _JOYupdateMouse ();


char char_salida[8];
void VDP_drawInt(s32,u8,u8,u8);

//void play_music(u8);
//u8 old_musica;

u8 randU8(u8,u8);

u16 paleta64[64];

//void TITUTLO();
void ZoneMap();




//-----------------------------------
typedef struct {
  const bool const PlanA;
  const u8 const musica;
  const u8 const Xtop;
  const u8 const Ytop;
  const u8 const *casillas;
  const u8 const top_blxpri;
  const u16 const *blockpri;
  const u8 const topPuertas;
  const u8 const *puertas;
} t_zona;

#endif
