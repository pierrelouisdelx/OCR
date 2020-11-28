files = SDL/main.c SDL/sdl.c SDL/pixel_operations.c SDL/grayscale.c SDL/noisecancel.c SDL/blackwhite.c SDL/paragraph.c
flags = -Wall -Wextra -std=c99

all: $(files)
	gcc $(files) -o ocr $(flags) -lm

sdl: $(files)
	gcc $(files) -o sdl -lSDL2 $(flags)

xor: 
	gcc $(flags)  NeuralNetwork/*.c -o xor -lm

gtk: $(files)
	g-config --cflags --libs gtk+-3.0` $(flags) GTK/$(files


clean:
	rm ocr sdl xor data.txt
