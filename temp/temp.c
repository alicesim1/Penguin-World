

u8 top_object2D 3
struct t_object2D {
	Sprite* sprt;
	u16 x, y;
};
struct t_object2D object2D[top_object2D];
//------------------------------------------------------------------------------------------
static void object2D_maker(SpriteDefinition sprited,u8 , u8, u16 , u16 , bool , bool );


//static void SPR_PRIORITY(){
//-----------------------------------------------------------
	for(u8 i=0;i<3;i++){
		SPR_setPosition(object2D[i].sprt,object2D[i].x-posX,object2D[i].y-posY);
	}
	SPR_setDepth(penguinsp,-posY); 
	


    //loadzona(){
	//-------------------------------------------
	for(u8 i=1;i<4;i++){
		object2D_maker(penguin,i-1,i,32*(i+2),32*(i+2),0,randU8(0,1));
	}
	//--------------------------------------------
	

	//ZoneMap() unloadmap
		for(u8 i=0; i<4; i++){
			SPR_releaseSprite(object2D[i].sprt); //advertencia compilador!!
		}
		
		SPR_releaseSprite(object2D[0].sprt);
		SPR_releaseSprite(object2D[1].sprt);
		SPR_releaseSprite(object2D[2].sprt);
		SPR_releaseSprite(object2D[3].sprt);
		


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


	switch(jugcontrol){
		
		//BUTTONS[1]=changed & BUTTON_UP;
		//BUTTONS[2]=changed & BUTTON_DOWN;
		//BUTTONS[3]=changed & BUTTON_LEFT;
		//BUTTONS[4]=changed & BUTTON_RIGHT;
		
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
		
		
			}break;
		}
	
	
	
	if(BUTTONS[8]){ gat=TRUE;
		
		jugcontrol++; if(jugcontrol==4) jugcontrol=0;
		
		JOY_reset();
		padtipo=JOY_getPortType(PORT_1);//13 = 
		//padtipo=15;//NINGUNO
		//padtipo=13;//PAD3,6
		//padtipo=0;//MOUSE
		
		padraton=JOY_getPortType(PORT_2);
		if(padraton==PORT_TYPE_MOUSE) JOY_setSupport(PORT_2, JOY_SUPPORT_MOUSE); //3
		//padraton=15;//NINGUNO
		//padraton=13;//PAD3,6
		//padraton=3;//MOUSE
		VDP_drawInt(padtipo,2,0,ScreenMY-2);
		VDP_drawInt(padraton,2,20,ScreenMY-2);
		
		SYS_doVBlankProcess(); // Renderizamos la pantalla
		
		pad6=JOY_getJoypadType(JOY_1);
		//0=3 botones
		//1=6 botones
		//15=NINGUNO

		VDP_drawInt(pad6,0,10,ScreenY-2);
		//VDP_drawInt(padmouse,2,30,ScreenY-2);
	}


static void dialogo(u8 ancho,u8 alto){
	
	u16 tilenum=MAP_getTile(bga,48,26) & TILE_INDEX_MASK;
	
	KLog_U1("tilenum:",tilenum);
	
	VDP_fillTileMapRect(BG_A,TILE_ATTR_FULL(0,TRUE,FALSE,FALSE,1531),48,26,ancho,alto);
	
	SPR_update();
	do{
		SYS_doVBlankProcess();
	}while(!BUTTONS[6]);
	
	KLog_U2("posX:",bga->posX,"posY:",bga->posY);
	KLog_U2("posX:",posX,"posY:",posY);
	
	//bga->planeWidthMask=0; // force full map update using row updates
	bga->lastXT = 0;bga->lastYT = 0;
	bga->posX = 0;	bga->posY = 0;
	MAP_scrollTo(bga,posX,posY);
	
}

/*
ts 0x7FF, 
If you find it easier you can also write it directly in binary, like so: 
0b11111111111 (eleven ones, to mask bits 0 to 10),
 I wish C would support underscores in numbers to make it easier to read tho.
*/

	//KLog_U1("ScreenY:",ScreenY);
	//KLog_S1("fixAlturaY:",fixAlturaY);
	ScreenTY=8+(ScreenY*8);//224/240
	ScreenMY=ScreenTY/2;//112/120
	
	//KLog_U1("ScreenTY:",ScreenTY);
	//KLog_U1("ScreenMY:",ScreenMY);
	//--------------------------------------
	//KLog("---------------");
	
	padtipo=JOY_getPortType(PORT_1);//13 = 
	//padtipo=15;//NINGUNO
	//padtipo=13;//PAD3,6
	//padtipo=0;//MOUSE

	padraton=JOY_getPortType(PORT_2);
	if(padraton==PORT_TYPE_MOUSE) JOY_setSupport(PORT_2, JOY_SUPPORT_MOUSE); //3
	//padraton=15;//NINGUNO
	//padraton=13;//PAD3,6
	//padraton=3;//MOUSE
	
	SYS_doVBlankProcess(); // Renderizamos la pantalla
	
	pad6=JOY_getJoypadType(JOY_1);
	//0=3 botones
	//1=6 botones
	//15=NINGUNO
	
	JOY_setEventHandler(&inputHandler);
	
	
void play_music(u8 indice){
	switch(indice){
		case 1:XGM_startPlay(M_titulo);break;
		case 2:XGM_startPlay(M_zone1);break;
		default: XGM_stopPlay();
	}
}


