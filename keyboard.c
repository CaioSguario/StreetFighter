#include <stdlib.h>
#include "keyboard.h"
#include <stdio.h>

void ajeita_estados(player *p1, player *p2, char keydown, int game_mode, ALLEGRO_EVENT event){
    if (event.keyboard.keycode == ALLEGRO_KEY_D) p1->direita ^= 1;
    else if (event.keyboard.keycode == ALLEGRO_KEY_A) p1->esquerda ^= 1;
    else if (event.keyboard.keycode == ALLEGRO_KEY_S) p1->abaixando ^= 1;
    else if (event.keyboard.keycode == ALLEGRO_KEY_W){
        if (keydown && !(p1->pulo_frame_counter) && !(p1->soco_frame_counter) && !(p1->chute_frame_counter)){
			p1->pulando = 1;
			p1->pulo_frame_counter = 24;
		}
    }
    else if (event.keyboard.keycode == ALLEGRO_KEY_X){
        if (keydown && !(p1->pulo_frame_counter) && !(p1->soco_frame_counter) && !(p1->chute_frame_counter)) {
            p1->soco = 1;
			p1->soco_frame_counter = 24;
        }
    }
    else if (event.keyboard.keycode == ALLEGRO_KEY_C){
        if (keydown && !(p1->pulo_frame_counter) && !(p1->soco_frame_counter) && !(p1->chute_frame_counter)) {
            p1->chute = 1;
			p1->chute_frame_counter = 24;
        }
    }

    if (game_mode){
        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) p2->direita ^= 1;
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) p2->esquerda ^= 1;
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) p2->abaixando ^= 1;
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP){
            if (keydown && !(p2->pulo_frame_counter) && !(p2->soco_frame_counter) && !(p2->chute_frame_counter)){
				p2->pulando = 1;
				p2->pulo_frame_counter = 24;
			}
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_K){
            if (keydown && !(p2->pulo_frame_counter) && !(p2->soco_frame_counter) && !(p2->chute_frame_counter)) {
                p2->soco = 1;
				p2->soco_frame_counter = 24;
            }
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_L){
            if (keydown && !(p2->pulo_frame_counter) && !(p2->soco_frame_counter) && !(p2->chute_frame_counter)) {
                p2->chute = 1;
				p2->chute_frame_counter = 24;
            }
        }
    }
}

void atualiza_estados(player *p){
    if (p->pulando) {
        if (p->pulo_frame_counter > 0) {
            p->pulo_frame_counter--;
        } else {
            p->pulando = 0;
        }
    }
    if (p->soco) {
        if (p->soco_frame_counter > 0) {
            p->soco_frame_counter--;
        } else {
            p->soco = 0;
        }
    }
    if (p->chute) {
        if (p->chute_frame_counter > 0) {
            p->chute_frame_counter--;
        } else {
            p->chute = 0;
        }
    }
}

void pula(player *p){
	p->estado = PULANDO;
	if (p->esquerda && !(p->direita)) p->x -= 20;
	if (p->direita && !(p->esquerda)) p->x += 20;

	if (p->pulo_frame_counter < 4) p->y += 40;
	else if (p->pulo_frame_counter < 8) p->y += 20;
	else if (p->pulo_frame_counter < 16);
	else if (p->pulo_frame_counter < 20) p->y -= 20;
	else p->y -= 40;
}

void abaixa(player *p){
	p->estado = ABAIXADO;
}

void soco(player *p){
	p->estado = ATAQUE_SUPERIOR;
}

void chute(player *p){
	p->estado = ATAQUE_INFERIOR;
}

void esquerda(player *p){
	p->estado = ANDANDO;
	p->x -= 20;
}

void direita(player *p){
	p->estado = ANDANDO;
	p->x += 20;
}

void para(player *p){
	p->estado = EM_PE;
}

void escolhe_acao(player *p){
	if (p->pulando) pula(p);
	else if (p->abaixando) abaixa(p);
	else if (p->soco || p->chute){
		if (!(p->soco)) chute(p);
		if (!(p->chute)) soco(p);
	}
	else if (p->direita && p->esquerda) para(p);
	else if (p->direita) direita(p);
	else if (p->esquerda) esquerda(p);
	else para(p);
}














