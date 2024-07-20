#include <stdlib.h>
#include "keyboard.h"

void pulo(player *p, int *sprite_frame_counter){
	if (p->abaixando) return;

	p->estado = PULANDO;
	p->sprite = 0;
	p->pulando = 1;

	*sprite_frame_counter = 0;
}

void direita(player *p, int *sprite_frame_counter){
	if (p->abaixando) return;
}

void esquerda(player *p, int *sprite_frame_counter){
	if (p->abaixando) return;

}

void abaixa(player *p, int *sprite_frame_counter){
	if (p->pulando || p->atacando) return;
}

void soco(player *p, int *sprite_frame_counter){
	if (p->abaixando) return;

}

void chute(player *p, int *sprite_frame_counter){
	if (p->abaixando) return;

}

