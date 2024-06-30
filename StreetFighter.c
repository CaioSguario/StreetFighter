#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
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
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) return choice;
		}
		// evento de fechamento da janela
		else if (event.type == 42) return 2;	
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
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) return choice;
		}
		// evento de fechamento da janela
		else if (event.type == 42) return -1;	
	}
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

	main_menu(queue);
	background_menu(queue);

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














