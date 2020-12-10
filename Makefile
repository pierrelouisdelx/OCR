files = SDL/main.c SDL/sdl.c SDL/pixel_operations.c SDL/paragraph.c
flags = -Wall -Wextra -std=c99

CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

all: $(files)
	gcc $(files) -o ocr $(flags) -lm

sdl: $(files)
	gcc $(files) -o sdl -lSDL2 $(flags)

xor: 
	gcc $(flags)  NeuralNetwork/*.c -o xor -lm

gtk:
	gcc $(CFLAGS) $(LDLIBS) GTK/main.c

clean:
	rm ocr sdl xor data.txt
