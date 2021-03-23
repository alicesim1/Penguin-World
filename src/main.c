#include "genesis.h"//OBLIGATORIO! [[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/

/////////DECLARAMOS LAS LIBRERIAS Y RECURSOS

//----------------------------------------
#include "basicos.h"

#include "logos.h"
#include "titulo.h"

//-----------------------------------------
#define Version "0.05"
//------------------------
char char_salida[16]; //Cadena de 16 caracteres(para rellenar o vaciar) No se debe superar!

//-----------------------------------------------------
u16 paleta64[64];

//para llevar la cuenta de tiles en VRAM
//reserva las primeras 16 posiciones de la VRAM, de la 0 a la 15 (ind = 16)
u16 ind;


//Definiciones de las funciones---------------------------------------------------
void SEGALOGO();
void SGDKlogo();
void ALICESIM1();
void TITUTLO();
u8 randomInRangeU8(u8,u8);
void VDP_drawInt(s32,u8,u8,u8);

//Manejador de entrada
u16 BUTTONS[9];
void inputHandler(u16,u16,u16);

/////////////////////////////INICIO DE TODO//////////////////////////////////////////////////
int main()
{	
	//KLog("INICIO!");
	/*desactiva el acceso al VDP
	Desactiva temporalmente cualquier tipo de interrupción (Vertical, Horizontal and External) al
	VDP, de esa forma podemos 'toquetearlo' a placer sin que una interrupción pare lo que estamos
	haciendo y deje a mitad el trabajo*/
	SYS_disableInts();
	
	VDP_loadFont(&font1,DMA);

	VDP_setScrollingMode(HSCROLL_LINE,VSCROLL_PLANE);//titulo
	//--------------------------------------
	JOY_setEventHandler(&inputHandler);
	
	VDP_drawImageEx(BG_B,&disclaimer,1,20-10,14-6,TRUE,TRUE);
	SYS_enableInts();
	JOY_waitPressBtnTime(900);
	SYS_disableInts();
	
	XGM_startPlay(M_titulo);
	
	SEGALOGO();
	if(BUTTONS[0]==0) SGDKlogo();
	if(BUTTONS[0]==0) ALICESIM1();
	
    while(1) //LOOP BASICO(NUNCA SE SALE!)
    {	
		
		TITUTLO();
		
		PAL_setColors(0,paleta64,64);
		
		VDP_drawText("Nuevo??",11,19);
		
		SYS_enableInts();
		
		while(!BUTTONS[5]) //loop 
		{
			VDP_showFPS(TRUE);//1x1
			VDP_showCPULoad();//1x2
			SYS_doVBlankProcess(); // Renderizamos la pantalla
		}
		
		SYS_hardReset();//reiniciamos todo!
		//SYS_die("Mensaje de error! Reinicia la MD/GS");
    }
    return 0;
}


void SEGALOGO(){
	
	VDP_clearPlane(BG_B,TRUE);
	u16 paleta16or[16];
	memcpy(&paleta16or[0],logosega.palette->data, 16 * 2);
	VDP_setPaletteColors(0,palette_black,16);
	
	VDP_drawImageEx(BG_B,&logosega,1,20-6,14-2,FALSE,TRUE);
	SYS_enableInts();
	
	for(u8 i=1;i<13;i++){
		PAL_fadeIn(i,i,&paleta16or[i],3,TRUE);
		do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
		if(BUTTONS[0]>9)break;
	}
	PAL_fadeIn(14,15,&paleta16or[14],15,TRUE);
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(900);
	else VDP_setPalette(PAL0,logosega.palette->data);
	
	PAL_fadeOutAll(20,FALSE);
	
	SYS_disableInts();
}



void SGDKlogo(){

	VDP_clearPlane(BG_B,TRUE);
	u16 paleta16or[16];
	memcpy(&paleta16or[0],sgdklogo.palette->data, 16 * 2);
	VDP_setPaletteColors(0,palette_black,16);
	
	VDP_drawImageEx(BG_B,&sgdklogo,1,20-4,14-4,FALSE,TRUE);
	SYS_enableInts();
	PAL_fadeIn(0,15,&paleta16or[0],10,TRUE);
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(750);
	else VDP_setPalette(PAL0,sgdklogo.palette->data);
	
	PAL_fadeOutAll(20,FALSE);
	SYS_disableInts();
	
}



void ALICESIM1(){
	
	VDP_clearPlane(BG_B,TRUE);
	u16 colblank[1]={RGB24_TO_VDPCOLOR(0xFFFFFF)};
	u16 paleta16or[16];
	
	memcpy(&paleta16or[0],alicesim1.palette->data, 16 * 2);
	VDP_setPaletteColors(0,palette_black,16); 
	VDP_drawImageEx(BG_B,&alicesim1,1,20-11,14-3,FALSE,TRUE);
	//Volvemos a activar las interrupciones del VDP
	SYS_enableInts();
	
	u8 i;
	for(i=1;i<16;i+=2){
		PAL_fadeIn(i,i,&paleta16or[i],3,TRUE);
		do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
		if(BUTTONS[0]>9)break;
	}
	if(BUTTONS[0]==0){
		for(i=0;i<16;i+=2){
			PAL_fade(i,i+1,&paleta16or[i],&colblank[0],1,FALSE);
			PAL_fade(i,i+1,&colblank[0],&paleta16or[i],3,FALSE);
			do{SYS_doVBlankProcess();}while(PAL_isDoingFade() && BUTTONS[0]==0);
			if(BUTTONS[0]>9)break;
		}
	}
	
	if(BUTTONS[0]==0)JOY_waitPressBtnTime(750);
	else VDP_setPaletteColors(0,&paleta16or[0],16);
	
	PAL_fadeOutAll(20,FALSE);
	
	SYS_disableInts();
}

void TITUTLO(){
	
	VDP_clearPlane(BG_B,TRUE);
	
	/*VDP_setPalette(PAL0,titulo.palette->data);//Seteamos la paleta 16 colores del titulo!
	VDP_setPalette(PAL1,fondogr.palette->data);
	VDP_setPalette(PAL2,titush.palette->data);*/
	// prepare palettes (BGB image contains the 4 palettes data)
	//PAL_getColors(0,paleta64,64);//COPIAMOS TODA LA PALETA 64 COLORES 
	/*u16 paleta32[32];
	PAL_getColors(16,paleta32,32);*/
	
	
	memcpy(&paleta64[0],titulo.palette->data, 16 * 2);
	memcpy(&paleta64[16],fondogr.palette->data, 16 * 2);
	memcpy(&paleta64[32],titush.palette->data, 16 * 2);
	memcpy(&paleta64[48],&palette_red, 16 * 2);
	
	
	/*Ponemos TODA LA PALETA (las 4 paletas) completamente en negro
	VDP_setPaletteColors( indice_color(0-63), valor_RGB, num_colores_afectados)
	Esta función pone un total de 'num_colores_afectados' al valor 'valor_RGB'.
	Esto lo hace desde el color 'indice_color' hasta 'indice_color+num_colores_afectados'
	En este caso: del color 0 al 63, todos -> un total de 64 colores
	*/
	// El motivo: hacer un fade_in (de pantalla negra a pantalla normal)
	//VDP_setPaletteColors(0,palette_black,64); 
	//palette_black = paleta SGDK negros
	
	
	//carga la imagen en VRAM y la dibuja en pantalla
	VDP_drawImageEx(BG_B,&fondogr,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,1),0,16,FALSE,TRUE);
	//incrementa ind para 'apuntar' a una zona de VRAM libre para futuras tiles
	ind=1+fondogr.tileset->numTile;
	
	//carga la imagen en VRAM y la dibuja en pantalla
	VDP_drawImageEx(BG_A,&titulo,ind,4,1,FALSE,TRUE);
	//incrementa ind para 'apuntar' a una zona de VRAM libre para futuras tiles
	ind+=titulo.tileset->numTile;
	
	bool gat2=FALSE;
	
	s16 vectorB[1];
	u8 contador2=randomInRangeU8(10,50);
	bool gat3=FALSE;
	
	vectorB[0]=240;
	vectorB[1]=-vectorB[0];
	u8 num_lin;
	for(num_lin=9;num_lin<120;num_lin+=2) VDP_setHorizontalScrollLine(BG_A,num_lin,vectorB,2,CPU);
	
	//Volvemos a activar las interrupciones del VDP
	SYS_enableInts();
	
	//FACE IN
	/* PAL_fadeIn(from_color, to_color, pal_final, num_frames, asyn)
	Esta función realiza un fade-in de la paleta actual a la paleta 'pal_final',
	utilizando para ello 'num_frames'. Tener en cuenta 60 frames/seg (NTCS).
	Podemos elegir para qué colores. En este caso, todos:
	from_color = 0 hasta el color to_color=63
	'asyn' =0 o FALSE --> El programa se detiene hasta que termine el fade-in
	'asyn' =0 o TRUE --> El programa continua mientras se hace el fade-in
	*/
	//Probar a cambiar TRUE y FALSE
	PAL_fadeInAll(paleta64,120,TRUE);
	
	u16 i=240;
	while(BUTTONS[0]<10 && i>0){
		i-=3;vectorB[0]=i;vectorB[1]=-i;
		for(num_lin=9;num_lin<120;num_lin+=2) VDP_setHorizontalScrollLine(BG_A,num_lin,vectorB,2,CPU);
		SYS_doVBlankProcess();
	}
	
	vectorB[0]=0;vectorB[1]=0;
	for(num_lin=9;num_lin<120;num_lin+=2) VDP_setHorizontalScrollLine(BG_A,num_lin,vectorB,2,CPU);
	if(BUTTONS[0]>9){
		PAL_interruptFade();
		VDP_setPaletteColors(0,&paleta64[0],64); //paleta en negro, PAL2
	}
	VDP_setPaletteColors(32,(u16*)palette_black,16); //paleta en negro, PAL2
	//carga la imagen en VRAM y la dibuja en pantalla
	VDP_drawImageEx(BG_B,&titush,TILE_ATTR_FULL(PAL2,FALSE,FALSE,FALSE,ind),3,0,FALSE,TRUE);//
	//incrementa ind para 'apuntar' a una zona de VRAM libre para futuras tiles
	ind+=titulo.tileset->numTile;
	
	VDP_drawImageEx(BG_A,&sgdk,TILE_ATTR_FULL(PAL2,FALSE,FALSE,FALSE,ind),31,24,FALSE,TRUE);//
	//incrementa ind para 'apuntar' a una zona de VRAM libre para futuras tiles
	//ind+=sgdk.tileset->numTile;
	
	VDP_setTextPalette(PAL2);
	VDP_drawText("Power By",31,23);
	VDP_drawText(Version,36,0);
	
	VDP_setTextPalette(PAL3);VDP_drawText("AliceSim1",9,22);VDP_setTextPalette(PAL0);VDP_drawText("- 2019-2021",19,22);
	VDP_drawText("Twitter:  @Alice_Sim1",9,24);
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
				VDP_setTextPalette(PAL0);VDP_drawText("PULSA BOTON",11,18);
				VDP_setTextPalette(PAL3);VDP_drawText("START!",23,18);
			}
			else VDP_clearText(11,18,18);
			gat=!gat;
		}
		
		if (gat3){ gat3=FALSE;
			vectorB[0]=0;
			VDP_setHorizontalScrollLine(BG_A,num_lin,vectorB,1,CPU);
		}
		
		contador2--;
		if(contador2==0){ contador2=randomInRangeU8(1,25);
			vectorB[0]=randomInRangeU8(0,10)-5;
			num_lin=randomInRangeU8(10,112);
			VDP_setHorizontalScrollLine(BG_A,num_lin,vectorB,1,CPU);
			gat3=TRUE;
		}
		
		
		if(BUTTONS[8] && !gatS) ok=TRUE;
		else if(gatS && !BUTTONS[8]) gatS=FALSE;
		
		//VDP_showFPS(TRUE);//1x1
		//VDP_showCPULoad();//1x2
		SYS_doVBlankProcess(); // Renderizamos la pantalla
	}while(!ok);
	
	PAL_fadeOutAll(120,FALSE);
	XGM_stopPlay();
	SYS_disableInts();
	
	VDP_clearPlane(BG_A,TRUE);VDP_clearPlane(BG_B,TRUE);
	
	VDP_setTextPalette(PAL0);
}


//https://github.com/diegomtassis/yamd-library/blob/master/src/fwk/commons.c#L40
u8 randomInRangeU8(u8 lower, u8 higher) {
	return lower + random() % (higher + 1 - lower);
}

void VDP_drawInt(s32 valor,u8 ceros,u8 x, u8 y){
	intToStr(valor,char_salida,ceros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawText(char_salida,x,y);
}


/**
 * Manejador de entrada
 * joy-> Indica el mando que ha activado la entrada
 * state -> Indica el estado del mando (boton activo)
 * changed -> indica si ha cambiado (pulsado o solatado)
 * */
void inputHandler(u16 joy, u16 state, u16 changed){
    BUTTONS[0]=changed;
	
	BUTTONS[1]=changed & BUTTON_UP;
	BUTTONS[2]=changed & BUTTON_DOWN;
	BUTTONS[3]=changed & BUTTON_LEFT;
	BUTTONS[4]=changed & BUTTON_RIGHT;
	
	BUTTONS[5]=changed & BUTTON_A;
	BUTTONS[6]=changed & BUTTON_B;
	BUTTONS[7]=changed & BUTTON_C;
	BUTTONS[8]=changed & BUTTON_START;
	
}

