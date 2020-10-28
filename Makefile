files = SDL/main.c SDL/sdl.c SDL/pixel_operations.c SDL/grayscale.c SDL/noisecancel.c SDL/blackwhite.c SDL/paragraph.c
flags = -Wall -Wextra -std=c99 -lm

all: $(files)
	gcc $(files) -o ocr $(flags)

sdl: $(files)
	gcc $(files) -o sdl -lSDL2 $(flags)

xor: 
	gcc $(flags)  NeuralNetwork/*.c -o xor

gtk: $(files)
	gcc `pkg-config --cflags --libs gtk+-3.0` 
	`pkg-config --cflags --libs gtk+-3.0` $(flags) GTK/$(files)

clean:
	rm ocr sdl xor data.txt
