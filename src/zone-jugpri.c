#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"

//---------------Zona 1---------------------------------
#include "../inc/zona1dat.h"
#include "../res/zona1.h"//res ficheros
const MapDefinition* const zona1[] = {&z1h0,&z1h1,&z1h2,&z1h3};
Map* bgb; //PLANO B (Fondo del nivel Prioridad Baja(*Puertas Altas...))

const MapDefinition* const zona1b[] = {0,&z1h1b,0,0};
Map* bga; //PLANO A (Capa superior Prioridad Alta)
//-----------------------------------------------------------

bool move_scroll;
s16 posX,posY;
u16 TopXMap,TopYMap;
u16 posXt,posYt;

static void loadzona();
static void pintarAB();

u8 ZONA_NUM;
//-------5 x 8
//u16 STARTXT=128;
s8 STARTYT=-32;

//----------11 x 16 
u16 STARTXT=319;
//s8 STARTYT=-64;

//---------------------------------------------------------
// DATA
//---------------------------------------------------------
u8 jugcontrol=3;//0=diagonales, 1=UP=UP+>>, 2=UP=UP+<<, 3=0+1

//------------------------------------------------------------------------------------------

Sprite* penguinsp; //atributo tipo Sprite
const u8 VELPING=2;
s16 PX,PY;
u8 PX32,PY32;//BLOQUES *32
bool pflag;
u8 pdirc,pdir,pdircm;
u8 panim;
bool JUGmueve;
bool jugpri,jugpricpy;

static void jug2diso();
static void jugpenguin();

//------------------------------------------------------------------------------------------

/*#define top_object2D 3
struct t_object2D {
	Sprite* sprt;
	u16 x, y;
};
struct t_object2D object2D[top_object2D];
//------------------------------------------------------------------------------------------
static void object2D_maker(SpriteDefinition sprited,u8 , u8, u16 , u16 , bool , bool );
*/
//--------------------------------------------------------------------------------------------



/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void ZoneMap(){

	ZONA_NUM=3;
	
	//--------------------------------------
	PAL_setColors(0,palette_black,64);
	
	VDP_setWindowVPos(1,26);// 27max vertical Windows
	VDP_setTextPlane(WINDOW);//Textos "normales SGDK" se pintan en Window es temporal
	
	
	//PX=32*1;PY=32*7; // casillas_2 11 x 16
	
	PX=PY=32; //32 = 1x1 (la casilla 0x0 esta vacia siempre)
	
	JUGmueve=FALSE;
	panim=3;
	
	jugcontrol=3;
	
	jugpri=jugpricpy=TRUE;

	memcpy(&paleta64[16],penguin.palette->data,8*2);//16+8
	memcpy(&paleta64[32],&palette_green, 16 * 2);
	memcpy(&paleta64[48],&palette_blue, 16 * 2);
	
	SPR_init();
	
	penguinsp=SPR_addSprite(&penguin,160-12,112-26,TILE_ATTR(1,jugpri,0,0));
	
	//pdirc=pdircm=1;//up+>>
	pdirc=pdircm=4;//down+>>
	//pdirc=pdircm=2;//up+<<
	//pdirc=pdircm=3;//down+<<
	
	switch(pdircm){
		case 1:{SPR_setAnim(penguinsp,1);pflag=FALSE;}break;
		case 2:{SPR_setAnim(penguinsp,0);pflag=TRUE;}break;
		case 3:{SPR_setAnim(penguinsp,1);pflag=TRUE;}break;
		case 4:{SPR_setAnim(penguinsp,0);pflag=FALSE;}
	}
	
	SPR_setHFlip(penguinsp,pflag);
	SPR_setFrame(penguinsp,1);//parado
	
	jug2diso();
	

	old_musica=0;
	
	//SYS_showFrameLoad(TRUE);
	
	bool gat;
    while(1){//LOOP BASICO(NUNCA SE SALE!)
	
		
		loadzona();pintarAB();
		
		SYS_doVBlankProcess();//fix (60Hrz) pintarAB Se necesita ciclos de procesamiento para pintar Sprites
		SPR_update();
		
		if(zona1dat[ZONA_NUM].musica!=old_musica){
			old_musica=zona1dat[ZONA_NUM].musica;
			play_music(zona1dat[ZONA_NUM].musica);
		}
		
		PAL_fadeInAll(paleta64,20,FALSE);
		
		
		
		gat=TRUE;
		do{
			
			jugpenguin();
			
			if(!gat){
			
				if(BUTTONS[8]){ gat=TRUE;
					jugcontrol++; if(jugcontrol==4) jugcontrol=0;
					
				}
				
			}else if(!BUTTONS[0]) gat=FALSE;
			
			//VDP_drawInt(move_scroll,0,0,26);
			if(move_scroll) pintarAB();
			
			VDP_drawInt(SYS_getCPULoad(),2,38,27);
			SYS_doVBlankProcess(); // Renderizamos la pantalla
			if(BUTTONS[8] && BUTTONS[5]) SYS_hardReset();
			
		}while(!BUTTONS[7] || gat);
		
		PAL_fadeOutAll(10,FALSE);
		
		MEM_free(bgb);
		if(zona1dat[ZONA_NUM].PlanA){
			MEM_free(bga);VDP_clearPlane(BG_A,TRUE);
		}
		
		ZONA_NUM++;
		if(ZONA_NUM==TOP_ZONAS) ZONA_NUM=0;
    }
}


/*
static void object2D_maker(SpriteDefinition sprited, u8 num_obj , u8 pal , u16 X, u16 Y, bool v, bool h){
	
	object2D[num_obj].x= STARTXT+(X-Y)   +160;
	object2D[num_obj].y=(STARTYT+(X+Y)/2)+112;
	
	bool tempbol=TRUE;
	if(zona1dat[0].top_blxpri>0){
		for(u8 i=0;i<zona1dat[0].top_blxpri;i+=2){
			if(object2D[num_obj].x+48>zona1dat[0].blockpri[i] && object2D[num_obj].x-48<zona1dat[0].blockpri[i]
			&& object2D[num_obj].y+48>zona1dat[0].blockpri[i+1] && object2D[num_obj].y<=zona1dat[0].blockpri[i+1]){
				tempbol=FALSE; break;
			}
		}
	}
	
	object2D[num_obj].x-=12;object2D[num_obj].y-=26;
	
	object2D[num_obj].sprt=SPR_addSprite(&sprited, object2D[num_obj].x-posX, object2D[num_obj].y-posY, TILE_ATTR(pal,tempbol,v,h));
	SPR_setDepth(object2D[num_obj].sprt,-object2D[num_obj].y+112-26);
	
	SPR_setFrame(object2D[num_obj].sprt,1);//parado
	
}
*/


static void pintarAB(){
	
	//VDP_drawInt(posX,3,5,26);VDP_drawInt(posY,3,5,27);
	MAP_scrollTo(bgb,posX,posY);
	
	if(zona1dat[ZONA_NUM].PlanA) MAP_scrollTo(bga,posX,posY);
	move_scroll=FALSE;
	
	u8 i;
	//-----------------------------------------------------------
	/*for(i=0;i<3;i++){
		SPR_setPosition(object2D[i].sprt,object2D[i].x-posX,object2D[i].y-posY);
	}*/
	
	///////////////////////////////////////////////////
	
	SPR_setDepth(penguinsp,-posY);
	//VDP_drawInt(-posY,3,0,27);
	
	jugpri=TRUE;
	if(zona1dat[ZONA_NUM].top_blxpri>0){
		posXt=posX+160;posYt=posY+112;//centro de la pantalla
		//VDP_drawInt(posXt,3,10,26);VDP_drawInt(posYt,3,10,27);
		for(i=0;i<zona1dat[ZONA_NUM].top_blxpri;i+=2){
			if(posXt+48>zona1dat[ZONA_NUM].blockpri[i] && posXt-48<zona1dat[ZONA_NUM].blockpri[i] && posYt+48>zona1dat[ZONA_NUM].blockpri[i+1] && posYt<=zona1dat[ZONA_NUM].blockpri[i+1]){
				jugpri=FALSE; break;
			}
		}
	}
	
	if(jugpri!=jugpricpy){ jugpricpy=jugpri; 
		SPR_setPriorityAttribut(penguinsp,jugpri);
	}
	
	SPR_update();
}

static void loadzona(){
	
	memcpy(&paleta64[0],zona1[ZONA_NUM]->palette->data,16*2);
	paleta64[0]=0;//colro de fondo 100% negro
	paleta64[15]=RGB24_TO_VDPCOLOR(0xFFFFFF);//color 15 (texo...) Blanco
	
	
	VDP_loadTileSet(zona1[ZONA_NUM]->tileset,0,DMA);
	bgb=MAP_create(zona1[ZONA_NUM],BG_B,0);
	
	
	if(zona1dat[ZONA_NUM].PlanA){
		u8 ind;
		ind=zona1[ZONA_NUM]->tileset->numTile;
		VDP_loadTileSet(zona1b[ZONA_NUM]->tileset,ind,DMA);
		bga=MAP_create(zona1b[ZONA_NUM],BG_A,TILE_ATTR_FULL(0,1,0,0,ind));//PLANO A SIEMPRE PRIORIDAD ALTA!
		//ind+=zona1b[ZONA_NUM]->tileset->numTile;
	}
	
	//-------------------------------------------
	/*for(u8 i=1;i<4;i++){
		object2D_maker(penguin,i-1,i,32*(i+2),32*(i+2),0,randU8(0,1));
	}*/
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
	
	s16 PXC,PYC;
	if(pdir>0){	
		if(PX%32==0 && PY%32==0){
			if(!JUGmueve){ JUGmueve=TRUE; //SI TENEMOS UNA CORDENADA MULTIPLE 32
				pdircm=pdir;
			}
			PXC=PX;PYC=PY;//copiamos antiguas coordenadas x32
		}
	}
	
	// Si estamos en movimiento (porque no estamos alineados EN LA GRILLA)
	// calculamos el desplazamiento del sprite a usar
	
	if(JUGmueve){
		
		//-----------------------------------------------------------------
		if(pdirc!=pdircm){pdirc=pdircm;
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
		}
		
		panim--;
		if(panim==0){panim=3;
			SPR_nextFrame(penguinsp);
		}
		//---------------------------------------------------------------------
		
		PX32=(PX+16)/32;PY32=(PY+16)/32;//division 32
		
		//VDP_drawInt(PX32,0,10,26);VDP_drawInt(PY32,0,12,26);
		//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,0,27);
		
		switch(pdircm){
		case 1:
			if(PY>0){ PY-=VELPING;
				if(PY>15){ PY32--;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && PY-(PY32*32)<32) PY=PYC;
				}
			}
		break;
		case 2:
			PY+=VELPING;PY32++;
			//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
			if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PY32*32)-PY<32) PY=PYC;
		break;
		case 3:
			if(PX>0){ PX-=VELPING;
				if(PX>15){ PX32--;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && PX-(PX32*32)<32) PX=PXC;
				}
			}
		break;
		case 4:
			PX+=VELPING;PX32++;
			//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
			if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PX32*32)-PX<32) PX=PXC;
		}
		
		//VDP_drawInt(PX32,0,10,26);VDP_drawInt(PY32,0,12,26);
		//VDP_drawInt(PX+16,3,20,26);VDP_drawInt(PY+16,3,20,27);
		
		jug2diso();
		
		// Si tenemos una posicion valida (multiplo de 32), podemos dejar de movernos
		if(PX%32==0 && PY%32==0) JUGmueve=FALSE; //Y NOS MARCAMOS COMO QUIETOS
		move_scroll=TRUE;
		
	}else if(penguinsp->frameInd!=1){
		SPR_setFrame(penguinsp,1);
		panim=3;
	}
	
}

