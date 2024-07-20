#ifndef __PLAYER__
#define __PLAYER__

typedef struct player{
	int x;
	int y;
	int h_side;
	int v_side;
	unsigned char face;
	unsigned char hp;
	unsigned char atacando;
	unsigned char pulando;
	unsigned char abaixando;
} player;

player* player_create(int h_side, int v_side, unsigned char face, int x, int y);

#endif
