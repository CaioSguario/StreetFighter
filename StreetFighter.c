#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main(){
	// prepara a biblioteca allegro
	al_init();

	// habilita a entrada via teclado
	al_install_keyboard();

	// cria o relógio do jogo com 30 atualizações por segundo
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

	// cria a fila de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// carrega a fonte padrao para escrever na tela
	ALLEGRO_FONT* font = al_create_builtin_font();

	// cria a janela do programa, nesse caso, full screen
	ALLEGRO_DISPLAY* disp = al_create_display(1920, 1080);

	// indicam o que sera inserido na fila de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());				
	al_register_event_source(queue, al_get_display_event_source(disp));				
	al_register_event_source(queue, al_get_timer_event_source(timer));				

	// variavel que guarda os eventos capturados
	ALLEGRO_EVENT event;

	// inicia o timer
	al_start_timer(timer);							


	// laço principal do programa
	while(1){
		al_wait_for_event(queue, &event);

		// evento de relogio
		if (event.type == 30){
			
		}
		// evento de fechamento da janela
		else if (event.type == 42) break;
	}

	// liberacao de memoria
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}














