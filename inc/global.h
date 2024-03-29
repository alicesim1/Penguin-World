#ifndef _GLOBAL_H
#define _GLOBAL_H
//------------------------------------------------------------------------------------------
#include "../res/basicos.h"//fuente, pinguno jug, cursor,

//-----------------------------------------------

u8 ScreenY;		//27/29
u8 ScreenMY;	//112/120
u8 ScreenTY;	//224/240
s8 fixAlturaY;	//-24/-32

u8 JoyType;		//JOY_getJoypadType(JOY_1); //JOY_TYPE_PAD6
u8 padraton;	//JOY_getPortType(PORT_2);
bool CursorON;


u16 BUTTONS[20];
bool gat;

Sprite* cursorsp;
s16 readedX,readedY;
Vect2D_s16 joypos;
void _JOYsetXY ( s16 x, s16 y );
void _JOYupdateMouse ();


char char_salida[8];
void VDP_drawInt(s32,u8,u8,u8);

#include "../res/musica.h" //toda coleccion de musicas vgm
void play_music(u8);
u8 old_musica;


u8 randU8(u8,u8);

u16 paleta64[64];

void TITUTLO();
void ZoneMap();


#define diag_ind 200 //VRAM hex:4B0
void dialogo(u16,u16,u8,u8,u8);


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
