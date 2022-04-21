#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <math.h>

const float FPS = 20;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;

const int NAVE_W = 100;
const int NAVE_H = 50;
const int MAX_INI = 10;

int TIRO_SAIU, ONLINE, COLI1, COLI2, SCORE, EV, VEL;
ALLEGRO_COLOR COR_CENARIO, COR_SCORE;

typedef struct Nave{
	int x,y;
	int vel;
	int dir_x,dir_y;
	ALLEGRO_COLOR cor;
}Nave;

typedef struct Bloco{
	
	int x, y;
	ALLEGRO_COLOR cor;
	int w, h;
	
}Bloco;

typedef struct Tiro{
	
	int x,y,vel;
	float r,velr;
	ALLEGRO_COLOR cor;
	int dir_x,dir_r;
	
}Tiro;

typedef struct Inimigo{
	
	int x, y, vel, r;
	ALLEGRO_COLOR cor;
	//int dir_x;
	
}Inimigo;

/*float distancia(Inimigo i1, Inimigo i2){
	return sqrt(pow(i1.x-i2.x,2)+pow(i1.y-i2.y,2));
}
*/
void initGlobais(){
	COR_CENARIO = al_map_rgb(rand()%64,rand()%64,rand()%64);
	COR_SCORE = al_map_rgb(64+rand()%64,64+rand()%64,64+rand()%64);
	TIRO_SAIU = 0;
	ONLINE = 0;
	SCORE = 0;
	EV=0;
	VEL=0;
}

void initNave(Nave *nave){
	nave->x = 10 + NAVE_W;
	nave->y = SCREEN_H/2;
	nave->vel = 4;
	nave->dir_x = 0;
	nave->dir_y = 0;
	nave->cor = al_map_rgb(180+rand()%64,180+rand()%64,180+rand()%64);
}
 
void initBloco(Bloco *bloco){
	
	bloco->x = SCREEN_W + rand()%(SCREEN_W);
	bloco->y = rand()%(4*SCREEN_H/5);
	bloco->w = SCREEN_W + rand()%(SCREEN_W);
	bloco->h = SCREEN_H/5 + rand()%(2*SCREEN_H/5);
	bloco->cor = al_map_rgb(rand(),rand(),rand());
	
}

void initTiro(Tiro *tiro){
	
	tiro->x = 10 + NAVE_W;
	tiro->y = SCREEN_H/2;
	tiro->r = 2;
	tiro->velr = 0.25;
	tiro->vel = 8;
	tiro->cor = al_map_rgb(208,0,0);
	tiro->dir_x = 0;
	tiro->dir_r = 0;
}

void initInimigo(Inimigo *inimigo){
	
	inimigo->r = 7+rand()%65;
	inimigo->x = SCREEN_W + rand()%(SCREEN_W-inimigo->r) + inimigo->r;
	inimigo->y = rand()%(SCREEN_H-inimigo->r) + inimigo->r;
	inimigo->vel = 1+rand()%8;
	inimigo->cor = al_map_rgb(72+rand()%64,72+rand()%64,72+rand()%64);
	
}

void desenhaCenario(){
	al_clear_to_color(COR_CENARIO);
}

void desenhaNave(Nave nave){
	
	al_draw_filled_triangle(nave.x,nave.y, nave.x - NAVE_W, nave.y - NAVE_H/2,nave.x - NAVE_W, nave.y + NAVE_H/2, nave.cor);
}

void desenhaBloco(Bloco bloco){
	
	al_draw_filled_rectangle(bloco.x,bloco.y,bloco.x + bloco.w, bloco.y + bloco.h, bloco.cor);
	
}

void desenhaTiro(Tiro tiro){
	 
	al_draw_filled_circle(tiro.x, tiro.y, tiro.r, tiro.cor);
	
}

void desenhaInimigo(Inimigo inimigo[], int n){
	
	int i;
	for(i = 0; i<n ; i++){
		al_draw_filled_circle(inimigo[i].x, inimigo[i].y, inimigo[i].r, inimigo[i].cor);
		//printf("\ndesenhou%d", i);
	}
	//printf("desenhou");
}

void desenhaScore(ALLEGRO_FONT *font){
	al_draw_textf( font ,COR_SCORE , 50 , 50 , 0, "Score: %d", SCORE);
}



void atualizaNave(Nave *nave){
	if(((nave->y + (nave->dir_y * nave->vel) + NAVE_H/2)<SCREEN_H)&&(nave->y + (nave->dir_y * nave->vel) - NAVE_H/2)>0){
	nave->y += nave->dir_y * nave->vel;
	}
	if(((nave->x + (nave->dir_x * nave->vel) - NAVE_W)>0) && (nave->x + (nave->dir_x * nave->vel) <SCREEN_W)){
		nave->x += nave->dir_x * nave->vel;
	}
}

void atualizaBloco(Bloco *bloco){
	
	bloco->x -= 1;
	
	if(bloco->x + bloco->w <0)
		initBloco(bloco);
}

void atualizaTiro(Tiro *tiro, Nave nave){
	//int espaco=0; //saiu;
	if(TIRO_SAIU == 0){
		tiro->y = nave.y;
		tiro->x = nave.x;
	}else {
		tiro->x += tiro->vel;
		if(tiro->x > SCREEN_W){
			TIRO_SAIU = 0;
			initTiro(tiro);
		}
	}
	if((tiro->r < 15) && (tiro->dir_r == 1) &&(TIRO_SAIU==0)){
		if( VEL == 1){
			tiro->r += (tiro->dir_r)*((tiro->velr)*4);
		}else tiro->r += (tiro->dir_r)*(tiro->velr);
		
	}
	
	//printf("rai %f", tiro->r);
	
}

void atualizaInimigo(Inimigo *inimigo, Inimigo in[], int i){
	
	ONLINE=1;
	inimigo->x -= inimigo->vel;
	if(inimigo->x <= 0){
		initInimigo(inimigo);
	}
	if(colisaoInimigos(in,i)){
		initInimigo(inimigo);
	}
	
	//printf("%d", inimigo->x);
	
}

int colisaoNaveBloco(Nave nave, Bloco bloco){
	if( ((nave.x >= bloco.x) && (nave.y+NAVE_H/2>=bloco.y) && (nave.x<=bloco.x + bloco.w) && (nave.y - NAVE_H/2 <= bloco.y + bloco.h)) || ((nave.x-NAVE_W <= bloco.x + bloco.w ) && (nave.y+NAVE_H/2>=bloco.y) && (nave.y - NAVE_H/2 <= bloco.y + bloco.h) && (nave.x-NAVE_W>=bloco.x)) ){
		return 1;
		//printf("colisao");
	}
	//printf("sem colisao");
	return 0;
}

void colisaoTiroBloco(Tiro *tiro, Bloco bloco){
	if( ((tiro->x >= bloco.x) && (tiro->y>=bloco.y) && (tiro->x<=bloco.x + bloco.w) && (tiro->y<=bloco.y+bloco.h)) ){
		//return 1;
		//printf("tiro");
		TIRO_SAIU = 0;
		initTiro(tiro);
	}
	//printf("sem colisao");
	//return 0;
}

int colisaoCirculos(Inimigo i1, Inimigo i2){
	float distancia;
	distancia = sqrt(pow(i1.x-i2.x,2)+pow(i1.y-i2.y,2));
	//printf("\npos 1 (%d,%d) pos 2 (%d,%d)distancia %f soma raio: %d", i1.x,i1.y,i2.x,i2.y, distancia, i1.r + i2.r);
	if (distancia< i1.r + i2.r){
		return 1;
	}
	return 0;
}

int colisaoCirculoTiroinimigo(Tiro tiro, Inimigo inimigo){
	float distancia;
	distancia = sqrt(pow(tiro.x-inimigo.x,2)+pow(tiro.y-inimigo.y,2));
	//printf("\npos 1 (%d,%d) pos 2 (%d,%d)distancia %f soma raio: %d", i1.x,i1.y,i2.x,i2.y, distancia, i1.r + i2.r);
	if (distancia< tiro.r + inimigo.r){
		return 1;
	}
	return 0;
}

int colisaoInimigos(Inimigo inimigo[]/*, Inimigo inimigo*/, int n){
	
	//int i;
	/*for(i = 0; i<n; i++){
		if(colisaoCirculos(inimigo, inimigo[i])){
			return 1;
		}
			
	}*/
	int ref = n;
	while(1){
		if(ref==0){
			return 0;
		}
		if(colisaoCirculos(inimigo[n],inimigo[ref-1])){
			//printf("\ncolidiu\n");
			if(ONLINE == 1){
				COLI1 = n;
				COLI2 = ref-1;
			}
			return 1;
		}
		//printf("travo");
		ref--;
	}
	//printf("entrou\n");
	return 0;
}

void colisaoBlocoInimigo(Inimigo *inimigo,Bloco bloco){
	
	if((inimigo->x + inimigo->r <= bloco.x + bloco.w) && (inimigo->y + inimigo->r >= bloco.y) && (inimigo->y - inimigo->r<= bloco.y +bloco.h)){
		initInimigo(inimigo);
	}
	
}

int colisaoTiroinimigo(Tiro *tiro, Inimigo inimigo[],int n){
	if(colisaoCirculoTiroinimigo(*tiro,inimigo[n])){
		//initInimigo(&inimigo[n]);
		//initTiro(tiro);
		if(inimigo[n].r >= 65){
			SCORE += 100;
		}else if(inimigo[n].r >= 32 ){
			SCORE += 50;
		}else if(inimigo[n].r >= 16){
			SCORE += 25;
		}else if(inimigo[n].r >= 8){
			SCORE += 5;
		}else SCORE += 2;
		return 1;
	}else return 0;
	
}

int colisaoNaveInimigo(Nave nave, Inimigo inimigo[]){
	int i;
	float d,d1, d2, d3, d4;
	for(i=0;i<MAX_INI;i++){
		d= sqrt(pow(nave.x-(inimigo[i].x+inimigo[i].r),2)+pow(nave.y-inimigo[i].y,2));
		d1= sqrt(pow((nave.x-NAVE_W/2)-(inimigo[i].x+inimigo[i].r),2)+pow((nave.y-NAVE_H/4)-inimigo[i].y,2));
		d2= sqrt(pow((nave.x-NAVE_W)-(inimigo[i].x+inimigo[i].r),2)+pow((nave.y-NAVE_H/2)-inimigo[i].y,2));
		d3=	sqrt(pow((nave.x-NAVE_W)-(inimigo[i].x+inimigo[i].r),2)+pow((nave.y+NAVE_H/2)-inimigo[i].y,2));
		d4= sqrt(pow((nave.x-NAVE_W/2)-(inimigo[i].x+inimigo[i].r),2)+pow((nave.y+NAVE_H/4)-inimigo[i].y,2));
		if( (d <= inimigo[i].r) || (d1 <= inimigo[i].r) || (d2 <= inimigo[i].r) || (d3 <= inimigo[i].r) || (d4 <= inimigo[i].r) ){
		//printf("\nperdeu\n");
		return 1;
		}
	}
		return 0;
}

int buscaRecord(){
    FILE *arq = fopen("records.txt", "r");
    //FILE *arq_risk= fopen("risks.txt","w");
    char linha[1000];
    int Sc=0,SMaior=0;
    while(!feof(arq)){
        fgets(linha,1000,arq);
        //printf("%s\n",linha);
        Sc=atoi(strtok(linha,"\n"));
		if(Sc>=SMaior){
			SMaior=Sc;
		}
        //printf("%d %d %d %f\n",ID,UR,PR,TMED);
    }
    
    fclose(arq);
	return SMaior;
}

void guardaRecord(){
    FILE *arq_rcd= fopen("records.txt","a");
	fprintf(arq_rcd,"%d\n", SCORE);
    fclose(arq_rcd);
}
  
int main(int argc, char **argv){
	
	srand(time(NULL));
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *font20 = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    font = al_load_font("arial.ttf", 32, 1);   
	font20 = al_load_font("arial.ttf", 20, 1);
	if(font == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}
	if(font20 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
   
	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	

	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
  	
	initGlobais();
	Nave nave;
	initNave(&nave);
	Bloco bloco;
	initBloco(&bloco);
	Tiro tiro;
	initTiro(&tiro);
	Inimigo inimigo[MAX_INI];
	int i=0;
	for(i = 0;i<MAX_INI;i++){
		initInimigo(&inimigo[i]);
		//printf("crio %d", i);
		//printf("inimigo %d (%d,%d)\n", i, inimigo[i].x,inimigo[i].y);
		if(colisaoInimigos(inimigo/*, inimigo*/, i)){
			i--;
		}
		
	}
	

	//inicia o temporizador
	al_start_timer(timer);
	
	int playing = 1;
	
	while(playing) 
	{
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			//limpa a tela
			desenhaCenario();
			atualizaBloco(&bloco);
			desenhaBloco(bloco);
			for(i=0;i<MAX_INI;i++){
				atualizaInimigo(&inimigo[i],inimigo,i);
				initInimigo(&inimigo[COLI1]);
				initInimigo(&inimigo[COLI2]);
				colisaoBlocoInimigo(&inimigo[i],bloco);
				//colisaoTiroinimigo(&tiro, inimigo,i);
				//atualizaTiro(&tiro,nave);
				//desenhaTiro(tiro);
			}
			desenhaInimigo(inimigo,MAX_INI);
			atualizaNave(&nave);
			desenhaNave(nave);
			atualizaTiro(&tiro,nave);
			desenhaTiro(tiro);
			desenhaScore(font20);
			if(TIRO_SAIU == 1){
				for(i=0;i<MAX_INI;i++){
					if(colisaoTiroinimigo(&tiro, inimigo,i)){
						
						initInimigo(&inimigo[i]);
						if(tiro.r <= 10){
							TIRO_SAIU=0;
							initTiro(&tiro);
							atualizaTiro(&tiro,nave);
						}
						break;
					}
				}
			}
			if(colisaoNaveBloco(nave,bloco) || colisaoNaveInimigo(nave,inimigo)){
				//paying = 1;
				int record = 0;
				record = buscaRecord();
				
				while(playing){
					//printf("travou");
					ALLEGRO_EVENT ev;
					al_wait_for_event(event_queue, &ev);
					if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
						playing = 0;
					}
					desenhaCenario();
					al_draw_textf(font, COR_SCORE , SCREEN_W/2 , SCREEN_H/2 , ALLEGRO_ALIGN_CENTRE, "Score: %d", SCORE);
					if(SCORE > record){
						al_draw_textf(font, COR_SCORE , SCREEN_W/2 , SCREEN_H/4 , ALLEGRO_ALIGN_CENTRE, "Novo record: %d", SCORE);
					}else al_draw_textf(font, COR_SCORE , SCREEN_W/2 , SCREEN_H/4 , ALLEGRO_ALIGN_CENTRE, "Record: %d", record);
					al_flip_display();
				}
				//printf("CABOUU");
			}
			//playing = !colisaoNaveBloco(nave,bloco);
			colisaoTiroBloco(&tiro,bloco);
				//if(!colisaoTiroBloco(tiro,bloco)){
			//	initTiro(&tiro);
			//}
			//aplica fisica
			//desenha
		
			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
		}

		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { 
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_W:
					nave.dir_y--;
				break;
				case ALLEGRO_KEY_S:
					nave.dir_y++;
				break;
				case ALLEGRO_KEY_A:
					nave.dir_x--;
				break;
				case ALLEGRO_KEY_D:
					nave.dir_x++;
					//printf("nave %d", nave.dir_x);
				break;
				case ALLEGRO_KEY_SPACE:
					
					tiro.dir_r++;
					//printf("espaco %d", tiro.dir_r);
				break;
				case ALLEGRO_KEY_M:
					EV=1;
					printf("espaco ");
				break;
			}
			//imprime qual tecla foi
			//printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_W:
					nave.dir_y++;
				break;
				case ALLEGRO_KEY_S:
					nave.dir_y--;
				break;
				case ALLEGRO_KEY_A:
					nave.dir_x++;
				break;
				case ALLEGRO_KEY_D:
					nave.dir_x--;
				break;
				case ALLEGRO_KEY_SPACE:
					tiro.dir_r--;
					TIRO_SAIU = 1;
					//printf("espaco ");
				break;
				case ALLEGRO_KEY_M:
					EV=0;
					nave.cor = al_map_rgb(190+rand()%64,190+rand()%64,190+rand()%64);
					VEL = 1;
					//printf("espaco ");
				break;
			}
		}

	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	guardaRecord();
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_font(font20);
   
 
	return 0;
}