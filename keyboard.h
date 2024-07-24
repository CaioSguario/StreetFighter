#ifndef __KEYBOARD__
#define __KEYBOARD__

#include "player.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void ajeita_estados(player *p1, player *p2, char keydown, int game_mode, ALLEGRO_EVENT event);

void atualiza_estados(player *p);

void escolhe_acao(player *p1, player *p2);

#endif
