all: main.c ./src/TAD.c ./src/Loaders.c ./src/FirstQuery.c ./src/SecondQuery.c
	gcc -g -pedantic -Wall -std=c99 -fsanitize=address main.c src/FirstQuery.c src/Loaders.c src/SecondQuery.c src/TAD.c -o archivo_de_salida.o
