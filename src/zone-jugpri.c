/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/zone-jugpri.h"


#include "zona1.h"//res ficheros
const MapDefinition* const zona1[] = {&z1h1};
Map* bgb; //PLANO B (Fondo del nivel Prioridad Baja(*Puertas Altas...))

const MapDefinition* const zona1b[] = {&z1h1b};
Map* bga; //PLANO A (Capa superior Prioridad Alta)


u8 habit=0;

bool move_scroll;
u16 posX,posY;
u16 TopXMap,TopYMap;
u16 posXt,posYt;

static void loadzona();
static void pintarAB();

const u8 STARTXT=128;
const u8 STARTYT=0;


//---------------------------------------------------------
// DATA
//---------------------------------------------------------

u8 mapindex_tiles;//indice de inicio de los tiles del MAP

u16 paleta32[32];

u8 jugcontrol=3;//0=diagonales, 1=UP=UP+>>, 2=UP=UP+<<, 3=0+1

//------------------------------------------------------------------------------------------
bool SPR_ACT;
Sprite* penguinsp; //atributo tipo Sprite
const u8 VELPING=2;
s16 PX,PY;
bool pflag;
u8 pdirc,pdir,pdircm;
u8 panim;
bool JUGmueve;
bool jugpri,jugpricpy;

static void jug2diso();
static void jugdir4();
static void jugpenguin();

//------------------------------------------------------------------------------------------
#define top_blxpri 5
struct t_blxpri {
	u16 x, y;
};
struct t_blxpri blxpri[top_blxpri];

//------------------------------------------------------------------------------------------
#define top_object2D 5
struct t_object2D {
	Sprite* sprt;
	u16 x, y;
};
struct t_object2D object2D[top_object2D];
//------------------------------------------------------------------------------------------
static void object2D_maker(SpriteDefinition sprited,u8 , u8, u16 , u16 , bool , bool );

//--------------------------------------------------------------------------------------------



/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void ZoneMap(){
	
	//--------------------------------------
	VDP_setPalette(0,palette_black);VDP_setPalette(1,palette_black);
	VDP_setPalette(2,palette_green);VDP_setPalette(3,palette_blue);
	
	VDP_setWindowVPos(1,26);// 27max vertical Windows
	VDP_setTextPlane(WINDOW);//Textos "normales SGDK" se pintan en Window
	
	
	PX=32*1;PY=32*2;
	JUGmueve=FALSE;
	panim=3;
	
	jugcontrol=3;
	
	jugpri=jugpricpy=TRUE;
	
	memcpy(&paleta32[16],penguin.palette->data,8*2);//16+8
	
	SPR_init();
	
	penguinsp=SPR_addSprite(&penguin,160-12,112-26,TILE_ATTR(1,jugpri,0,0));
	
	//pdirc=pdircm=1;//up+>>
	pdirc=pdircm=4;//down+>>
	//pdirc=pdircm=2;//up+<<
	//pdirc=pdircm=3;//down+<<
	jugdir4();
	SPR_setFrame(penguinsp,1);//parado
	
	jug2diso();
	
	loadzona();pintarAB();
	
	//SPR_update();SYS_doVBlankProcess();//fix (60Hrz) pintarAB Se necesita ciclos de procesamiento para pintar Sprites
	SPR_update();
	//SYS_doVBlankProcess();
	
	SPR_ACT=FALSE;
	
	PAL_fadeIn(0,32,&paleta32[0],20,0);
	
	bool gat=TRUE;
    while(1){//LOOP BASICO(NUNCA SE SALE!)
		
		jugpenguin();
		
		VDP_drawInt(move_scroll,0,0,26);
		if(move_scroll){pintarAB();SPR_update();}
		
		VDP_drawInt(SYS_getCPULoad(),2,38,27);
		
		
		
		if(!gat){
			if(BUTTONS[8]){ gat=TRUE;
				jugcontrol++;if(jugcontrol==4)jugcontrol=0;
				VDP_drawInt(jugcontrol,0,0,27);
			}
			
			if(BUTTONS[6] && !gat){ gat=TRUE;
				VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(2,1,0,0,1472),36,12);
			}
			if(BUTTONS[7] && !gat){ gat=TRUE;
				VDP_setTileMapXY(BG_A,TILE_ATTR_FULL(1,1,0,0,1025),36,20);
			}
		
		}else if(!BUTTONS[0]) gat=FALSE;
		
		
		SYS_doVBlankProcess(); // Renderizamos la pantalla
		
		if(BUTTONS[8] && BUTTONS[5]) SYS_hardReset();

    }
}



static void object2D_maker(SpriteDefinition sprited, u8 num_obj , u8 pal , u16 X, u16 Y, bool v, bool h){
	
	object2D[num_obj].x= STARTXT+(X-Y)   +160;
	object2D[num_obj].y=(STARTYT+(X+Y)/2)+112;
	
	bool tempbol=TRUE;
	for(u8 i=0;i<top_blxpri;i++){
		if(object2D[num_obj].x+48>blxpri[i].x && object2D[num_obj].x-48<blxpri[i].x
		&& object2D[num_obj].y+48>blxpri[i].y && object2D[num_obj].y <= blxpri[i].y){
			tempbol=FALSE; break;
		}
	}
	
	object2D[num_obj].x-=12;object2D[num_obj].y-=26;
	
	object2D[num_obj].sprt=SPR_addSprite(&sprited, object2D[num_obj].x-posX, object2D[num_obj].y-posY, TILE_ATTR(pal,tempbol,v,h));
	SPR_setDepth(object2D[num_obj].sprt,-object2D[num_obj].y+112-26);
	
	SPR_setFrame(object2D[num_obj].sprt,1);//parado
	
}

static void pintarAB(){
	VDP_drawInt(PX,3,20,26);VDP_drawInt(PY,3,20,27);
	
	VDP_drawInt(posX,3,5,26);VDP_drawInt(posY,3,5,27);
	MAP_scrollTo(bgb,posX,posY);MAP_scrollTo(bga,posX,posY);
	move_scroll=FALSE;
	u8 i;
	
	//-----------------------------------------------------------
	for(i=0;i<3;i++){
		SPR_setPosition(object2D[i].sprt,object2D[i].x-posX,object2D[i].y-posY);
	}
	
	///////////////////////////////////////////////////
	
	
	
	SPR_setDepth(penguinsp,-posY);
	VDP_drawInt(-posY,3,0,27);
	
	posXt=posX+160;posYt=posY+112;//centro de la pantalla
	VDP_drawInt(posXt,3,10,26);VDP_drawInt(posYt,3,10,27);
	
	jugpri=TRUE;
	for(i=0;i<top_blxpri;i++){
		if(posXt+48>blxpri[i].x && posXt-48<blxpri[i].x && posYt+48>blxpri[i].y && posYt<=blxpri[i].y){
			jugpri=FALSE; break;
		}
	}
	
	if(jugpri!=jugpricpy){ jugpricpy=jugpri; 
		SPR_setPriorityAttribut(penguinsp,jugpri);
	}
	
	
}

static void loadzona(){
	
	memcpy(&paleta32[0],zona1[habit]->palette->data,16*2);
	paleta32[0]=0;//colro de fondo 100% negro
	paleta32[15]=RGB24_TO_VDPCOLOR(0xFFFFFF);//color 15 (texo...) Blanco
	mapindex_tiles=ind=0;
	
	VDP_loadTileSet(zona1[habit]->tileset,mapindex_tiles,DMA);
	bgb=MAP_create(zona1[habit],BG_B,mapindex_tiles);
	ind+=zona1[habit]->tileset->numTile;
	
	
	VDP_loadTileSet(zona1b[habit]->tileset,ind,DMA);
	bga=MAP_create(zona1b[habit],BG_A,TILE_ATTR_FULL(0,1,0,0,ind));//PLANO B SIEMPRE PRIORIDAD ALTA!
	ind+=zona1b[habit]->tileset->numTile;
	
	blxpri[0].x=159;blxpri[0].y=143;//pared 
	blxpri[1].x=319;blxpri[1].y=159;//bloque
	blxpri[2].x=351;blxpri[2].y=175;//
	blxpri[3].x=393;blxpri[3].y=191;//
	blxpri[4].x=415;blxpri[4].y=207;//
	
	
	//-------------------------------------------
	for(u8 i=1;i<4;i++){
		object2D_maker(penguin,i-1,randU16(0,3),32*(i+1),32*(i+1),0,randU16(0,1));
	}
	//--------------------------------------------
	
	
}


//Calculo de jugador a isometrico
static void jug2diso(){ //PX->posX
	posX= STARTXT + (PX - PY);
	posY= STARTYT + (PX + PY)/2;
}
 
static void jugpenguin(){
	
	pdir=0;
	switch(jugcontrol){
		/*
		BUTTONS[1]=changed & BUTTON_UP;
		BUTTONS[2]=changed & BUTTON_DOWN;
		BUTTONS[3]=changed & BUTTON_LEFT;
		BUTTONS[4]=changed & BUTTON_RIGHT;
		*/
		case 0:{ //solo diagonales!
			if 		(BUTTONS[1] && BUTTONS[4])pdir=1;//up+>>
			else if (BUTTONS[2] && BUTTONS[3])pdir=2;//down+<<
			else if (BUTTONS[1] && BUTTONS[3])pdir=3;//up+<<
			else if (BUTTONS[2] && BUTTONS[4])pdir=4;//down+>>
		}break;
		case 1:{//evita diagonales
			if 		(BUTTONS[1] && !BUTTONS[3] && !BUTTONS[4])pdir=1;//up+>>
			else if (BUTTONS[2] && !BUTTONS[3] && !BUTTONS[4])pdir=2;//down+<<
			else if (BUTTONS[3] && !BUTTONS[1] && !BUTTONS[2])pdir=3;//up+<<
			else if (BUTTONS[4] && !BUTTONS[1] && !BUTTONS[2])pdir=4;//down+>>
		}break;
		case 2:{//evita diagonales
			if 		(BUTTONS[4] && !BUTTONS[1] && !BUTTONS[2])pdir=1;//up+>>
			else if (BUTTONS[3] && !BUTTONS[1] && !BUTTONS[2])pdir=2;//down+<<
			else if (BUTTONS[1] && !BUTTONS[3] && !BUTTONS[4])pdir=3;//up+<<
			else if (BUTTONS[2] && !BUTTONS[3] && !BUTTONS[4])pdir=4;//down+>>
		}break;
		case 3:{//hibrido!!
			if 		(BUTTONS[1] && BUTTONS[4] && !BUTTONS[2] && !BUTTONS[3])pdir=1;//up+>>
			else if (BUTTONS[1] && !BUTTONS[3] && !BUTTONS[4])pdir=1;
			else if (BUTTONS[2] && BUTTONS[3] && !BUTTONS[1] && !BUTTONS[4])pdir=2;//down+<<
			else if (BUTTONS[2] && !BUTTONS[3] && !BUTTONS[4])pdir=2;
			else if (BUTTONS[1] && BUTTONS[3] && !BUTTONS[2] && !BUTTONS[4])pdir=3;//up+<<
			else if (BUTTONS[3] && !BUTTONS[1] && !BUTTONS[2])pdir=3;
			else if (BUTTONS[2] && BUTTONS[4] && !BUTTONS[1] && !BUTTONS[3])pdir=4;//down+>>
			else if (BUTTONS[4] && !BUTTONS[1] && !BUTTONS[2])pdir=4;
		}break;
	}
	
	
	
	if(pdir>0){	
		if(PX%32==0 && PY%32==0){
			if(!JUGmueve){ JUGmueve=TRUE; //SI TENEMOS UNA CORDENADA MULTIPLE 32
				pdircm=pdir;
			}
		}
	}
	
	// Si estamos en movimiento (porque no estamos alineados EN LA GRILLA)
	// calculamos el desplazamiento del sprite a usar
	
	if(JUGmueve){
		
		//-----------------------------------------------------------------
		if(pdirc!=pdircm){pdirc=pdircm;
			jugdir4();
		}
		
		panim--;
		if(panim==0){panim=3;
			SPR_nextFrame(penguinsp);SPR_ACT=TRUE;
		}
		//---------------------------------------------------------------------
		
		switch(pdircm){
			case 1:PY-=VELPING;break;
			case 2:PY+=VELPING;break;
			case 3:PX-=VELPING;break;
			case 4:PX+=VELPING;
		}
		
		jug2diso();
		
		// Si tenemos una posicion valida (multiplo de 32), podemos dejar de movernos
		if(PX%32==0 && PY%32==0) JUGmueve=FALSE; //Y NOS MARCAMOS COMO QUIETOS
		move_scroll=TRUE;
		
	}else if(penguinsp->frameInd!=1){
		SPR_setFrame(penguinsp,1);SPR_ACT=TRUE;
		panim=3;
	}
	
}

static void jugdir4(){
	switch(pdircm){
		case 1:{SPR_setAnim(penguinsp,1);pflag=FALSE;}
		break;
		case 2:{SPR_setAnim(penguinsp,0);pflag=TRUE;}
		break;
		case 3:{SPR_setAnim(penguinsp,1);pflag=TRUE;}
		break;
		case 4:{SPR_setAnim(penguinsp,0);pflag=FALSE;}
	}
	
	SPR_setHFlip(penguinsp,pflag);
	SPR_ACT=TRUE;
}


