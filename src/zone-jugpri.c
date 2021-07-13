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

#define diag_ind 1200 //hex:4B0

static void dialogo(u16,u16,u8,u8);
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
	//old_musica=0;
	
	ZONA_NUM=3;
	PX=PY=32;
	//PX=32*0;PY=32*0; 
	
	//----------------------------------------------
	VDP_loadFont(&font2,CPU);VDP_setTextPalette(2);
	
	memcpy(&paleta64[16],penguin.palette->data,8*2);//16+8
	memcpy(&paleta64[32],dig_marco1.palette->data,8*2);//16+8
	
	//PAL_setColors(32,dig_marco1.palette->data,8,CPU);
	//memcpy(&paleta64[32],&palette_green, 16 * 2);
	//memcpy(&paleta64[48],&palette_blue, 16 * 2);
	
	
	SPR_init();
	
	//VDP_drawInt(spriteVramSize,0,0,ScreenY);
	
	JUGmueve=FALSE;
	panim=3;
	jugpri=jugpricpy=TRUE;
	
	penguinsp=SPR_addSpriteEx(&penguin,160-12,ScreenMY-18,TILE_ATTR(1,jugpri,FALSE,FALSE),
	0,SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
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
	
	
	if(padraton==PORT_TYPE_MOUSE || padraton==PORT_TYPE_PAD){ 
		cursorsp=SPR_addSpriteEx(&cursor,160,ScreenMY,TILE_ATTR(0,TRUE,FALSE,FALSE),
		0,SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_INSERT_HEAD);
		SPR_setVisibility(cursorsp,VISIBLE);
		_JOYsetXY(160,ScreenMY);
	}
	
	
	//--------------------------------------------------
	Sprite* SPRITE_TEMP[3];
	SPRITE_TEMP[0]=SPR_addSpriteEx(&dig_marco1,0,0,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);	
	SPRITE_TEMP[1]=SPR_addSpriteEx(&dig_marco2,0,0,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	SPRITE_TEMP[2]=SPR_addSpriteEx(&dig_marco3,0,0,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	SPR_update();//SPR_FLAG_AUTO_TILE_UPLOAD FUNCIONE! Volvado automatico de tileset de los sprites a la VRAM
	for(u8 i=0;i<3;i++)	SPR_releaseSprite(SPRITE_TEMP[i]);
	SYS_doVBlankProcess();//Evita sobre carga DMA SPRITES
	
	//--------------------------------------------------
	
	//SYS_showFrameLoad(TRUE);//Sprite 0: prioridad maxima, tile nº: 1534, pal 0
	
	PUERTA_SAL=TRUE;
	
    while(1){//LOOP BASICO(NUNCA SE SALE!)
		
		loadzona();//SYS_doVBlankProcess(); X 4 / 8
		
		/*if(zona1dat[ZONA_NUM].musica!=old_musica){
			old_musica=zona1dat[ZONA_NUM].musica;
			play_music(zona1dat[ZONA_NUM].musica);
		}*/
		
		SYS_doVBlankProcess();//Evita sobre carga DMA SPRITES
		SPR_update();
		
		PAL_fadeInAll(paleta64,20,TRUE);
		
		gat=TRUE;
		PUERTA_SAL=FALSE;
		
		do{
			
			jugpenguin();
			
			if(PUERTA_SAL){
				if(!PAL_isDoingFade()) PAL_fadeOutAll(20,TRUE);//transicion fade
			}else{
				if(!gat){
					if(!JUGmueve){
						if(BUTTONS[6]){ gat=TRUE;
							dialogo(0,0,2,2);
						}
						
						if(BUTTONS[5]){ gat=TRUE;
							dialogo(160-((16+(32*4))/2),ScreenMY-((16+(32*2))/2),4,2);
						}
						
						if(BUTTONS[7]){ gat=TRUE;
							dialogo(160-((16+(32*6))/2),ScreenTY-(16+(32*2)),6,2);
						}
					}
				}else if(!BUTTONS[0]) gat=FALSE;
				
				
				if(padraton==PORT_TYPE_MOUSE || padraton==PORT_TYPE_PAD){
					_JOYupdateMouse();
				}
			}
			
			VDP_drawInt(SYS_getCPULoad(),2,38,ScreenY);
			SPR_update();
			SYS_doVBlankProcess(); // Renderizamos la pantalla
			
		}while(!PUERTA_SAL || PAL_isDoingFade());
		
		MEM_free(bgb);
		if(zona1dat[ZONA_NUM].PlanA) MEM_free(bga);

		PX=32*DestPX32;PY=32*DestPY32;
		ZONA_NUM=DestZONA_NUM;
		
    }
}


static void dialogo(u16 x,u16 y,u8 ancho, u8 alto){
	if(ancho<1) ancho=1;
	if(alto<1) alto=1;
	
	u8 i;
	Sprite* dig_marcoE[4];
	Sprite* dig_marcoH[ancho];//superior
	Sprite* dig_marcoV[alto];//izquierdaq
	
	Sprite* dig_marcoHd[ancho];//abajo
	Sprite* dig_marcoVd[alto];//derecho
	
	//-----------------------------------------------------------------
	dig_marcoE[0]=SPR_addSpriteEx(&dig_marco1,x,y,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	dig_marcoE[1]=SPR_addSpriteEx(&dig_marco1,x+8+(32*ancho),y,TILE_ATTR_FULL(2,TRUE,FALSE,TRUE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	dig_marcoE[2]=SPR_addSpriteEx(&dig_marco1,x,y+8+(32*alto),TILE_ATTR_FULL(2,TRUE,TRUE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	dig_marcoE[3]=SPR_addSpriteEx(&dig_marco1,x+8+(32*ancho),y+8+(32*alto),TILE_ATTR_FULL(2,TRUE,TRUE,TRUE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	for(i=0;i<4;i++){
		SPR_setVisibility(dig_marcoE[i],VISIBLE);SPR_setDepth(dig_marcoE[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	u16 x2;
	u16 y2=y+8+(32*alto);
	
	for(i=0;i<ancho;i++){
		x2=x+8+(32*i);
		dig_marcoH [i]=SPR_addSpriteEx(&dig_marco2,x2,y ,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		dig_marcoHd[i]=SPR_addSpriteEx(&dig_marco2,x2,y2,TILE_ATTR_FULL(2,TRUE,TRUE ,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		SPR_setVisibility(dig_marcoH[i],VISIBLE);SPR_setDepth(dig_marcoH[i],SPR_MIN_DEPTH+2);//-32766	
		SPR_setVisibility(dig_marcoHd[i],VISIBLE);SPR_setDepth(dig_marcoHd[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	x2=x+8+(32*ancho);
	for(i=0;i<alto;i++){
		y2=y+8+(32*i);
		dig_marcoV [i]=SPR_addSpriteEx(&dig_marco3,x ,y2,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		dig_marcoVd[i]=SPR_addSpriteEx(&dig_marco3,x2,y2,TILE_ATTR_FULL(2,TRUE,FALSE,TRUE ,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		SPR_setVisibility(dig_marcoV[i],VISIBLE);SPR_setDepth(dig_marcoV[i],SPR_MIN_DEPTH+2);//-32766
		SPR_setVisibility(dig_marcoVd[i],VISIBLE);SPR_setDepth(dig_marcoVd[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	Sprite* dig_lienzo[ancho*alto];
	u8 p=0;
	for(u8 h=0;h<ancho;h++){
		for(u8 v=0;v<alto;v++){
			dig_lienzo[p]=SPR_addSpriteEx(&dig_marco4,x+8+(32*h),y+8+(32*v),TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4+4+(16*p)),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			SPR_setVisibility(dig_lienzo[p],VISIBLE);SPR_setDepth(dig_lienzo[p],SPR_MIN_DEPTH+2);//-32766
			p++;
			//--------------------------------------------------------------------
		}
	}
	
	SPR_update();
	do{
		if(gat && !BUTTONS[6]) gat=FALSE;
		SYS_doVBlankProcess();
	}while(!BUTTONS[6] || gat);	gat=TRUE;
	
	for(i=0;i<4;i++)	SPR_releaseSprite(dig_marcoE[i]);
	
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoH[i]);
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoHd[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoV[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoVd[i]);
	
	for(i=0;i<p;i++)	SPR_releaseSprite(dig_lienzo[i]);
}


static void pintarAB(){	 //ingame al movernos con el jugador
	MAP_scrollTo(bgb,posX,posY);
	if(zona1dat[ZONA_NUM].PlanA) MAP_scrollTo(bga,posX,posY);
}

static void pintarfULLAB(){	//para pantallas de carga
	
	//DMA_setMaxQueueSize();
	
	MAP_scrollTo(bgb,posX,posY);
	SYS_doVBlankProcess();SYS_doVBlankProcess();
	if(zona1dat[ZONA_NUM].PlanA){
		MAP_scrollTo(bga,posX,posY);
		SYS_doVBlankProcess();SYS_doVBlankProcess();
	}
	
	//DMA_setMaxQueueSizeToDefault();
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
	posY= 8 - ScreTile8 + ((PX + PY)>>1);
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
			if(PY>0){ //solo camina si estamos dentro en cordenadas
				PY-=VELPING;
				if(PY>15){ //comprueba si es superior +15 pixeles
					PY32--;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && PY-(PY32*32)<32) PY=PYC;
				}
			}
		break;
		case 2:
			if(PY<zona1dat[ZONA_NUM].Ytop<<5){ //evita extraño bug //0,0,0,B,0,0
				PY+=VELPING;
				if(PY<(zona1dat[ZONA_NUM].Ytop<<5)-15){ 
					PY32++;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PY32*32)-PY<32) PY=PYC;
				}
			}
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
			if(PX<(zona1dat[ZONA_NUM].Xtop-1)<<5){ 
				PX+=VELPING;
				if(PX<((zona1dat[ZONA_NUM].Xtop-1)<<5)-15){ 
					PX32++;
					//VDP_drawInt(zona1dat[0].casillas[PX32+(PY32*8)],0,2,27);
					if(zona1dat[ZONA_NUM].casillas[PX32+(PY32*zona1dat[ZONA_NUM].Xtop)]!=1 && (PX32*32)-PX<32) PX=PXC;
				}
			}
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



