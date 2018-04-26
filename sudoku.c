/*
  boarduthors:
    Baylon, Kimberly D.
    Saylon, Francis T.
    Soluren, Nicole B.

  Section:
    CMSC 142 C-6L

  Description:
    Sudoku Solver
*/

#include <stdio.h>
#include <stdlib.h>

// Function that prints a Matrix
void printMatrix(int **matrix, int row, int col){
	int i, j;

	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%d ", *(*(matrix+i)+j));
		}
		printf("\n");
	}
}

int main(){
  // Variable Declaration
  FILE *fp;
  int num_of_boards;
  int board_size;
  int i, j;
  int **board;

  fp = fopen("milestone1.in", "r"); // File open
  fscanf(fp, "%d\n", &num_of_boards); // Scans number of boards

  while(num_of_boards > 0){ // Loop until all boards are solved
    fscanf(fp, "%d\n", &board_size); // Scans the size of boards
    board_size *= board_size; // board_size = board_size raised to 2

    // Dynamically allocate board
    board = (int **) malloc(board_size * sizeof(int *));
    for(i=0; i<board_size; i++)
      board[i] = (int *) malloc(board_size * (sizeof(int)));

    // Scan the board from the file
    for(i=0; i<board_size; i++)
      for(j=0; j<board_size; j++)
        fscanf(fp, "%d ", &board[i][j]);

    // Print the board
    printMatrix(board, board_size, board_size);
    num_of_boards--;
  }

  // Frees dynamically allocated matrix/board
  for(i= 0; i<board_size*board_size; i++){
    int  *currentIntPtr = board[i];
    free(currentIntPtr);
	}


  return 0;
}
