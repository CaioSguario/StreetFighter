#ifndef __MENU__
#define __MENU__

#include <allegro5/allegro5.h>

int pause_menu(ALLEGRO_EVENT_QUEUE* queue);
int main_menu(ALLEGRO_EVENT_QUEUE* queue);
int background_menu(ALLEGRO_EVENT_QUEUE* queue);
int player_selection(ALLEGRO_EVENT_QUEUE* queue, int player);

#endif
