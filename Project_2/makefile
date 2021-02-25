Game: FrogFunction.o MapFunction.o SNES.o Game.o
	gcc  FrogFunction.o MapFunction.o SNES.o Game.o -o Game 

FrogFunction.o: FrogFunction.c 
	gcc -c FrogFunction.c

MapFunction.o: MapFunction.c 
	gcc -c MapFunction.c

SNES.o: SNES.c 
	gcc -c SNES.c

Game.o:Game.c
	gcc -c Game.c 

clean:
	rm *.o