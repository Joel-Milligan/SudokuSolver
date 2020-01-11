#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define WIDTH 9
#define HEIGHT 9

int **read_puzzle_from_file(char *file_name);
// TODO void print_sudoku(int **sudoku_puzzle);

int main() {
	return 0;
}

int **read_puzzle_from_file(char *file_name) {
	// Initialise 2D puzzle array
	int **puzzle_array = NULL;
	puzzle_array = malloc(WIDTH * sizeof(int *));
	for(int i = 0; i < WIDTH; i++) {
		puzzle_array[i] = malloc(HEIGHT * sizeof(int));
	}

	// Open file to take puzzle from
	FILE *p_file = fopen(file_name, "r");

	// Insert each number from the file into the array
	if(p_file == NULL) {
		printf("Unable to open file: %s\n", file_name);
		return NULL;
	} else {
		char c[2] = { 'a', '\0'  };
		for(int x = 0; x < WIDTH; x++) {
			for(int y = 0; y < HEIGHT; y++) {
				while(1) {
					c[0] = fgetc(p_file);
					if(isdigit(c)) {break;}
				}
				puzzle_array[x][y] = atoi(c);
			}
		}
	}
	return puzzle_array;
}
