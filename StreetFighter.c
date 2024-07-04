#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"

int fight(ALLEGRO_EVENT_QUEUE* queue, char game_mode, char background_choice, char character1, char character2){
	ALLEGRO_EVENT event;

	int pause;

	// seleciona o background escolhido
	ALLEGRO_BITMAP* background;
	if (background_choice == 0) background = al_load_bitmap("./images/backgrounds/background1.jpg");
	else if (background_choice == 1) background = al_load_bitmap("./images/backgrounds/background2.jpg");
	else if (background_choice == 2) background = al_load_bitmap("./images/backgrounds/background3.jpg");

	// laco principal do jogo
	while (1){
		al_wait_for_event(queue, &event);

		if (event.type == 30){
			al_draw_bitmap(background, 0, 0, 0);

			al_flip_display();
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ 
				pause = pause_menu(queue);
				if (pause) return -1;
			}
		}
		else if (event.type == 42){
			al_destroy_bitmap(background);
			return -1;
		}

	}
}

int game(ALLEGRO_EVENT_QUEUE* queue){
	// menu principal
	char mode = main_menu(queue);
	if (mode == 2) return -1;

	// selecao de cenario
	char background = background_menu(queue);
	if (background == -1) return -1;

	// selecao de personagem
	char player1 = player_selection(queue, 1);
	if (player1 == -1) return -1;
	char player2 = player_selection(queue, 2);
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
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_DISPLAY* disp = al_create_display(1920, 1080);

	// indicam o que sera inserido na fila de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_display_event_source(disp));				
	al_register_event_source(queue, al_get_timer_event_source(timer));				

	// variavel que guarda os eventos capturados
	ALLEGRO_EVENT event;

	// inicia o timer
	al_start_timer(timer);							

	// comeca o jogo
	game(queue);

/*
	// laço principal do programa
	while(1){
		al_wait_for_event(queue, &event);

		// evento de relogio
		if (event.type == 30){
			
		}
		// evento de fechamento da janela
		else if (event.type == 42) break;
	}
*/

	// liberacao de memoria
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}














