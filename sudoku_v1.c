/*
  Authors:
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
#include <stdbool.h>

// Constants
#define UNASSIGNED 0

// Function Prototypes
void printMatrix(int **matrix, int row, int col);
void destroy(int **board, int board_size);

bool findUnassignedLocation(int board_size, int **board, int row, int col);
bool isSafe(int board_size, int **board, int row, int col, int num);

bool solveSudoku(int board_size, int **board){
    int row, col;

    if(!findUnassignedLocation(board_size, board, row, col)) return true;

    for(int num = 1; num <= 9; num++){
        if(isSafe(board_size, board, row, col, num)){
            board[row][col] = num;

            if(solveSudoku(board_size, board)) return true;

            board[row][col] = UNASSIGNED;
        }
    }
    return false;
}

bool findUnassignedLocation(int board_size, int **board, int row, int col){
    for(row=0; row < board_size; row++)
        for(col=0; col < board_size; col++)
            if(board[row][col] == UNASSIGNED)
                return true;
    return false;            
}

bool usedInRow(int board_size, int **board, int row, int num){
    for(int col=0; col < board_size; col++){
        if(board[row][col] == num)
            return true;
    return false;        
    }
}

bool usedInCol(int board_size, int **board, int col, int num){
    for(int row=0; row < board_size; row++){
        if(board[row][col] == num)
            return true;
    return false;        
    }
}

bool usedInBox(int board_size, int **board, int boxStartRow, int boxStartCol, int num){
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool isSafe(int board_size, int **board, int row, int col, int num){
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !usedInRow(board_size, board, row, num) &&
           !usedInCol(board_size, board, col, num) &&
           !usedInBox(board_size, board, row - row%3 , col - col%3, num);
}

// Main Function
int main(){
  // Variable Declaration
  FILE *fp;
  int num_of_boards;
  int board_size;
  int i, j;
  int **board;

  fp = fopen("milestone1.in", "r"); // File open
  fscanf(fp, "%d\n", &num_of_boards); // Scans number of boards

//   while(num_of_boards > 0){ // Loop until all boards are solved

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

    if(solveSudoku(board_size, board) == true){
        // Print the board
        printMatrix(board, board_size, board_size);
    }else{
        printf("No solution!");
    }

    // Free the board
    // destroy(board, board_size);
    // num_of_boards--;
//   }

  return 0;
}

// FUNCTIONS
// Function that prints a Matrix
void printMatrix(int **matrix, int row, int col){
	int i, j;

	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%2d ", *(*(matrix+i)+j));
		}
		printf("\n");
	}
}

// Frees dynamically allocated matrix/board
void destroy(int **board, int board_size){
  for(int i=0; i<board_size; i++){
    int *currentIntPtr = board[i];
    free(currentIntPtr);
  }
}
