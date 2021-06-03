#ifndef _GLOBAL_H
#define _GLOBAL_H
//------------------------------------------------------------------------------------------
#include "../res/basicos.h"//fuente, pinguno jug,
#include "../res/musica.h"
//-----------------------------------------------
u8 padtipo;
u8 pad6;
u8 padraton;
u8 padmouse;

u16 BUTTONS[12];

s16 readedX;
s16 readedY;
Vect2D_s16 joypos;


void _JOYsetXY ( s16 x, s16 y );
void _JOYupdateMouse ();


char char_salida[8];
void VDP_drawInt(s32,u8,u8,u8);

void play_music(u8);

u8 randU8(u8,u8);

u16 paleta64[64];

void TITUTLO();
void ZoneMap();

u8 old_musica;
//-----------------------------------
typedef struct {
  const bool const PlanA;
  const u8 const musica;
  const u8 const Xtop;
  const u8 const *casillas;
  const u8 const top_blxpri;
  const u16 const *blockpri;
} t_zona;

#endif
