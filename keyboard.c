#include <stdlib.h>
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>

void ajeita_estados(player *p1, player *p2, char keydown, int game_mode, ALLEGRO_EVENT event){
    if (event.keyboard.keycode == ALLEGRO_KEY_D){
		if (keydown) p1->direita = 1;
		else p1->direita = 0;
	}
    else if (event.keyboard.keycode == ALLEGRO_KEY_A){
		if (keydown) p1->esquerda = 1;
		else p1->esquerda = 0;
	}
    else if (event.keyboard.keycode == ALLEGRO_KEY_S){
		if (keydown) p1->abaixando = 1;
		else p1->abaixando = 0;
	}
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

	// multiplayer
    if (game_mode){
        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
			if (keydown) p2->direita = 1;
			else p2->direita = 0;
		}
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT){
			if (keydown) p2->esquerda = 1;
			else p2->esquerda = 0;
		}
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN){
			if (keydown) p2->abaixando = 1;
			else p2->abaixando = 0;
		}
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

void ajeita_singleplayer(player *p1, player *p2, ALLEGRO_EVENT event){
	int random = (rand() % 120) + 1;
	int ataque = rand() % 2;
	int atacando = rand() % 12;

	if (p1->x - p2->x > 350) p2->direita = 1;
	else if (p1->x - p2->x >= 0) p2->direita = 0;

	if (p1->x - p2->x < -350) p2->esquerda = 1;
	else if (p1->x - p2->x <= 0) p2->esquerda = 0;

	if (random == 1 && !(p2->pulo_frame_counter) && !(p2->soco_frame_counter) && !(p2->chute_frame_counter)){
		p2->pulando = 1;
		p2->pulo_frame_counter = 24;
	}

	if (abs(p1->x - p2->x) < 250 && atacando == 1 && !(p2->pulo_frame_counter) && !(p2->soco_frame_counter) && !(p2->chute_frame_counter)){
		if (ataque){
			p2->soco = 1;
			p2->soco_frame_counter = 24;
		} else{
			p2->chute = 1;
			p2->chute_frame_counter = 24;
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
	if (p->esquerda && !(p->direita) && p->x > 220) p->x -= 20;
	if (p->direita && !(p->esquerda) && p->x < 1700) p->x += 20;

	if (p->pulo_frame_counter < 4) p->y += 40;
	else if (p->pulo_frame_counter < 8) p->y += 20;
	else if (p->pulo_frame_counter < 16);
	else if (p->pulo_frame_counter < 20) p->y -= 20;
	else p->y -= 40;
}

void abaixa(player *p){
	p->estado = ABAIXADO;
}

// retorna 1 caso derrote o p2
int soco(player *p1, player *p2, int game_mode){
	p1->estado = ATAQUE_SUPERIOR;

	int dx = abs(p1->x - p2->x);
	int dy = p1->y - p2->y;

	if (p2->abaixando) return 0;

	if (p1->soco_frame_counter > 6 && p1->soco_frame_counter < 18 && dx < 200 && dy < 220){
		if (game_mode) p2->hp--;
		else p2->hp -= 2;
	}
	if (p2->hp == 0) return 1;
	return 0;
}

// retorna 1 caso derrote o p2
int chute(player *p1, player *p2, int game_mode){
	p1->estado = ATAQUE_INFERIOR;
	
	int dx = abs(p1->x - p2->x);
	int dy = p1->y - p2->y;

	if (p2->abaixando) return 0;

	if (p1->chute_frame_counter > 6 && p1->chute_frame_counter < 18 && dx < 200 && dy < 220){
		if (game_mode) p2->hp--;
		else p2->hp -= 2;
	}
	if (p2->hp == 0) return 1;
	return 0;
}

void esquerda(player *p, int game_mode){
	p->estado = ANDANDO;
	if (p->x > 220){
		if (game_mode) p->x -= 20;
		else p->x -= 15;
	}
}

void direita(player *p, int game_mode){
	p->estado = ANDANDO;
	if (p->x < 1700){
		if (game_mode) p->x += 20;
		else p->x += 15;
	}
}

void para(player *p){
	p->estado = EM_PE;
}

// retorna 1 caso o player 2 seja derrotado
int escolhe_acao(player *p1, player *p2, int game_mode){
	int status = 0;
	if (p1->pulando) pula(p1);
	else if (p1->abaixando) abaixa(p1);
	else if (p1->soco || p1->chute){
		if (!(p1->soco)) status = chute(p1, p2, game_mode);
		if (!(p1->chute)) status = soco(p1, p2, game_mode);
	}
	else if (p1->direita && p1->esquerda) para(p1);
	else if (p1->direita) direita(p1, game_mode);
	else if (p1->esquerda) esquerda(p1, game_mode);
	else para(p1);

	return status;
}














