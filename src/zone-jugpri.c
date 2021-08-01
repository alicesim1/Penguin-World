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

const MapDefinition* const zona1b[] = {0,&z1h1b,0,&z1h3b};
Map* bga; //PLANO A (Capa superior Prioridad Alta)
//-----------------------------------------------------------

u16 posX,posY;
u16 TopXMap,TopYMap;
u16 posXt,posYt;

static void loadzona();
static void pintarAB();
static void pintarfULLAB();
static void SPR_PRIORITY();

u8 ZONA_NUM,DestZONA_NUM;
u8 DestPX32,DestPY32;
bool PUERTA_SAL;

u16 STARTXT;


//---------------------------------------------------------
// DATA
//---------------------------------------------------------
//const u8 jugcontrol=3;//0=diagonales, 1=UP=UP+>>, 2=UP=UP+<<, 3=0+1

//------------------------------------------------------------------------------------------

Sprite* penguinsp; //atributo tipo Sprite
bool JUGmueve;
const u8 const VELPING=2;
s16 PX,PY;
u8 PX32,PY32,PX32C,PY32C;//BLOQUES *32
bool pflag;
u8 pdirc,pdir,pdircm;
u8 panim;
bool jugpri,jugpricpy;

static void jug2diso();
static void jugpenguin();

//------------------------------------------------------------------------------------------


/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void ZoneMap(){
	old_musica=0;
	ZONA_NUM=0;
	
	PX=PY=32;
	//PX=32*0;PY=32*0; 
	
	//----------------------------------------------
	
	memcpy(&paleta64[16],penguin.palette->data,8*2);//16+8
	memcpy(&paleta64[32],dig_marco1.palette->data,8*2);//16+8
	//memcpy(&paleta64[48],&palette_blue, 16 * 2);
	
	
	SPR_init();
	
	Sprite* dig_temp[3];
	dig_temp[0]=SPR_addSpriteEx(&dig_marco1,0,0,diag_ind,0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	dig_temp[1]=SPR_addSpriteEx(&dig_marco2,0,0,diag_ind+1,0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	dig_temp[2]=SPR_addSpriteEx(&dig_marco3,0,0,diag_ind+1+4,0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	
	
	JUGmueve=FALSE;
	panim=3;
	jugpri=jugpricpy=TRUE;
	
	penguinsp=SPR_addSpriteEx(&penguin,160-12,ScreenMY-18,TILE_ATTR(1,jugpri,FALSE,FALSE),0,SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	SPR_setVisibility(penguinsp,VISIBLE);

	//pdirc=pdircm=1;//up+>>
	pdirc=pdircm=4;//down+>>
	//pdirc=pdircm=2;//down+<<
	//pdirc=pdircm=3;//up+<<
	switch(pdircm){
		case 1:{SPR_setAnim(penguinsp,1);pflag=FALSE;}break;
		case 2:{SPR_setAnim(penguinsp,0);pflag=TRUE;}break;
		case 3:{SPR_setAnim(penguinsp,1);pflag=TRUE;}break;
		case 4:{SPR_setAnim(penguinsp,0);pflag=FALSE;}
	}
	SPR_setHFlip(penguinsp,pflag);
	SPR_setFrame(penguinsp,1);//parado
	
	
	if(CursorON){ 
		cursorsp=SPR_addSpriteEx(&cursor,160,ScreenMY,TILE_ATTR(0,TRUE,FALSE,FALSE),0,SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_INSERT_HEAD);
		SPR_setVisibility(cursorsp,HIDDEN);
		_JOYsetXY(160,ScreenMY);
	}
	
	SPR_update();
	
	for(u8 i=0;i<3;i++)	SPR_releaseSprite(dig_temp[i]);
	
	SYS_doVBlankProcess();
	//--------------------------------------------------
	
	//--------------------------------------------------
	
	//SYS_showFrameLoad(TRUE);//Sprite 0: prioridad maxima, tile nº: 1534, pal 0
	
	PUERTA_SAL=TRUE;
	
    while(1){//LOOP BASICO(NUNCA SE SALE!)
		
		loadzona();//SYS_doVBlankProcess(); X 4 / 8
		
		if(zona1dat[ZONA_NUM].musica!=old_musica){
			old_musica=zona1dat[ZONA_NUM].musica;
			play_music(zona1dat[ZONA_NUM].musica);
		}
		
		SYS_doVBlankProcess();//Evita sobre carga DMA SPRITES
		SPR_update();
		
		PAL_fadeInAll(paleta64,20,FALSE);
		
		gat=TRUE;
		PUERTA_SAL=FALSE;
		
		if(CursorON) SPR_setVisibility(cursorsp,VISIBLE);
		
		do{
			
			jugpenguin();
			
			if(PUERTA_SAL){
				if(CursorON) SPR_setVisibility(cursorsp,HIDDEN);
				if(!PAL_isDoingFade()) PAL_fadeOutAll(20,TRUE);//transicion fade
			}else{
				if(!gat){
					if(!JUGmueve){
						if(BUTTONS[6]){ gat=TRUE;
							dialogo(0,0,2,2);
						}
						
						if(BUTTONS[10]){ gat=TRUE;
							dialogo(100,100,1,1);
						}
						
						if(BUTTONS[5]){ gat=TRUE;
							dialogo(160-((16+(32*4))/2),ScreenMY-((16+(32*2))/2),4,2);
						}
						
						if(BUTTONS[7]){ gat=TRUE;
							dialogo(160-((16+(32*6))/2),ScreenTY-(16+(32*2)),6,2);
						}
						
						if(BUTTONS[9]){ gat=TRUE;
							dialogo(160-((16+(32*8))/2),ScreenTY-(16+(32*2)),8,1);
						}
					}
				}else if(!BUTTONS[0]) gat=FALSE;
				
				
				if(CursorON){
					_JOYupdateMouse();
				}
			}
			
			//VDP_drawInt(SYS_getCPULoad(),2,38,ScreenY);
			SPR_update();
			SYS_doVBlankProcess(); // Renderizamos la pantalla
			
		}while(!PUERTA_SAL || PAL_isDoingFade());
		
		MEM_free(bgb);
		if(zona1dat[ZONA_NUM].PlanA) MEM_free(bga);

		PX=32*DestPX32;PY=32*DestPY32;
		ZONA_NUM=DestZONA_NUM;
		
    }
}

static void pintarAB(){	 //ingame al movernos con el jugador
	MAP_scrollTo(bgb,posX,posY);
	if(zona1dat[ZONA_NUM].PlanA) MAP_scrollTo(bga,posX,posY);
}

static void pintarfULLAB(){	//para pantallas de carga
	MAP_scrollTo(bgb,posX,posY);
	SYS_doVBlankProcess();SYS_doVBlankProcess();
	if(zona1dat[ZONA_NUM].PlanA){
		MAP_scrollTo(bga,posX,posY);
		SYS_doVBlankProcess();SYS_doVBlankProcess();
	}
}

static void loadzona(){
	
	VDP_clearPlane(BG_B,TRUE);VDP_clearPlane(BG_A,TRUE);
	//Limpiar el plano especificado (usando DMA).
	
	memcpy(&paleta64[0],zona1[ZONA_NUM]->palette->data,16*2);
	paleta64[0]=0;//colro de fondo 100% -Negro
	paleta64[15]=0xFFF;//color 15 (texo...) Blanco
	
	//u16 ind=TILE_USERINDEX;
	VDP_loadTileSet(zona1[ZONA_NUM]->tileset,0,CPU);
	bgb=MAP_create(zona1[ZONA_NUM],BG_B,0);
	u16 ind = zona1[ZONA_NUM]->tileset->numTile;
	
	if(zona1dat[ZONA_NUM].PlanA){
		VDP_loadTileSet(zona1b[ZONA_NUM]->tileset,ind,CPU);
		bga=MAP_create(zona1b[ZONA_NUM],BG_A,TILE_ATTR_FULL(0,1,0,0,ind));	//PLANO A SIEMPRE PRIORIDAD ALTA!
		//ind += zona1b[ZONA_NUM]->tileset->numTile;
	}
	
	//Pintado del mapa por completo
	pintarfULLAB();//pintado completo 1º vez.
	
	//8x4=32(la mitad de una casilla isometrica) * casillasY)
	STARTXT=zona1dat[ZONA_NUM].Ytop*32;
	STARTXT-=32;//fix SGDK 1.65
	jug2diso();
	
	pintarfULLAB();//necesaria llamar 2º vez, para actualizar el mapa
	
	
	SPR_PRIORITY();
	
}


static void SPR_PRIORITY(){
	
	///////////////////////////////////////////////////
	
	if(zona1dat[ZONA_NUM].top_blxpri>0){
		jugpri=TRUE;
		//VDP_drawInt(-posY,3,0,27);
		posXt=posX+160;posYt=posY+ScreenMY;//centro de la pantalla
		
		//VDP_drawInt(posXt,4,10,26);VDP_drawInt(posYt,4,10,27);
		
		for(u8 i=0;i<zona1dat[ZONA_NUM].top_blxpri;i+=2){
			if(posXt+48>zona1dat[ZONA_NUM].blockpri[i] && posXt-48<zona1dat[ZONA_NUM].blockpri[i] && posYt+48>zona1dat[ZONA_NUM].blockpri[i+1] && posYt<=zona1dat[ZONA_NUM].blockpri[i+1]){
				jugpri=FALSE; break;
			}
		}
		if(jugpri!=jugpricpy){ jugpricpy=jugpri; 
			SPR_setPriorityAttribut(penguinsp,jugpri);
		}
	}
	
}



//Calculo de jugador a isometrico
static void jug2diso(){ //PX->posX
	posX= STARTXT +   PX - PY;
	posY= fixAlturaY + ((PX + PY)>>1);
}
 
static void jugpenguin(){
	
	pdir=0;
	if(!PUERTA_SAL){
		if 		(BUTTONS[1] && BUTTONS[4] && !BUTTONS[2] && !BUTTONS[3])pdir=1;//up+>>
		else if (BUTTONS[1] && !BUTTONS[3] && !BUTTONS[4])pdir=1;
		else if (BUTTONS[2] && BUTTONS[3] && !BUTTONS[1] && !BUTTONS[4])pdir=2;//down+<<
		else if (BUTTONS[2] && !BUTTONS[3] && !BUTTONS[4])pdir=2;
		else if (BUTTONS[1] && BUTTONS[3] && !BUTTONS[2] && !BUTTONS[4])pdir=3;//up+<<
		else if (BUTTONS[3] && !BUTTONS[1] && !BUTTONS[2])pdir=3;
		else if (BUTTONS[2] && BUTTONS[4] && !BUTTONS[1] && !BUTTONS[3])pdir=4;//down+>>
		else if (BUTTONS[4] && !BUTTONS[1] && !BUTTONS[2])pdir=4;
	}
	
	s16 PXC,PYC;
	
	if(pdir>0){	
		if((PX&31)==0 && (PY&31)==0){
			if(!JUGmueve){
				JUGmueve=TRUE; //SI TENEMOS UNA CORDENADA MULTIPLE 32
				pdircm=pdir;
			}
			PXC=PX;PYC=PY;//copiamos antiguas coordenadas x32
		}
	}
	
	// Si estamos en movimiento (porque no estamos alineados EN LA GRILLA)
	// calculamos el desplazamiento del sprite a usar
	
	if(JUGmueve){
		
		//---------------------------------------------------------------------
		
		PX32=(PX+16)>>5;PY32=(PY+16)>>5;//division 32
		
		if(PX32!=PX32C || PY32!=PY32C || pdirc!=pdircm){ PX32C=PX32; PY32C=PY32;
			
			//VDP_drawInt(PX32,0,20,ScreenY-1);VDP_drawInt(PY32,0,22,ScreenY-1);
			
			//VDP_drawInt(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)],0,20,ScreenY);
			
			u8 t;
			for(u8 i=1;i<=zona1dat[ZONA_NUM].topPuertas;i++){//1,2,3,
				t=6*(i-1);//0=(0,1,2,3,4,5),1=(6,7,8,9,10,11),2=(12,13,14,15,16,17),
				if(PX32==zona1dat[ZONA_NUM].puertas[1+t] && PY32==zona1dat[ZONA_NUM].puertas[t] && pdircm==zona1dat[ZONA_NUM].puertas[2+t]){
					DestZONA_NUM=zona1dat[ZONA_NUM].puertas[3+t];
					DestPX32=zona1dat[ZONA_NUM].puertas[5+t];
					DestPY32=zona1dat[ZONA_NUM].puertas[4+t];
					PUERTA_SAL=TRUE;
				}
			}
			
			if(pdirc!=pdircm){  pdirc=pdircm;
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
				
				//VDP_drawInt(pdircm,0,25,ScreenY-1);
			}
			
		}
		
		switch(pdircm){
		case 1:
			if(PY>0){ 
				PY-=VELPING;
				if(PY>15){ 
					PY32--;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && PY-(PY32*32)<32) PY=PYC;
				}
			}
		break;
		case 2:
			PY+=VELPING;
			PY32++;
			//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
			if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PY32*32)-PY<32) PY=PYC;
		break;
		case 3:
			if(PX>0){ 
				PX-=VELPING;
				if(PX>15){ 
					PX32--;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && PX-(PX32*32)<32) PX=PXC;
				}
			}
		break;
		case 4:
			PX+=VELPING;
			PX32++;
			//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
			if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PX32*32)-PX<32) PX=PXC;
		}
		
		//VDP_drawInt(PX32,2,10,26);VDP_drawInt(PY32,2,12,26);
		//VDP_drawInt(PX+16,4,20,26);VDP_drawInt(PY+16,4,20,27);
		
		// Si tenemos una posicion valida (multiplo de 32), podemos dejar de movernos
		if((PX&31)==0 && (PY&31)==0) JUGmueve=FALSE; //Y NOS MARCAMOS COMO QUIETOS
		
		if(PX!=PXC || PY!=PYC){
		
			panim--;
			if(panim==0){panim=3;
				SPR_nextFrame(penguinsp);
			}
			
			jug2diso();
			pintarAB();
			
			SPR_PRIORITY();
			
			//KLog_U2("PX:", PX," PY:", PY);
			//KLog_S2("posX:", posX," posY:", posY);
		}
		
		
	}else {
		PXC=PX;PYC=PY;
	}
	
	if(PX==PXC && PY==PYC && penguinsp->frameInd!=1){
		SPR_setFrame(penguinsp,1);
		panim=3;
	}
	
}

