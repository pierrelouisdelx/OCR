sdl = SDL/sdl.c SDL/pixel_operations.c SDL/paragraph.c
gtk = GTK/main.c 
N = NeuralNetwork/main.c NeuralNetwork/neuralnetwork.c NeuralNetwork/row_matrix.c

flags = -Wall -Wextra -std=c99 -lm -lSDL2 -lSDL2_image -rdynamic

CFLAGS = `pkg-config --cflags gtk+-3.0`
LDLIBS = `pkg-config --libs gtk+-3.0` 

all:
	gcc $(CFLAGS) $(LDLIBS) $(flags) $(sdl) $(gtk)  -o ocr 
clean:
	rm ocr
