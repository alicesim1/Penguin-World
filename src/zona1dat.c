#include "genesis.h"//[[SGDK]]

#include "../inc/global.h"
#include "../inc/zona1dat.h"

const u8 const casillas_0[] = {
	1,1,1,1,1,1,0,//0	,8-15
	1,1,1,1,1,1,0,//1	,16-23
	1,1,1,1,1,1,1,//2	,24-31
	1,1,1,1,1,1,0,//3 ,32-39
	1,1,1,1,1,1,0 //4 ,40-47
//--,0,1,2,3,4,5,6 = 7
};

const u8 const casillas_1[] = {
	9,1,1,1,1,1,1,0,//1	,8-15
	9,1,1,0,0,0,0,0,//2	,16-23
	1,1,1,1,1,1,1,1,//3	,24-31
	9,1,1,1,1,1,1,0,//4	,32-39
	9,1,1,1,1,1,1,0 //5	,40-47
//--0,1,2,3,4,5,6,7 = 8
};

const u8 const casillas_2[] = {
	0,0,0,0,0,0,0,0,0,0 ,6,3,1,6,6,0,//0
	0,0,0,0,0,0,0,0,0,10,1,1,1,1,1,0,//1
	0,0,0,0,0,0,0,0,0,10,1,1,1,1,1,0,//2
	0,0,0,0,0,0,0,0,0,10,1,1,1,1,1,0,//3
	0,0,0,0,0,0,0,0,0,10,1,1,1,1,1,0,//4
	0,0,0,0,0,0,0,0,0,10,1,1,1,1,1,0,//5
	0,7,7,7,7,7,7,7,7,7 ,1,1,1,1,1,0,//6
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,//7
	4,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,//8
	1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,//9
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,//10
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0 //11
//--0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5 = 16
};					   //10

const u8 const casillas_3[] = {
	0,7,7,7,7,7,7,7,7,7 ,6,3,1,6,6,0,
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,
	9,1,1,0,0,0,0,0,0,8 ,1,1,1,1,1,0,
	9,1,1,0,0,0,0,0,0,10,1,1,1,1,1,0,
	9,1,1,0,0,0,0,0,0,10,1,1,1,1,1,0,
	9,1,1,5,7,7,7,7,7,7 ,1,1,1,1,1,0,
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,
	4,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,
	1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0,
	9,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,0 //11
  //0,0,0,B,0,0,0,0,0,0 ,0,0,0,0,0,0 //12
//--0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5 = 16
};					   //10

const u16 const blxpri_0[] = {
	191,159,//0,1 puerta
	351,175,//2,3 bloque
	383,191,//4,5
	425,207,//6,7
	447,223 //8,9 (top_blxpri=9)
};

const u16 const blxpri_2[] = {
	223,287,//0,1 puerta
	896,335 //2,3 
};

const u16 const blxpri_3[] = {
	223,287,//0,1 puerta
	896,335,//2,3 
	385,271,//4,5 Pared <<
	385,271-32,//6,7 Pared <<
	735,320,//8,9 Pared >>
	735,320-32 //10,11 Pared >>
};

//cordenas de la grilla 32x32 para indicar Numero de Zona a teletransportar
//cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2,3,4,5
const u8 const puertas_0[] = {
	2,6,4,1,2,0 //Puerta [1] 
};

/*const u8 const puertas_0[] = {
	3,7,4,1,3,0 //Puerta [1] 
};
const u8 const puertas_1[] = {
	3,0,3,0,3,7,//Puerta [1]
	3,7,4,2,9,0 //Puerta [2]
};*/

const u8 const puertas_1[] = {
	2,0,3,0,2,6,//Puerta [1]
	2,7,4,2,9,0 //Puerta [2]
};

const u8 const puertas_2[] = {
	9,0,3,1,2,7,//Puerta [1]
	9,15,4,3,9,0 //Puerta [2]
};

const u8 const puertas_3[] = {
	9,0,3,2,9,15,//Puerta [1]
};



const t_zona zona1dat[TOP_ZONAS] = {
  {
	FALSE, //PlanA
	2,//musica
	7,//Xtop
	4,//Ytop
    casillas_0,//casillas
	0,//top_blxpri
	0,//blockpri
	1,//topPuertas
	puertas_0 //puertas
  },
  {
	TRUE, //PlanA
	2,//musica
	8,//Xtop
	4,//Ytop
    casillas_1,//casillas
	9, //top_blxpri
	blxpri_0,//blockpri
	2,//topPuertas
	puertas_1 //puertas
  },
  {
	FALSE, //PlanA
	0, //musica
	16,//Xtop
	11,//Ytop
    casillas_2,//casillas
	3, //top_blxpri
	blxpri_2, //blockpri
	2,//topPuertas
	puertas_2 //puertas
  },
  {
	TRUE, //PlanA
	1, //musica
	16,//Xtop
	11,//Ytop
    casillas_3,//casillas
	11, //top_blxpri
	blxpri_3, //blockpri
	1,
	puertas_3
  }
};


