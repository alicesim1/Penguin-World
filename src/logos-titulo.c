#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"
#define Version "1/7"

//res ficheros
#include "../res/logos.h"
#include "../res/titulo.h"
//-----------------------------------------------------

s16 vectorB[1];

//Definiciones de las funciones---------------------------------------------------
static void SEGALOGO();
static void SGDKlogo();
static void ALICESIM1();
static void Titulo_scrollLine();
//----------------------------------------


/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
void TITUTLO(){	
	//--------------------------------------
	VDP_loadFont(&font1,DMA);
	
	VDP_drawImageEx(BG_B,&disclaimer,1,20-10,14-6+IS_PALSYSTEM,TRUE,TRUE);
	JOY_waitPressBtnTime(900);
	VDP_clearPlane(BG_B,TRUE);
	
	SYS_doVBlankProcess();
	XGM_startPlay(M_titulo);
	
	SEGALOGO();
	if(BUTTONS[0]==0) SGDKlogo();
	if(BUTTONS[0]==0) ALICESIM1();
	
	//-------------------------------------------------------------
	VDP_setScrollingMode(HSCROLL_LINE,VSCROLL_PLANE);//titulo
	
	memcpy(&paleta64[0],titulo.palette->data, 16 * 2);
	memcpy(&paleta64[16],fondogr.palette->data, 16 * 2);
	memcpy(&paleta64[32],titush.palette->data, 16 * 2);
	memcpy(&paleta64[48],&palette_red, 16 * 2);
	
	//carga la imagen en VRAM y la dibuja en pantalla
	VDP_drawImageEx(BG_B,&fondogr,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,1),0,16+(IS_PALSYSTEM*2),FALSE,TRUE);
	//incrementa ind para 'apuntar' a una zona de VRAM libre para futuras tiles
	u16 ind=1+fondogr.tileset->numTile;
	
	VDP_drawImageEx(BG_A,&titulo,ind,4,1+IS_PALSYSTEM,FALSE,TRUE);
	ind+=titulo.tileset->numTile;
	
	bool gat2=FALSE;
	
	
	u8 contador2=randU8(10,50);
	bool gat3=FALSE;
	u8 num_lin=0;
	vectorB[0]=240;
	vectorB[1]=-vectorB[0];
	
	Titulo_scrollLine();
	
	PAL_fadeInAll(paleta64,120,TRUE);
	
	u16 i=240;
	while(BUTTONS[0]<10 && i>0){
		i-=3;vectorB[0]=i;vectorB[1]=-i;
		Titulo_scrollLine();
		SYS_doVBlankProcess();
	}
	
	vectorB[0]=vectorB[1]=0;
	Titulo_scrollLine();
	if(BUTTONS[0]>9){
		PAL_interruptFade();
		PAL_setColors(0,&paleta64[0],64,DMA);//restaura las paletas
	}
	PAL_setPalette(2,palette_black,DMA);
	
	VDP_drawImageEx(BG_B,&titush,TILE_ATTR_FULL(PAL2,FALSE,FALSE,FALSE,ind),3,IS_PALSYSTEM,FALSE,TRUE);
	ind+=titulo.tileset->numTile;
	
	VDP_drawImageEx(BG_A,&sgdk,TILE_ATTR_FULL(PAL2,FALSE,FALSE,FALSE,ind),31,24+IS_PALSYSTEM,FALSE,TRUE);
	
	VDP_setTextPalette(PAL2);
	VDP_drawText("Power By",31,23+IS_PALSYSTEM);
	VDP_drawText(Version,36,0);
	
	VDP_setTextPalette(PAL3);VDP_drawText("AliceSim1",9,22+IS_PALSYSTEM);VDP_setTextPalette(PAL0);VDP_drawText("- 2020-2021",19,22+IS_PALSYSTEM);
	VDP_drawText("Twitter:  @Alice_Sim1",9,24+IS_PALSYSTEM);
	u8 contador=0;
	bool gat=FALSE;
	
	bool gatS=TRUE;
	bool ok=FALSE;
	

	
	do{
		
		if(XGM_getElapsed()>1755) XGM_startPlay(M_titulo);
		
		if(!PAL_isDoingFade()){
			if(gat2) PAL_fadeIn(16,47,&paleta64[16],120,TRUE);
			else PAL_fadeOut(16,47,90,TRUE);
			gat2=!gat2;
		}
		
		contador++;
		if(contador==60){ contador=0;
			if(!gat){
				VDP_setTextPalette(PAL0);VDP_drawText("PULSA BOTON",11,18+IS_PALSYSTEM);
				VDP_setTextPalette(PAL3);VDP_drawText("START!",23,18+IS_PALSYSTEM);
			}
			else VDP_clearText(11,18+IS_PALSYSTEM,18);
			gat=!gat;
		}
		
		if (gat3){ gat3=FALSE;
			vectorB[0]=0;
			VDP_setHorizontalScrollLine(BG_A,num_lin+ScreTile8,vectorB,1,DMA);
		}
		
		contador2--;
		if(contador2==0){ contador2=randU8(1,25);
			vectorB[0]=randU8(0,10)-5;
			num_lin=randU8(10,112);
			VDP_setHorizontalScrollLine(BG_A,num_lin+ScreTile8,vectorB,1,DMA);
			gat3=TRUE;
		}
		
		
		if(BUTTONS[8] && !gatS) ok=TRUE;
		else if(gatS && !BUTTONS[8]) gatS=FALSE;
		
		SYS_doVBlankProcess(); // Renderizamos la pantalla
	}while(!ok);
	
	PAL_fadeOutAll(90,FALSE);
	
	VDP_clearPlane(BG_A,TRUE);VDP_clearPlane(BG_B,TRUE);
	
	VDP_setTextPalette(PAL0);
	VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
	
	XGM_stopPlay();SYS_doVBlankProcess();//necesita VSync para parar la musica por completo
	
	
}


static void Titulo_scrollLine(){
	for(u8 num_lin=9;num_lin<120;num_lin+=2) VDP_setHorizontalScrollLine(BG_A,num_lin+ScreTile8,vectorB,2,DMA);
}

static void SEGALOGO(){
	
	u16 paleta16or[16];
	memcpy(&paleta16or[0],logosega.palette->data, 16 * 2);
	PAL_setPalette(0,palette_black,DMA);
	
	VDP_drawImageEx(BG_B,&logosega,1,20-6,14-2+IS_PALSYSTEM,FALSE,TRUE);
	
	for(u8 i=1;i<13;i++){
		PAL_fadeIn(i,i,&paleta16or[i],3,TRUE);
		do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
		if(BUTTONS[0]>9)break;
	}
	PAL_fadeIn(14,15,&paleta16or[14],15,TRUE);
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(900);
	else PAL_setPalette(PAL0,logosega.palette->data,DMA);
	
	PAL_fadeOutAll(20,FALSE);
	VDP_clearPlane(BG_B,TRUE);
}



static void SGDKlogo(){
	
	u16 paleta16or[16];
	memcpy(&paleta16or[0],sgdklogo.palette->data, 16 * 2);
	PAL_setPalette(0,palette_black,DMA);
	
	VDP_drawImageEx(BG_B,&sgdklogo,1,20-4,14-4+IS_PALSYSTEM,FALSE,TRUE);
	PAL_fadeIn(0,15,&paleta16or[0],10,TRUE);
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(750);
	else PAL_setPalette(PAL0,sgdklogo.palette->data,DMA);
	
	PAL_fadeOutAll(20,FALSE);
	VDP_clearPlane(BG_B,TRUE);
}



static void ALICESIM1(){
	
	u16 colblank[1]={RGB24_TO_VDPCOLOR(0xFFFFFF)};
	u16 paleta16or[16];
	
	memcpy(&paleta16or[0],alicesim1.palette->data, 16 * 2);
	PAL_setPalette(0,palette_black,DMA);
	PAL_setPalette(1,palette_grey,DMA);
	VDP_setTextPalette(PAL1);
	
	VDP_drawImageEx(BG_B,&alicesim1,1,20-11,14-4+IS_PALSYSTEM,FALSE,TRUE);
	//Volvemos a activar las interrupciones del VDP
	
	u8 i;
	for(i=1;i<16;i+=2){
		PAL_fadeIn(i,i,&paleta16or[i],3,TRUE);
		do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
		if(BUTTONS[0]>9)break;
	}
	VDP_drawText("Alicia Sanchez Martos",10,22+IS_PALSYSTEM);
	if(BUTTONS[0]==0){
		for(i=0;i<16;i+=2){
			PAL_fade(i,i+1,&paleta16or[i],&colblank[0],1,FALSE);
			PAL_fade(i,i+1,&colblank[0],&paleta16or[i],3,FALSE);
			do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
			if(BUTTONS[0]>9)break;
		}
	}
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(750);
	else PAL_setPalette(0,paleta16or,DMA);
	
	PAL_fadeOutAll(20,FALSE);
	
	VDP_clearPlane(BG_B,TRUE);VDP_clearPlane(BG_A,TRUE);
}

