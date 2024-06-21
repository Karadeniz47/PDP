all: derle calistir

derle:
	gcc -I ./inc/ -o ./lib/Habitat.o -c ./src/Habitat.c
	gcc -I ./inc/ -o ./lib/Canli.o -c ./src/Canli.c
	gcc -I ./inc/ -o ./lib/Bitki.o -c ./src/Bitki.c
	gcc -I ./inc/ -o ./lib/Bocek.o -c ./src/Bocek.c
	gcc -I ./inc/ -o ./lib/Sinek.o -c ./src/Sinek.c
	gcc -I ./inc/ -o ./lib/Pire.o -c ./src/Pire.c
	gcc -I ./inc/ -o ./bin/Test ./lib/Habitat.o ./lib/Canli.o ./lib/Bitki.o ./lib/Bocek.o ./lib/Sinek.o ./lib/Pire.o ./src/Test.c
	
calistir:
	./bin/Test