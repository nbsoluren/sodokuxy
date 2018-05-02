/*
  Authors:
    Baylon, Kimberly D.
    Saylon, Francis T.
    Soluren, Nicole B.

  Section:
    CMSC 142 C-6L

  Description:
    SUDOKU SOLVER:
    Gets the number of all possible solution to a 
    Sudoku Puzzle
*/


// ---------------------------------------------------------------------------------- //
// HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"
// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //
// CONSTANTS
#define BLANK 0
// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //
// MAIN FUNCTION
int main(){
    
    // ------------------------------------------------------------------------------ //
    // VARIABLE DECLARATIONS
    FILE *fp; 
    int i, j; // Iterators 
    int num_of_boards; // Number of iteration for test case
    int subgrid_size, board_size, **board; // Variables for the board
    int stack_row, stack_col, **stacks; // Variables for the stacks
    // ------------------------------------------------------------------------------ //


    // ------------------------------------------------------------------------------ //
    // ACCESSING INPUT FILE
    fp = fopen("milestone1.in", "r"); // File open
    fscanf(fp, "%d\n", &num_of_boards); // Scans number of boards

    while(num_of_boards > 0){ // Loop until all boards are solved
        fscanf(fp, "%d\n", &subgrid_size); // Scans the size of boards
        board_size = subgrid_size * subgrid_size; // board_size = subgrid_size squared

        // Dynamically allocate board
        board = (int **) malloc(board_size * sizeof(int *));
        for(i=0; i<board_size; i++)
            board[i] = (int *) malloc(board_size * (sizeof(int)));

        // Scan the board from the file
        for(i=0; i<board_size; i++)
            for(j=0; j<board_size; j++)
            fscanf(fp, "%d ", &board[i][j]);
    // ------------------------------------------------------------------------------ //

        /* 
            The implementation of stack will be a 2D array where: 
                ROW == number of stacks or number of blank spaces on the board
                COLUMN == max number of options or board size
            The Top Of Stack (TOS) is the first element of each row in the array.
        */

        // Dynamically allocate the stacks
        stacks = (int **) malloc(stack_row * sizeof(int *));
        for(i=0; i<stack_col; i++)
            stacks[i] = (int *) malloc(stack_col * (sizeof(int)));

        
        printBoard(board, board_size); // Print the board
        destroy(board, board_size); // Free the board
        num_of_boards--; // Decrementor
    }

    return 0;
}
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //
// RESOURCES:
 