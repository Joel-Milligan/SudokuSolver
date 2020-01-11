#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define WIDTH 9
#define HEIGHT 9
#define H_LINE "---------------------\n"

int **read_puzzle_from_file(char *file_name);
void print_puzzle(int **puzzle);

int main() {
	int **current_puzzle = read_puzzle_from_file("example.txt");
	if(current_puzzle == NULL) {
		exit(EXIT_FAILURE);
	}

	print_puzzle(current_puzzle);
	return 0;
}

int **read_puzzle_from_file(char *file_name) {
	// Initialise 2D puzzle array
	int **puzzle_array = NULL;
	puzzle_array = malloc(HEIGHT * sizeof(int *));
	for(int i = 0; i < HEIGHT; i++) {
		puzzle_array[i] = malloc(WIDTH * sizeof(int));
	}

	// Open file to take puzzle from
	FILE *p_file = fopen(file_name, "r");

	// Insert each number from the file into the array
	if(p_file == NULL) {
		printf("Unable to open file: %s\n", file_name);
		return NULL;
	} else {
		char c[2] = { 'a', '\0'  };
		for(int y = 0; y < HEIGHT; y++) {
			for(int x = 0; x < WIDTH; x++) {
				c[0] = fgetc(p_file);
				if(c[0] != '\n') {
					puzzle_array[x][y] = atoi(c);
					// printf("%d", puzzle_array[x][y]);
				}
			}
		}
	}
	return puzzle_array;
}

void print_puzzle(int **puzzle) {
	for(int y = 0; y < HEIGHT; y++) {
		if(y == 3 || y == 6) {printf(H_LINE);}

		for(int x = 0; x < WIDTH; x++) {
			if(x == 3 || x == 6) {
				printf("| %d ", puzzle[x][y]);
			} else {
				printf("%d ", puzzle[x][y]);
			}
		}
		printf("\n");
	}
}
