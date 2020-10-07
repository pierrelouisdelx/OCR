files = main.c
flags = -Wall -Wextra -std=c99

all: $(files)
	gcc $(files) -o OCR.o $(flags)

sdl: $(files)
	gcc SDL/$(files) -o SDL.o -lSDL2 $(flags)

gtk: $(files)
	gcc `pkg-config --cflags --libs gtk+-3.0` 
	`pkg-config --cflags --libs gtk+-3.0` $(flags) GTK/$(files)

clean:
	rm OCR.o SDL.o