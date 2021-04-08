#define top_zonas 2

/*struct t_zona {
	const u8 ancho=8;
	const u8 alto=6;
	
	//0= Vacio (Muro)
	//1= Suelo para caminar,
	//7= Pared Derecho
	//9= Pared Izquierdo
	const u8 top_casillas = ancho * alto;//48
	const u8 casillas [top_casillas] = {
		0,7,7,7,7,7,7,0,
		9,1,1,1,1,1,1,0,
		9,1,1,0,0,0,0,0,
		1,1,1,1,1,1,1,1,
		9,1,1,1,1,1,1,0,
		9,1,1,1,1,1,1,0
	};
	
	const u8 top_blxpri=5;
	const u16 blxpri [top_blxpri] [2] = {
		{159,143},//puerta
		{319,159},//bloque
		{351,175},
		{393,191},
		{415,207}
	};
	
};
*/

struct t_zona zona[top_zonas];

typedef struct {
  const u8 ancho;
  const u8 alto;
  const u8 *casillas;
}t_zona;

const u8 casillas_0 [] = {
        0,7,7,7,7,7,7,0,
        9,1,1,1,1,1,1,0,
        9,1,1,0,0,0,0,0,
        1,1,1,1,1,1,1,1,
        9,1,1,1,1,1,1,0,
        9,1,1,1,1,1,1,0
};

const u16 blxpri [] [2] = {
		{159,143},//puerta
		{319,159},//bloque
		{351,175},
		{393,191},
		{415,207}
};

const t_zona zona [] = {
  {
    8, //ancho
    6, //alto
    &casillas_0  //casillas
  },
  {
    8,//ancho
    8,//alto
    NULL//casillas
  }
};

/*
//..................leer datos.....................
zona[0].ancho=8;
zona[0].alto=6;
zona[0].top_casillas=ancho*alto;

zona[0].casillas[0]=0;
zona[0].casillas[1]=7;
//-------------------
zona[0].top_blxpri=5;

zona[0].blxpri[0][0]=159;
*/


