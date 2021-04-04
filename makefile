Frogger:InforBar.o Menus.o ValuePackage.o SNES.o Game.o Images.o MapFunction.o FrogFunction.o FrameBuffer.o Render.o 
	gcc InforBar.o Menus.o ValuePackage.o SNES.o Game.o Images.o MapFunction.o FrogFunction.o FrameBuffer.o Render.o -pthread -g -o Frogger

SNES.o:SNES.c
	gcc -g -c SNES.c

ValuePackage.o:ValuePackage.c
	gcc -g -c ValuePackage.c

Render.o:Render.c
	gcc -g -c Render.c

Game.o:Game.c
	gcc -g -c Game.c

Images.o:Images.c
	gcc -g -c Images.c

MapFunction.o:MapFunction.c
	gcc -g -c MapFunction.c


FrogFunction.o:FrogFunction.c
	gcc -g -c FrogFunction.c

FrameBuffer.o:FrameBuffer.c
	gcc -g -c FrameBuffer.c


Menus.o: Menus.c
	gcc -g -c Menus.c

InforBar.o:InforBar.c
	gcc -g -c InforBar.c

clean:
	rm *.o