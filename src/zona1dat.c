#include "genesis.h"//[[SGDK]]

#include "../inc/global.h"
#include "../inc/zona1dat.h"


const u8 const casillas_0[] = {
	0,7,7,7,7,7,7,0,//0-7
	9,1,1,1,1,1,1,0,//8-15
	9,1,1,0,0,0,0,0,//16-23
	1,1,1,1,1,1,1,1,//24-31
	9,1,1,1,1,1,1,0,//32-39
	9,1,1,1,1,1,1,0,//40-47
	0,0,0,0,0,0,0,0 //48-55
//--0,1,2,3,4,5,6,7 = 8
};

const u16 const blxpri_0[] = {
	159,143,//0,1 puerta
	319,159,//2,3 bloque
	351,175,//4,5
	393,191,//6,7
	415,207 //8,9 (top_blxpri=9)
};

const t_zona zona1dat[TOP_ZONAS] = {
  {
    TRUE, //PlanA
	2, //musica
    casillas_0,  //casillas
	9, //top_blxpri
	blxpri_0 //blockpri
	
  },
  {
    FALSE, //PlanA
	2,//musica
    0,//casillas /* 0 = null*/
	0,//top_blxpri
	0 //blockpri
	
  }
};


