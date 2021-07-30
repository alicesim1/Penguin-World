#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"



void dialogo(u16 x,u16 y,u8 ancho, u8 alto){
	
	u8 i;
	//--------Marco Esquinas---------------------------------------------------------
	Sprite* dig_marcoE[4];
	dig_marcoE[0]=SPR_addSpriteEx(&dig_marco1,x,y,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
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
		dig_marcoH [i]=SPR_addSpriteEx(&dig_marco2,x2,y ,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
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
		dig_marcoV [i]=SPR_addSpriteEx(&dig_marco3,x ,y2,TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		dig_marcoVd[i]=SPR_addSpriteEx(&dig_marco3,x2,y2,TILE_ATTR_FULL(2,TRUE,FALSE,TRUE ,diag_ind+1+4),0,SPR_FLAG_AUTO_SPRITE_ALLOC);
		SPR_setDepth(dig_marcoV[i],SPR_MIN_DEPTH+2);//-32766
		SPR_setDepth(dig_marcoVd[i],SPR_MIN_DEPTH+2);//-32766
	}
	
	//Lienzo 32x32---------------------------------------------------
	Sprite* dig_lienzo[ancho*alto];
	u8 spritelienzo3232=0;
	for(u8 v=0;v<alto;v++){
		for(u8 h=0;h<ancho;h++){
			dig_lienzo[spritelienzo3232]=SPR_addSpriteEx(&dig_marco4,x+8+(32*h),y+8+(32*v),TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,diag_ind+1+4+4+(16*spritelienzo3232)),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			SPR_setDepth(dig_lienzo[spritelienzo3232],SPR_MIN_DEPTH+2);//-32766
			spritelienzo3232++;
		}
	}
	
	SPR_update();//SPR_FLAG_AUTO_TILE_UPLOAD FUNCIONE! Deve estar VISIBLE! Volvado automatico de tileset de los sprites a la VRAM
	
	SYS_doVBlankProcess();
	
	//Insertar Caracteres 8x16 en el lienzo VRAM
	
	// unpack first
	TileSet *t = unpackTileSet(&font16, NULL);//descomprimimos TilSet
	//KLog_U1("t->numTile:",t->numTile);//numTile:384
	
	u16 Start_ind=diag_ind+1+4+4;
	//u16 top_ind=Start_ind+(16*spritelienzo3232);
	u16 ind=Start_ind;
	u16 copy_ind;
	
	u8 cancho=0;
	u8 tcancho=ancho*4;// 1 ancho = 4 tiles
	
	u8 dig_fila=0;
	bool subfila=FALSE;
	
	u8 c=0;
	
	//KLog_U4("ancho:",ancho,"-tcancho:",tcancho,">ind:",Start_ind," -top_ind:",top_ind);
	bool skip=FALSE;
	
	do{
		
		
		//KLog_U1(">ind:",ind);
		if(c>0){//0=Espacio,1=!,2=...
			//Tails8521
			//----No se puede comprimir----Dirección del búfer de origen., Dirección de destino VRAM / CRAM / VSRAM.
			//DMA_queueDma(DMA_VRAM, (void *)yourtileset.tiles + yourtileindexinthetileset * 32, yourvramtileindex * 32, 16, 2);
			DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles+c *32,ind*32,16,2);ind++;//0>1    (2>3)
			//ancho> 128/8= 16 tiles | situamos el origen segunda fila de tiles 8x8, parte inferior de chara 8x16
			DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles+(c+16)*32,ind*32,16,2);ind++;//1>2... (3>4...)
			
		}else ind+=2;
		
		cancho++;
		//KLog_U2("cancho:",cancho,"==tcancho:",tcancho);
		if(cancho==tcancho){ cancho=0;
			
			if(subfila){ subfila=FALSE; //posicion inferior > superior (2-3 > 0-1) + siguiente		
				dig_fila++;//pasamos a la siguiente fila (siguiente fila de Sprites)
				copy_ind=ind;//copiamos la ultima posicion del indice, para continuar en la siguiente fila dig_fila>0
				
			}else{ subfila=TRUE; //posicion superior > inferior (0-1 > 2-3)	
				if(dig_fila>0) ind=copy_ind;//restauramos la posicion inicial
				else ind=Start_ind;//nos posicioamos al inicio
				ind+=2;
				//nos situamos en el indie equivalente y16-32
			}
			
			if(skip) SYS_doVBlankProcess();
			
			//KLog_U2("subfila:",subfila,">dig_fila:",dig_fila);
		} else ind+=2;//saltamos la segunda fila de texto VRAM
		
		
		c++;if((c&15)==0) c+=16;//necesario para saltar a la siguiente linea tabla ASCII
		
		if(!skip){
			for(i=0;i<3;i++){
				if(!gat){
					if(BUTTONS[6]) { skip=TRUE; break;}//salimos del FOR
				}
				else if(!BUTTONS[6]) gat=FALSE;
				
				SYS_doVBlankProcess();
			}
		}
		//JOY_waitPressTime(JOY_ALL,BUTTON_B,1000);
	} while(dig_fila<alto);
	
	//liberamos el TileSet de la fuente 8x16 de la RAM
	MEM_free(t);
	
	
	gat=TRUE;
	do{
		
		if(CursorON){
			_JOYupdateMouse();
			SPR_update();
		}
		
		if(gat && !BUTTONS[6]) gat=FALSE;
		SYS_doVBlankProcess();
	}while(!BUTTONS[6] || gat);	gat=TRUE;
	
	for(i=0;i<4;i++)	SPR_releaseSprite(dig_marcoE[i]);
	
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoH[i]);
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoHd[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoV[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoVd[i]);
	
	for(i=0;i<spritelienzo3232;i++)	SPR_releaseSprite(dig_lienzo[i]);

}
