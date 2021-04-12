#ifndef _GLOBAL_H
#define _GLOBAL_H
//------------------------------------------------------------------------------------------
#include "../res/basicos.h"//fuente, pinguno jug,
#include "../res/musica.h"
//-----------------------------------------------
u16 BUTTONS[9];

char char_salida[8];
void VDP_drawInt(s32,u8,u8,u8);

void play_music(u8);

u8 randU8(u8,u8);

u16 paleta64[64]; //copia Paletas 0,1,2,3 ,para fades completos

void TITUTLO();
void ZoneMap();

u8 ZONA_NUM;
u8 old_musica;

typedef struct {
  const bool const PlanA;
  const u8 const musica;
  const u8 const Xtop;
  const u8 const *casillas;
  const u8 const top_blxpri;
  const u16 const *blockpri;
} t_zona;

#endif
