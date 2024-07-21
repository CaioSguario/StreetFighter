#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>
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

int fight(ALLEGRO_EVENT_QUEUE* queue, int game_mode, int background_choice, int character1, int character2){
	ALLEGRO_EVENT event;

	bool keys[ALLEGRO_KEY_MAX];
	for (int i=0; i<ALLEGRO_KEY_MAX; i++) keys[i] = 0;

	int pause;
	int sprite1_frame_counter = 0;
	int sprite2_frame_counter = 0;
	int action1_counter = 0;
	int action2_counter = 0;

	// inicializa o player1 e o player2
	player *p1 = player_create(210, 340, DIREITA, 500, 750, character1);
	player *p2 = player_create(210, 340, ESQUERDA, 1450, 750, character2);

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
			// atualiza os sprites para gerar animação
			sprite1_frame_counter++;
			if (sprite1_frame_counter == 6){
				sprite1_frame_counter = 0;
				p1->sprite = (p1->sprite + 1) % 4;
			}
			sprite2_frame_counter++;
			if (sprite2_frame_counter == 6){
				sprite2_frame_counter = 0;
				p2->sprite = (p2->sprite + 1) % 4;
			}
			// atualiza os estados dos personagens
			if (!(p1->pulando) && !(p1->atacando) && !(p1->abaixando) && !(p1->direita) && !(p1->esquerda)) p1->estado = EM_PE;
			action1_counter++;
			if (action1_counter == 24){
				action1_counter = 0;
				p1->pulando = 0;
				p1->atacando = 0;
			}
			if (!(p2->pulando) && !(p2->atacando) && !(p2->abaixando) && !(p2->direita) && (p2->esquerda)) p2->estado = EM_PE;
			action2_counter++;
			if (action2_counter == 24){
				action2_counter = 0;
				p2->pulando = 0;
				p2->atacando = 0;
			}

			// desenha as imagens
			al_draw_bitmap(background, 0, 0, 0);
			desenha_bitmap_centralizado(sprites[p1->character][p1->estado][p1->sprite], p1->x, p1->y, p1->face);
			desenha_bitmap_centralizado(sprites[p2->character][p2->estado][p2->sprite], p2->x, p2->y, p2->face);

			al_flip_display();
		}

		// tecla pressionada
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			// tecla pressionada
			if (event.type == ALLEGRO_EVENT_KEY_DOWN){
				// controla o player 1
				if (event.keyboard.keycode == ALLEGRO_KEY_W) pulo(p1, &sprite1_frame_counter, &action1_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_D) direita(p1, &sprite1_frame_counter, &action1_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_A) esquerda(p1, &sprite1_frame_counter, &action1_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_S) abaixa(p1, &sprite1_frame_counter, &action1_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_X) soco(p1, &sprite1_frame_counter, &action1_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_C) chute(p1, &sprite1_frame_counter, &action1_counter);

				// caso multiplayer
				if (game_mode){
					if (event.keyboard.keycode == ALLEGRO_KEY_UP) pulo(p2, &sprite2_frame_counter, &action2_counter);
					else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) direita(p2, &sprite2_frame_counter, &action2_counter);
					else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) esquerda(p2, &sprite2_frame_counter, &action2_counter);
					else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) abaixa(p2, &sprite2_frame_counter, &action2_counter);
					else if (event.keyboard.keycode == ALLEGRO_KEY_K) soco(p2, &sprite2_frame_counter, &action2_counter);
					else if (event.keyboard.keycode == ALLEGRO_KEY_L) chute(p2, &sprite2_frame_counter, &action2_counter);
				}
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ 
				pause = pause_menu(queue);
				if (pause){
					al_destroy_bitmap(background);
					free(p1);
					free(p2);
					return -1;
				}
			}
		}
	
		//tecla solta
		else if (event.type == ALLEGRO_EVENT_KEY_UP){
			// controla o player 1
			if (event.keyboard.keycode == ALLEGRO_KEY_D) direita(p1, &sprite1_frame_counter, &action1_counter);
			else if (event.keyboard.keycode == ALLEGRO_KEY_A) esquerda(p1, &sprite1_frame_counter, &action1_counter);
			else if (event.keyboard.keycode == ALLEGRO_KEY_S) abaixa(p1, &sprite1_frame_counter, &action1_counter);

			// caso multiplayer
			if (game_mode){
				if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) direita(p2, &sprite2_frame_counter, &action2_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) esquerda(p2, &sprite2_frame_counter, &action2_counter);
				else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) abaixa(p2, &sprite2_frame_counter, &action2_counter);
			}
		}

		// janela fechada
		else if (event.type == 42){
			al_destroy_bitmap(background);
			free(p1);
			free(p2);
			return -1;
		}

	}

}

int game(ALLEGRO_EVENT_QUEUE* queue){
	// menu principal
	int mode = main_menu(queue);
	if (mode == 2) return -1;

	// selecao de cenario
	int background = background_menu(queue);
	if (background == -1) return -1;


	// selecao de personagem
	int player1 = player_selection(queue, 1);
	if (player1 == -1) return -1;

	int player2 = player_selection(queue, 2);
	if (player2 == -1) return -1;

	// a luta
	if (fight(queue, mode, background, player1, player2) == -1) return -1;
}

int main(){
	// inicializacoes
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();

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














