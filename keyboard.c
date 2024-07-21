#include <stdlib.h>
#include "keyboard.h"

void pulo(player *p, int *sprite_frame_counter, int *action_counter){
	if (p->abaixando || p->pulando || p->atacando) return;
	
	p->estado = PULANDO;
	p->sprite = 0;
	p->pulando = 1;

	*sprite_frame_counter = 0;
	*action_counter = 0;
}

void direita(player *p, int *sprite_frame_counter, int *action_counter){
	if (p->abaixando || p->pulando || p->atacando) return;

	if (p->estado == ANDANDO) p->estado = EM_PE;
	else p->estado = ANDANDO;
	p->sprite = 0;
	p->direita ^= 1;

	*sprite_frame_counter = 0;
	*action_counter = 0;
}

void esquerda(player *p, int *sprite_frame_counter, int *action_counter){
}

void abaixa(player *p, int *sprite_frame_counter, int *action_counter){
	if (p->pulando || p->atacando) return;
}

void soco(player *p, int *sprite_frame_counter, int *action_counter){
	if (p->abaixando || p->pulando || p->atacando) return;
	
	p->estado = ATAQUE_SUPERIOR;
	p->sprite = 0;
	p->esquerda = 0;
	p->direita = 0;
	p->atacando = 1;

	*sprite_frame_counter = 0;
	*action_counter = 0;
}

void chute(player *p, int *sprite_frame_counter, int *action_counter){
	if (p->abaixando || p->pulando || p->atacando) return;
	
	p->estado = ATAQUE_INFERIOR;
	p->sprite = 0;
	p->esquerda = 0;
	p->direita = 0;
	p->atacando = 1;

	*sprite_frame_counter = 0;
	*action_counter = 0;
}

