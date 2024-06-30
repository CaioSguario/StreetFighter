FLAGS = $(shell pkg-config allegro-5 allegro_image-5 allegro_primitives-5 allegro_main-5 allegro_font-5 --libs --cflags)

CC = gcc

all: SF

SF: StreetFighter.o
	@$(CC) StreetFighter.o -o SF $(FLAGS)

StreetFighter.o: StreetFighter.c
	@$(CC) -c StreetFighter.c $(FLAGS)

# limpa todos os objetos
clean:
	@rm -f *.o

# limpa todos os objetos e o executavel
purge: clean
	@rm -f SF

