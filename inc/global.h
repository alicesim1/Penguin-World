#ifndef _GLOBAL_H
#define _GLOBAL_H
//------------------------------------------------------------------------------------------
#include "../res/basicos.h"//fuente, pinguno jug,
//-----------------------------------------------
u16 BUTTONS[9];

char char_salida[16];
void VDP_drawInt(s32,u8,u8,u8);

u8 randU8(u8,u8);

u16 paleta64[64]; //copia Paletas 0,1,2,3 ,para fades completos

void TITUTLO();
void ZoneMap();


typedef struct {
  const u8 const ancho;
  const u8 const alto;
  const u8 const *casillas;
  const u16 const *blockpri;
} t_zona;

#endif
