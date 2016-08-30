#-*-sh-*-
CPPFLAGS=-g -W -Wall -Wextra
LIBS = -lSDL2 -lSDL2_image -lGL -lGLEW
INCS = # -I/usr/include/SDL2
sdltest: main.o shader.o mesh.o renderpass.o util.o texture.o gaussian.o
	g++ main.o shader.o mesh.o renderpass.o util.o texture.o gaussian.o -o sdlgame $(LIBS)
main.o: main.cpp shader.h mesh.h renderpass.h util.h
	g++ -c $(CPPFLAGS) $(INCS) main.cpp -o main.o
shader.o: shader.cpp shader.h
	g++ -c $(CPPFLAGS) $(INCS) shader.cpp -o shader.o
mesh.o: mesh.cpp mesh.h
	g++ -c $(CPPFLAGS) $(INCS) mesh.cpp -o mesh.o
renderpass.o: renderpass.cpp renderpass.h
	g++ -c $(CPPFLAGS) $(INCS) renderpass.cpp -o renderpass.o
util.o: util.cpp util.h
	g++ -c $(CPPFLAGS) $(INCS) util.cpp -o util.o
texture.o: texture.cpp texture.h
	g++ -c $(CPPFLAGS) $(INCS) texture.cpp -o texture.o
gaussian.o: gaussian.cpp gaussian.h
	g++ -c $(CPPFLAGS) $(INCS) gaussian.cpp -o gaussian.o
clean:
	rm -f main.o shader.o mesh.o renderpass.o util.o texture.o gaussian.o sdlgame *~
.PHONY: clean

devtest:
	make; ./sdlgame
.PHONY:devtest
