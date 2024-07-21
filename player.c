#include <stdlib.h>
#include "player.h"

player* player_create(int h_side, int v_side, unsigned char face, int x, int y, int character){
	player *p = (player*) malloc(sizeof(player));

	p->character = character;
	p->estado = EM_PE;
	p->sprite = 0;
	p->v_side = v_side;
	p->h_side = h_side;
	p->x = x;
	p->y = y;
	p->face = face;
	p->hp = 100;
	p->soco = 0;
	p->chute = 0;
	p->abaixando = 0;
	p->pulando = 0;
	p->esquerda = 0;
	p->direita = 0;
	p->pulo_frame_counter = 0;
	p->soco_frame_counter = 0;
	p->chute_frame_counter = 0;
	return p;
}
