frogger:SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o
	gcc SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o -o frogger
SNES.o:SNES.c
	gcc -c SNES.c

Seg7Simulator.o:Seg7Simulator.c
	gcc -c Seg7Simulator.c

Game.o:Game.c
	gcc -c Game.c

Images.o:Images.c
	gcc -c Images.c

MapFunction.o:MapFunction.c
	gcc -c MapFunction.c

NumberRender.o:NumberRender.c
	gcc -c NumberRender.c

FrogFunction.o:FrogFunction.c
	gcc -c FrogFunction.c

FrameBuffer.o:FrameBuffer.c
	gcc -c FrameBuffer.c

CharRender.o:
	gcc -c CharRender.c

clean:
	rm *.o