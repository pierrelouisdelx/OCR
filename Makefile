files = main.c
flags = -Wall -Wextra -std=c99

all: $(files)
	gcc $(files) -o OCR.o $(flags)

sdl: $(files)
	gcc SDL/$(files) -o SDL.o -lSDL2 $(flags)

clean:
	rm OCR.o SDL.o
