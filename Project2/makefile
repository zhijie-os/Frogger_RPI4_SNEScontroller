Game: FrogFunction.o MapFunction.o SNES.o Game.o FrameBuffer.o Images.o
	gcc  FrogFunction.o MapFunction.o SNES.o Game.o FrameBuffer.o Images.o -o Game 

FrogFunction.o: FrogFunction.c 
	gcc -c FrogFunction.c

MapFunction.o: MapFunction.c 
	gcc -c MapFunction.c

SNES.o: SNES.c 
	gcc -c SNES.c

Game.o:Game.c
	gcc -c Game.c 

FrameBuffer.o:FrameBuffer.c
	gcc -c FrameBuffer.c 

Images.o:Images.c
	gcc -c Images.c
clean:
	rm *.o Game