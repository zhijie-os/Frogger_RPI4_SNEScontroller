Frogger:InforBar.o Menus.o ValuePackage.o SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o Render.o 
	gcc InforBar.o Menus.o ValuePackage.o SNES.o Seg7Simulator.o Game.o Images.o MapFunction.o NumberRender.o FrogFunction.o FrameBuffer.o CharRender.o Render.o  -pthread -g -o Frogger

SNES.o:SNES.c
	gcc -g -c SNES.c

ValuePackage.o:ValuePackage.c
	gcc -g -c ValuePackage.c

Seg7Simulator.o:Seg7Simulator.c
	gcc -g -c Seg7Simulator.c

Render.o:Render.c
	gcc -g -c Render.c

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

CharRender.o:CharRender.c
	gcc -g -c CharRender.c

Menus.o: Menus.c
	gcc -g -c Menus.c

InforBar.o:InforBar.c
	gcc -g -c InforBar.c

clean:
	rm *.o