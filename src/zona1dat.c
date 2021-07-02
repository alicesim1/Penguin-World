#include "genesis.h"//[[SGDK]]

#include "../inc/global.h"
#include "../inc/zona1dat.h"


const u8 const casillas_0[] = {
	0,7,7,7,7,7,7,0,//0	,0-7
	9,1,1,1,1,1,1,0,//1	,8-15
	9,1,1,1,1,1,1,0,//2	,16-23
	9,1,1,1,1,1,1,1,//3	,24-31
	9,1,1,1,1,1,1,0,//4 ,32-39
	9,1,1,1,1,1,1,0 //5 ,40-47
	//0,0,0,1,0,0,0,0
//--0,1,2,3,4,5,6,7 = 8
};

const u8 const casillas_1[] = {
	0,7,7,7,7,7,7,0,//0	,0-7
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
//--0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5 = 16
};					   //10

const u16 const blxpri_0[] = {
	159,143,//0,1 puerta
	319,159,//2,3 bloque
	351,175,//4,5
	393,191,//6,7
	415,207 //8,9 (top_blxpri=9)
};

const u16 const blxpri_2[] = {
	159,239,//0,1 puerta
	896,287 //2,3 
};

const u16 const blxpri_3[] = {
	159,239,//0,1 puerta
	896,287,//2,3 
	384,223,//4,5 Pared <<
	671,271 //6,7 Pared >>
};

//cordenas de la grilla 32x32 para indicar Numero de Zona a teletransportar
const u8 const puertas_0[] = {
	3,7,4,1,3,0 //Puerta [1] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
};

const u8 const puertas_1[] = {
	3,0,3,0,3,7,//Puerta [1] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
	3,7,4,2,9,0 //Puerta [2] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
};

const u8 const puertas_2[] = {
	9,0,3,1,3,7,//Puerta [1] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
	9,15,4,3,9,0 //Puerta [2] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
};

const u8 const puertas_3[] = {
	9,0,3,2,9,15,//Puerta [1] cord_origen: x,y,pdircm, num_zone_dest,cord_dest: 0,1,2
};



const t_zona zona1dat[TOP_ZONAS] = {
  {
	FALSE, //PlanA
	2,//musica
	8,//Xtop
	5,//Ytop
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
	5,//Ytop
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
	6, //top_blxpri
	blxpri_3, //blockpri
	1,
	puertas_3
  }
};


