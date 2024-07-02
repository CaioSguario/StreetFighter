#include "menu.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

int main_menu(ALLEGRO_EVENT_QUEUE* queue){
	// carrega a imagem
	ALLEGRO_BITMAP* main_menu_image = al_load_bitmap("./images/menus/main_menu_image.jpg");

	ALLEGRO_EVENT event;

	// escolha atual
	int choice = 0;

	while (1){
		if (choice == -1) choice = 2;
		choice = choice % 3;
		al_wait_for_event(queue, &event);

		// evento de relogio
		// desenha a imagem e faz a selecao da opcao
		if (event.type == 30){
			al_draw_bitmap(main_menu_image, 0, 0, 0);

			if (choice == 0) al_draw_filled_circle(756, 639, 10, al_map_rgb(237, 28, 36));
			else if (choice == 1) al_draw_filled_circle(771, 712, 10, al_map_rgb(237, 28, 36));
			else if (choice == 2) al_draw_filled_circle(867, 792, 10, al_map_rgb(237, 28, 36));

			al_flip_display();
		}
		// tecla pressionada
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) choice++;
			else if (event.keyboard.keycode == ALLEGRO_KEY_UP) choice--;
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
				al_destroy_bitmap(main_menu_image);
				return choice;
			}
		}
		// evento de fechamento da janela
		else if (event.type == 42){
			al_destroy_bitmap(main_menu_image);
			return 2;	
		}
	}
}

int background_menu(ALLEGRO_EVENT_QUEUE* queue){
	// carrega a imagem
	ALLEGRO_BITMAP* background_menu = al_load_bitmap("./images/menus/background_selection_menu.png");

	ALLEGRO_EVENT event;

	// escolha atual
	int choice = 0;

	while (1){
		if (choice == -1) choice = 2;
		choice = choice % 3;
		al_wait_for_event(queue, &event);

		// evento de relogio
		// desenha a imagem e faz a selecao da opcao
		if (event.type == 30){
			al_draw_bitmap(background_menu, 0, 0, 0);

			if (choice == 0) al_draw_filled_circle(397, 750, 10, al_map_rgb(237, 28, 36));
			else if (choice == 1) al_draw_filled_circle(970, 750, 10, al_map_rgb(237, 28, 36));
			else if (choice == 2) al_draw_filled_circle(1538, 750, 10, al_map_rgb(237, 28, 36));

			al_flip_display();
		}
		// tecla pressionada
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) choice++;
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) choice--;
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
				al_destroy_bitmap(background_menu);
				return choice;
			}
		}
		// evento de fechamento da janela
		else if (event.type == 42){
			al_destroy_bitmap(background_menu);	
			return -1;
		}
	}
}

int player_selection(ALLEGRO_EVENT_QUEUE* queue, int player){
	// carrega a imagem
	ALLEGRO_BITMAP* player1_menu = al_load_bitmap("./images/menus/player1_selection.png");
	ALLEGRO_BITMAP* player2_menu = al_load_bitmap("./images/menus/player2_selection.png");
	ALLEGRO_BITMAP* menu;

	if (player == 1) menu = player1_menu;
	else menu = player2_menu;

	ALLEGRO_EVENT event;

	// escolha atual
	int choice = 0;

	while (1){
		if (choice == -1) choice = 3;
		choice = choice % 4;
		al_wait_for_event(queue, &event);

		// evento de relogio
		// desenha a imagem e faz a selecao da opcao
		if (event.type == 30){
			al_draw_bitmap(menu, 0, 0, 0);

			if (choice == 0) al_draw_filled_circle(425, 800, 10, al_map_rgb(237, 28, 36));
			else if (choice == 1) al_draw_filled_circle(780, 800, 10, al_map_rgb(237, 28, 36));
			else if (choice == 2) al_draw_filled_circle(1135, 800, 10, al_map_rgb(237, 28, 36));
			else if (choice == 3) al_draw_filled_circle(1508, 800, 10, al_map_rgb(237, 28, 36));

			al_flip_display();
		}
		// tecla pressionada
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) choice++;
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) choice--;
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
				al_destroy_bitmap(player1_menu);
				al_destroy_bitmap(player2_menu);
				return choice;
			}
		}
		// evento de fechamento da janela
		else if (event.type == 42){
			al_destroy_bitmap(player1_menu);	
			al_destroy_bitmap(player2_menu);
			return -1;
		}
	}
}



















