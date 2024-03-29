sdl = SDL/sdl.c SDL/pixel_operations.c SDL/paragraph.c SDL/rotate.c
gtk = GTK/main.c 
N = NeuralNetwork/ocr.c NeuralNetwork/neuralnetwork.c NeuralNetwork/row_matrix.c

flags = -Wall -Wextra -std=c99 -lm -lSDL2 -lSDL2_image -rdynamic

CFLAGS = `pkg-config --cflags gtk+-3.0`
LDLIBS = `pkg-config --libs gtk+-3.0` 

all:
	gcc $(sdl) $(gtk) $(N) $(CFLAGS) $(LDLIBS) $(flags) -o ocr 
	
clean:
	rm ocr
