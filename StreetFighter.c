#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "player.h"
#include "keyboard.h"

#define NUM_PERSONAGENS 4
#define NUM_ESTADOS 6
#define NUM_SPRITES 4

#define DIREITA 0
#define ESQUERDA 1

ALLEGRO_BITMAP *sprites[NUM_PERSONAGENS][NUM_ESTADOS][NUM_SPRITES];

void desenha_bitmap_centralizado(ALLEGRO_BITMAP *bitmap, int x, int y, unsigned char face){
	x = x - al_get_bitmap_width(bitmap)/2;
	y = y - al_get_bitmap_height(bitmap)/2;
	al_draw_bitmap(bitmap, x, y, face);
}

void carrega_sprites(){
    const char *personagens[] = {"ryu", "ken", "chun-li", "bison"};
    const char *estados[] = {"abaixado", "andando", "em_pe", "pulando", "ataque_superior", "ataque_inferior"};

    for (int i = 0; i < NUM_PERSONAGENS; i++) {
        for (int j = 0; j < NUM_ESTADOS; j++) {
            for (int k = 0; k < NUM_SPRITES; k++) {
                char caminho[100];
                snprintf(caminho, sizeof(caminho), "./images/sprites/%s/%s/%d.png", personagens[i], estados[j], k + 1);
                sprites[i][j][k] = al_load_bitmap(caminho);
        	}
    	}
	}
}

void desaloca_sprites(){
	for (int i=0; i<NUM_PERSONAGENS; i++)
		for (int j=0; j<NUM_ESTADOS; j++)
			for (int k=0; k<NUM_SPRITES; k++)
				al_destroy_bitmap(sprites[i][j][k]);
		
}

// retorna -1 caso o jogo seja fechado, 1 caso o p1 ganhe e 2 caso o p2 ganhe
int fight(ALLEGRO_EVENT_QUEUE* queue, int game_mode, int background_choice, int character1, int character2, int wins1, int wins2){
	ALLEGRO_EVENT event;

	bool keys[ALLEGRO_KEY_MAX];
	for (int i=0; i<ALLEGRO_KEY_MAX; i++) keys[i] = 0;

	int pause;
	int sprite1_frame_counter = 0;
	int sprite2_frame_counter = 0;
	int ultimo_estado1 = EM_PE;
	int ultimo_estado2 = EM_PE;

	// inicializa o player1 e o player2
	player *p1 = player_create(210, 340, DIREITA, 500, 750, character1);
	player *p2 = player_create(210, 340, ESQUERDA, 1450, 750, character2);

	ALLEGRO_FONT *font = al_load_ttf_font("./images/arcade_font.ttf", 32, 0);
	if (!font) return -1;

	// seleciona o background escolhido
	ALLEGRO_BITMAP* background;
	if (background_choice == 0) background = al_load_bitmap("./images/backgrounds/background1.jpg");
	else if (background_choice == 1) background = al_load_bitmap("./images/backgrounds/background2.jpg");
	else if (background_choice == 2) background = al_load_bitmap("./images/backgrounds/background3.jpg");


	// laco principal do jogo
	while (1){
		al_wait_for_event(queue, &event);

		// evento de relogio
		if (event.type == 30){
			atualiza_estados(p1);
			atualiza_estados(p2);

			if (escolhe_acao(p1, p2)){
				al_destroy_bitmap(background);
				free(p1);
				free(p2);
				al_destroy_font(font);
				return 1;
			}
			if (escolhe_acao(p2, p1)){
				al_destroy_bitmap(background);
				free(p1);
				free(p2);
				al_destroy_font(font);
				return 2;
			}

			if (p1->x <= p2->x){
				p1->face = DIREITA;
				p2->face = ESQUERDA;
			}else{
				p1->face = ESQUERDA;
				p2->face = DIREITA;
			}

			if (ultimo_estado1 != p1->estado){
				sprite1_frame_counter = 0;
				p1->sprite = 0;
			}
			if (ultimo_estado2 != p2->estado){
				sprite2_frame_counter = 0;
				p2->sprite = 0;
			}

			// atualiza os sprites para gerar animação
			if (sprite1_frame_counter == 6){
				sprite1_frame_counter = 0;
				p1->sprite = (p1->sprite + 1) % 4;
			}
			sprite1_frame_counter++;
			if (sprite2_frame_counter == 6){
				sprite2_frame_counter = 0;
				p2->sprite = (p2->sprite + 1) % 4;
			}
			sprite2_frame_counter++;

			ultimo_estado1 = p1->estado;
			ultimo_estado2 = p2->estado;

			// desenha o background
			al_draw_bitmap(background, 0, 0, 0);

			//desenha a barra preta de vida
			al_draw_filled_rectangle(200, 50, 700, 100, al_map_rgb(20, 20, 20));
        	al_draw_filled_rectangle(1220, 50, 1720, 100, al_map_rgb(20, 20, 20));

			// desenha a barra vermelha de vida
			if (p1->hp > 0) al_draw_filled_rectangle(200, 50, 200 + 500 * p1->hp / 100, 100, al_map_rgb(255, 0, 0));
        	if (p2->hp > 0) al_draw_filled_rectangle(1220, 50, 1220 + 500 * p2->hp / 100, 100, al_map_rgb(255, 0, 0));

			// desenha o placar
			al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 75, 0, "%d", wins1);
			al_draw_textf(font, al_map_rgb(0, 0, 0), 1120, 75, 0, "%d", wins2);

			// desenha a sombra dos personagens
			al_draw_filled_ellipse(p1->x - 80, 875, 150, 35, al_map_rgba(0, 0, 0, 128));
			al_draw_filled_ellipse(p2->x - 80, 875, 150, 35, al_map_rgba(0, 0, 0, 128));

			// desenha os personagens
			desenha_bitmap_centralizado(sprites[p1->character][p1->estado][p1->sprite], p1->x, p1->y, p1->face);
			desenha_bitmap_centralizado(sprites[p2->character][p2->estado][p2->sprite], p2->x, p2->y, p2->face);

			al_flip_display();
		}

		// tecla pressionada
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			// tecla pressionada
			ajeita_estados(p1, p2, 1, game_mode, event);
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ 
				pause = pause_menu(queue);
				if (pause){
					al_destroy_bitmap(background);
					free(p1);
					free(p2);
					al_destroy_font(font);
					return -1;
				}
			}
		}
	
		//tecla solta
		else if (event.type == ALLEGRO_EVENT_KEY_UP) ajeita_estados(p1, p2, 0, game_mode, event);

		// janela fechada
		else if (event.type == 42){
			al_destroy_bitmap(background);
			free(p1);
			free(p2);
			free(font);
			return -1;
		}

	}

}

void game(ALLEGRO_EVENT_QUEUE* queue){
	int status, winner;

	// placar
	int wins1 = 0;
	int wins2 = 0;

	// menu principal
	int mode = main_menu(queue);
	if (mode == 2) return;

	// selecao de cenario
	int background = background_menu(queue);
	if (background == -1) return;


	// selecao de personagem
	int player1 = player_selection(queue, 1);
	if (player1 == -1) return;

	int player2 = player_selection(queue, 2);
	if (player2 == -1) return;

	// a luta
	while (wins1 < 2 && wins2 < 2){
		status = fight(queue, mode, background, player1, player2, wins1, wins2);
		if (status == -1) return;
		if (status == 1) wins1++;
		if (status == 2) wins2++;
	}

	if (wins1 == 2) winner = 1;
	else winner = 2;
	end_menu(queue, winner);
}

int main(){
	// inicializacoes
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	// habilita a entrada via teclado
	al_install_keyboard();

	// cria as estruturas do jogo
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 24.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_DISPLAY* disp = al_create_display(1920, 1080);

	// indicam o que sera inserido na fila de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_display_event_source(disp));				
	al_register_event_source(queue, al_get_timer_event_source(timer));				

	carrega_sprites();

	// variavel que guarda os eventos capturados
	ALLEGRO_EVENT event;

	al_start_timer(timer);

	// comeca o jogo
	game(queue);

	// liberacao de memoria
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	desaloca_sprites();

	return 0;
}














