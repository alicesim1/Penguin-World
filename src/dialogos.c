#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"


#define diag_ind 200 //hex:4B0




/*
void Dialogo_VRAM(){
	
	KLog_U1("numTile:",font16.numTile);//384
	
	u32 tile[8]=
	{
		0x00111100,
		0x01144110,
		0x11244211,
		0x11244211,
		0x11222211,
		0x11222211,
		0x01122110,
		0x00111100
	};
	
	for(u8 i=0;i<8;i++){
		tile[i]=font16.tiles[i];
		KLog_U1("tiles:",tile[i]);//296157552
	}
	
	VDP_loadTileData( (u32 *)tile, 199, 1, CPU);
	VDP_loadTileSet(&font16,600,CPU);
	*/



void dialogo(u16 x,u16 y,u8 ancho, u8 alto){
	
	PAL_setColors(32,dig_marco1.palette->data,8,CPU);
	u8 i;
	//--------Marco Esquinas---------------------------------------------------------
	Sprite* dig_marcoE[4];
	dig_marcoE[0]=SPR_addSpriteEx(&dig_marco1,x,y,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	dig_marcoE[1]=SPR_addSpriteEx(&dig_marco1,x+8+(32*ancho),y,TILE_ATTR_FULL(2,TRUE,FALSE,TRUE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	dig_marcoE[2]=SPR_addSpriteEx(&dig_marco1,x,y+8+(32*alto),TILE_ATTR_FULL(2,TRUE,TRUE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	dig_marcoE[3]=SPR_addSpriteEx(&dig_marco1,x+8+(32*ancho),y+8+(32*alto),TILE_ATTR_FULL(2,TRUE,TRUE,TRUE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
	for(i=0;i<4;i++) SPR_setDepth(dig_marcoE[i],SPR_MIN_DEPTH+2);//-32766
	
	
	//-------Marco horizontales----------------------
	Sprite* dig_marcoH[ancho];//superior
	Sprite* dig_marcoHd[ancho];//abajo
	u16 x2;
	u16 y2=y+8+(32*alto);
	for(i=0;i<ancho;i++){
		x2=x+8+(32*i);
		if(i==0) dig_marcoH[i]=SPR_addSpriteEx(&dig_marco2,x2,y ,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
		else dig_marcoH[i]=SPR_addSpriteEx(&dig_marco2,x2,y ,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		dig_marcoHd[i]=SPR_addSpriteEx(&dig_marco2,x2,y2,TILE_ATTR_FULL(2,TRUE,TRUE ,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		SPR_setDepth(dig_marcoH[i],SPR_MIN_DEPTH+2);//-32766	
		SPR_setDepth(dig_marcoHd[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	//-------Marco verticales-----------------------
	Sprite* dig_marcoV[alto];//izquierdaq
	Sprite* dig_marcoVd[alto];//derecho
	x2=x+8+(32*ancho);
	for(i=0;i<alto;i++){
		y2=y+8+(32*i);
		if(i==0) dig_marcoV[i]=SPR_addSpriteEx(&dig_marco3,x ,y2,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
		else dig_marcoV[i]=SPR_addSpriteEx(&dig_marco3,x ,y2,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		dig_marcoVd[i]=SPR_addSpriteEx(&dig_marco3,x2,y2,TILE_ATTR_FULL(2,TRUE,FALSE,TRUE ,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		SPR_setDepth(dig_marcoV[i],SPR_MIN_DEPTH+2);//-32766
		SPR_setDepth(dig_marcoVd[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	//Lienzo 32x32---------------------------------------------------
	Sprite* dig_lienzo[ancho*alto];
	u8 p=0;
	for(u8 v=0;v<alto;v++){
		for(u8 h=0;h<ancho;h++){
			dig_lienzo[p]=SPR_addSpriteEx(&dig_marco4,x+8+(32*h),y+8+(32*v),TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4+4+(16*p)),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			SPR_setDepth(dig_lienzo[p],SPR_MIN_DEPTH+2);//-32766
			p++;
			//--------------------------------------------------------------------
		}
	}
	
	SPR_update();//SPR_FLAG_AUTO_TILE_UPLOAD FUNCIONE! Deve estar VISIBLE! Volvado automatico de tileset de los sprites a la VRAM
	
	VDP_drawInt(SYS_getCPULoad(),2,38,ScreenY);
	SYS_doVBlankProcess();
	
	//Insertar Caracteres 8x16 en el lienzo VRAM
	
	u16 ind=diag_ind+1+4+4;
	u16 top_ind=ind+(16*p);
	KLog_U2(">ind:",ind," -top_ind:",top_ind);
	//Message : >ind:209 -top_ind:337
	u8 c=0;
	u8 c2;
	do{
		
		//Message : c:0>ind:209 -c2:16
		//Message : c:1>ind:213 -c2:17
		//Message : c:30>ind:329 -c2:46
		//Message : c:31>ind:333 -c2:47
		
		c2=c+16;//ancho> 128/8= 16 tiles | situamos el origen segunda fila de tiles 8x8, parte inferior de chara 8x16
		
		KLog_U3("c:",c,">ind:",ind," -c2:",c2);
		
		//----No se puede comprimir----Dirección del búfer de origen., Dirección de destino VRAM / CRAM / VSRAM.
		DMA_queueDma(DMA_VRAM,(void *)font16.tiles+c *32,ind*32,16,2);ind++;
		DMA_queueDma(DMA_VRAM,(void *)font16.tiles+c2*32,ind*32,16,2);
		ind+=3;//saltamos la segunda fila de texto VRAM
		
		c++;if((c&15)==0) c+=16;
		
		//VDP_drawInt(SYS_getCPULoad(),2,38,ScreenY);
		SYS_doVBlankProcess();
		JOY_waitPressTime(JOY_ALL,BUTTON_B,1000);
	} while(ind<top_ind);
	//DMA_queueDma(DMA_VRAM, (void *)yourtileset.tiles + yourtileindexinthetileset * 32, yourvramtileindex * 32, 16, 2);
	
	
	do{
		if(gat && !BUTTONS[6]) gat=FALSE;
		if(CursorON){
			_JOYupdateMouse();
			SPR_update();
		}
		//VDP_drawInt(SYS_getCPULoad(),2,38,ScreenY);
		SYS_doVBlankProcess();
	}while(!BUTTONS[6] || gat);	gat=TRUE;
	
	for(i=0;i<4;i++)	SPR_releaseSprite(dig_marcoE[i]);
	
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoH[i]);
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoHd[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoV[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoVd[i]);
	
	for(i=0;i<p;i++)	SPR_releaseSprite(dig_lienzo[i]);

}
