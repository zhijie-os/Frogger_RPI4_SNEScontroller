frogger:SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o
	gcc SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o -g -o frogger
SNES.o:SNES.c
	gcc -g -c SNES.c

Seg7Simulator.o:Seg7Simulator.c
	gcc -g -c Seg7Simulator.c

Game.o:Game.c
	gcc -g -c Game.c

Images.o:Images.c
	gcc -g -c Images.c

MapFunction.o:MapFunction.c
	gcc -g -c MapFunction.c

NumberRender.o:NumberRender.c
	gcc -g -c NumberRender.c

FrogFunction.o:FrogFunction.c
	gcc -g -c FrogFunction.c

FrameBuffer.o:FrameBuffer.c
	gcc -g -c FrameBuffer.c

CharRender.o:
	gcc -g -c CharRender.c

clean:
	rm *.o