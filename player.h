#ifndef __PLAYER__
#define __PLAYER__

#define ABAIXADO 0
#define ANDANDO 1
#define EM_PE 2
#define PULANDO 3
#define ATAQUE_SUPERIOR 4
#define ATAQUE_INFERIOR 5

typedef struct player{
	int character;
	int estado;
	int sprite;
	int x;
	int y;
	int h_side;
	int v_side;
	unsigned char face;
	unsigned char hp;
	unsigned char atacando;
	unsigned char pulando;
	unsigned char abaixando;
	unsigned char direita;
	unsigned char esquerda;
} player;

player* player_create(int h_side, int v_side, unsigned char face, int x, int y, int character);

#endif
