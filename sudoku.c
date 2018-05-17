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
#include <string.h>
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
    int stack_row_size, stack_col_size; // Variables for the stacks
    NODE **stacks;
    int count_sudoku=0, count_sudokuX=0, count_sudokuY=0, count_sudokuXY=0;
    // ------------------------------------------------------------------------------ //


    // ------------------------------------------------------------------------------ //
    // ACCESSING INPUT FILE
    fp = fopen("test.in", "r"); // File open
    fscanf(fp, "%d\n", &num_of_boards); // Scans number of boards

    // Array for storing of answers
    ANSWERS * answers = (ANSWERS *) malloc(num_of_boards * sizeof(ANSWERS));
    int answer_iter = 0;
    
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
            The implementation of stack will be an array of linked list where: 
                SIZE_OF_ARRAY == number of stacks or number of blank spaces on the board
                NUMBER_OF_NODES == max number of options or board size
            The Top Of Stack (TOS) is the first element of each row in the array.
        */
        
        stack_row_size = findBlank(board, board_size);
        stack_col_size = board_size;

        // Dynamically allocate the stacks
        stacks = (NODE **) malloc(stack_row_size * (sizeof(NODE*)));
            
        ANSWERS counters = solve(board, board_size, subgrid_size, stacks, stack_row_size);

        printf("Finished looking for solutions.\n\n");
        if(counters.sudoku == 0) printf("No solutions found!\n");
        else {
            printf("Number of solution/s found: %d\n", counters.sudoku);
        }
        destroy_int(board, board_size); // Free the board
        // printBoard(board, board_size); // Print the board         
        // for(i=0; i<stack_row_size; i++) destroy_node(&stacks[i]); // Free the stacks
        num_of_boards--; // Decrementor
        answers[answer_iter++] = counters;
    }
    
    printf("\nNumber of Solutions for all Test Cases:\n");
    for(i=0; i<answer_iter; i++){
        printf("\nBoard: %d \nSudoku: %d \nSudokuX: %d \nSudokuY: %d \nSudokuXY: %d\n", i+1, answers[i].sudoku, answers[i].sudokuX, answers[i].sudokuY, answers[i].sudokuXY);
    }
    return 0;
}
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //
// RESOURCES:
 