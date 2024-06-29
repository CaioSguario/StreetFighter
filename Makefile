# Flags para o compilador e linker
FLAGS = $(shell pkg-config allegro-5 allegro_image-5 allegro_primitives-5 allegro_main-5 allegro_font-5 --libs --cflags)

# Comando do compilador
CC = gcc

# Regra padrão para compilar o programa
all: SF

# Regra para compilar o executável
SF: StreetFighter.o
	@$(CC) StreetFighter.o -o SF $(FLAGS)

# Regra para compilar o arquivo objeto
StreetFighter.o: StreetFighter.c
	@$(CC) -c StreetFighter.c $(FLAGS)

# Regra para limpar os arquivos objeto
clean:
	@rm -f *.o

# Regra para limpar os arquivos objeto e o executável
purge: clean
	@rm -f SF

