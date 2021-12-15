#include "genesis.h"//[[SGDK]]
/********************************************************************************
*      @Title:  PENGUIN WORLD
*      @Author: Alicia Sanchez Martos "AliceSim1"
***********************************************************************************/
#include "../inc/global.h"

/*
  ASCI: 33 = " (comillas)  usar: \"
  ASCI: 92 = \ (CUIDADO! escape seuence)  usar siempre: \\
*/

#define topdialogo 128//0-127=X  128=\0
//---------------------|XXXXXXXXXXXXXXXXXXXXXXXXX0|---------
const char dialogo0[]={"El veloz murciélago hindú comía feliz cardillo y kiwi. La cigüeña tocaba el saxofón detrás del palenque de paja."};
const char dialogo1[]={" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "};


const char dialogo2[]={"¡¿ÁÉÍÑÓÚÜáéíñóúü"};//ASCII Extendido
const char dialogo3[]={" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ¡¿ÁÉÍÑÓÚÜáéíñóúü"};

const u8 ascii_SP[]={129,159,161,169,173,177,179,186,188,193,201,205,209,211,218,220};
/*Message : ¡
Message : letra: 14 >ASCI: 161 >c: 129
Message : ¿
Message : letra: 15 >ASCI: 191 >c: 159
Message : Á
Message : letra: 0 >ASCI: 193 >c: 161
Message : É
Message : letra: 1 >ASCI: 201 >c: 169
Message : Í
Message : letra: 2 >ASCI: 205 >c: 173
Message : Ñ
Message : letra: 5 >ASCI: 209 >c: 177
Message : Ó
Message : letra: 3 >ASCI: 211 >c: 179
Message : Ú
Message : letra: 4 >ASCI: 218 >c: 186
Message : Ü
Message : letra: 6 >ASCI: 220 >c: 188
Message : á
Message : letra: 7 >ASCI: 225 >c: 193
Message : é
Message : letra: 8 >ASCI: 233 >c: 201
Message : í
Message : letra: 9 >ASCI: 237 >c: 205
Message : ñ
Message : letra: 12 >ASCI: 241 >c: 209
Message : ó
Message : letra: 10 >ASCI: 243 >c: 211
Message : ú
Message : letra: 11 >ASCI: 250 >c: 218
Message : ü
Message : letra: 13 >ASCI: 252 >c: 220
*/

static u8 ASCII_EXT(u8 charasci){
	u8 i=0;
	while(ascii_SP[i]!=charasci){
		i++;
	}
	return 96+i;
}


const char* dialogos[] = {dialogo0,dialogo1,dialogo2,dialogo3};

void dialogo(u16 x,u16 y,u8 ancho, u8 alto, u8 numdiag){
	
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
	SPR_update();SYS_doVBlankProcess();
	
	//Lienzo 32x32---------------------------------------------------

	u16 Start_ind=diag_ind+1+4+4;
	
	u8 aa=ancho*alto;
	KLog_U3("ancho: ",ancho,"*alto: ",alto," >",aa);
	Sprite* dig_lienzo[aa];
	
	u8 spritelienzo3232=0;
	for(u8 v=0;v<alto;v++){
		for(u8 h=0;h<ancho;h++){
			dig_lienzo[spritelienzo3232]=SPR_addSpriteEx(&dig_marco4,x+8+(32*h),y+8+(32*v),TILE_ATTR_FULL(2,TRUE,FALSE,FALSE,Start_ind+(16*spritelienzo3232)),0,SPR_FLAG_AUTO_SPRITE_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);		
			if((spritelienzo3232&10)==10){ //necesario para no llenar el DMA
				SPR_update();SYS_doVBlankProcess();
			}
			SPR_setDepth(dig_lienzo[spritelienzo3232],SPR_MIN_DEPTH+2);//-32766
			spritelienzo3232++;
		}
	}
	
	SPR_update();//SPR_FLAG_AUTO_TILE_UPLOAD FUNCIONE! Deve estar VISIBLE! Volvado automatico de tileset de los sprites a la VRAM
	SYS_doVBlankProcess();
	
	//Insertar Caracteres 8x16 en el lienzo VRAM
	
	//descomprimimos TilSet
	TileSet *t = unpackTileSet(&font16, NULL);
	//KLog_U1("t->numTile: ",t->numTile);//numTile:384
	
	
	//u16 top_ind=Start_ind+(16*spritelienzo3232);
	u16 ind=Start_ind;
	u16 copy_ind=0;
	
	u8 cancho=0;
	u8 tcancho=ancho*4;// 1 ancho = 4 tiles
	
	u8 dig_fila=0;
	bool subfila=FALSE;
	
	char cadena_org[topdialogo];//tipo cadena completa ""(se auto añade al final \0)
	char cadena_temp[1];//[0] caracter, [1]=\0
	
	u16 c;//valor indice de Tileset de la tabla ASCII grafico! 8x16
	u8 rc,ct;//valor caracter ASCII 0(32)=" "
	
	/*for(rc=32;rc<256;rc++){
		cadena_temp[0]=rc;cadena_temp[1]='\0';
		KLog_U1(cadena_temp,rc);
	}*/
	
	u8 dig_long=strlen(dialogos[numdiag]);
	//VDP_drawInt(dig_long,0,35,ScreenY);
	
	strcpy(cadena_org,dialogos[numdiag]);//VDP_drawText(cadena_org,0,ScreenY);
	
	KLog(cadena_org);
	
	u8 letra=0;//numero de posicion de caracteres de la frase
	u8 vel_letra=6;
	//KLog_U4("ancho:",ancho,"-tcancho:",tcancho,">ind:",Start_ind," -top_ind:",top_ind);
	bool skip=FALSE;
	
	do{
		
		cadena_temp[0]=cadena_org[letra];cadena_temp[1]='\0';// [0] = H > ASCII:72
		
		KLog(cadena_temp);
		
		rc=cadena_temp[0];//32-255
		c=rc-32;//32>0 ASCII valor
		
		if(c>128){ c=ASCII_EXT(c); }
		
		
		KLog_U3("letra: ",letra," >ASCI: ",rc," >c: ",c);
		
		
		//KLog_U1(">ind:",ind);
		if(c>0){//0=Espacio,1=!,2=...
			
			if(c>15){//calcular +16 X cada > 16 caracteres ASCII
				ct=c/16;
				ct=16*ct;//necesario para saltar a la siguiente linea tabla ASCII
				c+=ct;
				KLog_U2("/16> ",ct," *16= ",c);
			}
			//Tails8521
			//----No se puede comprimir----Dirección del búfer de origen., Dirección de destino VRAM / CRAM / VSRAM.
			//DMA_queueDma(DMA_VRAM, (void *)yourtileset.tiles + yourtileindexinthetileset * 32, yourvramtileindex * 32, 16, 2);
			DMA_queueDmaFast(DMA_VRAM,(void *)t->tiles+ c    *32,ind*32,16,2);ind++;//0>1    (2>3)
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
		
		
		letra++;
		
		if(!skip){
			if(vel_letra>0){
				for(i=0;i<vel_letra;i++){
					if(!gat){
						if(BUTTONS[6]) { skip=TRUE; break;}//salimos del FOR
					}
					else if(!BUTTONS[6]) gat=FALSE;
					
					SYS_doVBlankProcess();
				}
			}
		}
		//JOY_waitPressTime(JOY_ALL,BUTTON_B,1000);
	} while(dig_fila<alto && letra<dig_long);
	
	//liberamos el TileSet de la fuente 8x16 ASCII de la RAM
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
	
	for(i=0;i<spritelienzo3232;i++)	SPR_releaseSprite(dig_lienzo[i]);
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoH[i]);
	for(i=0;i<ancho;i++)SPR_releaseSprite(dig_marcoHd[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoV[i]);
	for(i=0;i<alto;i++) SPR_releaseSprite(dig_marcoVd[i]);
	for(i=0;i<4;i++)	SPR_releaseSprite(dig_marcoE[i]);
	
}
