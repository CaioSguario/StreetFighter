#ifndef __KEYBOARD__
#define __KEYBOARD__

#include "player.h"

void pulo(player *p, int *sprite_frame_counter, int *action_counter);

void direita(player *p, int *sprite_frame_counter, int *action_counter);

void esquerda(player *p, int *sprite_frame_counter, int *action_counter);

void abaixa(player *p, int *sprite_frame_counter, int *action_counter);

void soco(player *p, int *sprite_frame_counter, int *action_counter);

void chute(player *p, int *sprite_frame_counter, int *action_counter);

#endif
