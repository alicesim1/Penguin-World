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
