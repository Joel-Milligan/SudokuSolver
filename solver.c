#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 9
#define H_LINE "---------------------\n"

int power(int base, int exp);
int **read_puzzle_from_file(char *file_name);
void print_puzzle(int **puzzle);
void pass_over_puzzle(int **puzzle);
void pass_over_number(int **puzzle, int x, int y);

int main() {
	int **current_puzzle = read_puzzle_from_file("example.txt");
	if(current_puzzle == NULL) {
		exit(EXIT_FAILURE);
	}

	while(1) {
		print_puzzle(current_puzzle);
		pass_over_puzzle(current_puzzle);
		printf("\n\n");
	}

	return 0;
}

int power(int base, int exp) {
	int answer = base;

	if(exp == 0) {
		return 1;
	}

	for(int i = 1; i < exp; i++) {
		answer *= base;
	}
	return answer;
}

int **read_puzzle_from_file(char *file_name) {
	// Initialise 2D puzzle array
	int **puzzle_array = NULL;
	puzzle_array = malloc(SIZE * sizeof(int *));
	for(int i = 0; i < SIZE; i++) {
		puzzle_array[i] = malloc(SIZE * sizeof(int));
	}

	// Open file to take puzzle from
	FILE *p_file = fopen(file_name, "r");

	// Insert each number from the file into the array
	if(p_file == NULL) {
		printf("Unable to open file: %s\n", file_name);
		return NULL;
	} else {
		char c[2] = { 'a', '\0'  };
		for(int y = 0; y < SIZE; y++) {
			for(int x = 0; x < SIZE; x++) {
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
	for(int y = 0; y < SIZE; y++) {
		if(y == 3 || y == 6) {printf(H_LINE);}

		for(int x = 0; x < SIZE; x++) {
			if(x == 3 || x == 6) {
				printf("| %d ", puzzle[x][y]);
			} else {
				printf("%d ", puzzle[x][y]);
			}
		}
		printf("\n");
	}
}

void pass_over_puzzle(int **puzzle) {
	for(int y = 0; y < SIZE; y++) {
		for(int x = 0; x < SIZE; x++) {
			if(puzzle[x][y] == 0) {
				pass_over_number(puzzle, x, y);
			}
		}
	}
}

void pass_over_number(int **puzzle, int x, int y) {
	int possible = 511; // 111 111 111
	int i, j;

	for(i = 0; i < SIZE; i++) {
		if(x != i && puzzle[i][y] != 0) {
			possible = possible & ~power(2, (puzzle[i][y] - 1));
		}

		if(y != i && puzzle[x][i] != 0) {
			possible = possible & ~power(2, (puzzle[x][i] - 1));
		}
	}

	for(i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++) {
		for(j = (y / 3) * 3; j < (y / 3) * 3 + 3; j++) {
			if(puzzle[i][j] != 0) {
				possible = possible & ~power(2, (puzzle[i][j] - 1));
			}
		}
	}

	switch(possible) {
		case 1:
			puzzle[x][y] = 1;
			break;
		case 2:
			puzzle[x][y] = 2;
			break;
		case 4:
			puzzle[x][y] = 3;
			break;
		case 8:
			puzzle[x][y] = 4;
			break;
		case 16:
			puzzle[x][y] = 5;
			break;
		case 32:
			puzzle[x][y] = 6;
			break;
		case 64:
			puzzle[x][y] = 7;
			break;
		case 128:
			puzzle[x][y] = 8;
			break;
		case 256:
			puzzle[x][y] = 9;
			break;
	}
}
