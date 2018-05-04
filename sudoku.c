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
    int stack_row_size, stack_col_size; // Variables for the stacks
    NODE **stacks;
    // ------------------------------------------------------------------------------ //


    // ------------------------------------------------------------------------------ //
    // ACCESSING INPUT FILE
    fp = fopen("test.in", "r"); // File open
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
            The implementation of stack will be an array of linked list where: 
                SIZE_OF_ARRAY == number of stacks or number of blank spaces on the board
                NUMBER_OF_NODES == max number of options or board size
            The Top Of Stack (TOS) is the first element of each row in the array.
        */
        
        stack_row_size = findBlank(board, board_size);
        stack_col_size = board_size;

        // Dynamically allocate the stacks
        stacks = (NODE **) malloc(stack_row_size * (sizeof(NODE*)));
        int stack_row=0, stack_col=0;

        for(i=0; i<board_size; i++){
            for(j=0; j<board_size; j++){
                if(board[i][j] == BLANK){
                    for(int num=1; num<board_size+1; num++){
                        if(isSafe(board, board_size, subgrid_size, i, j, num)){
                            // printf("SAFE: %d %d %d\n", i, j, num);

                            if(board[i][j] == BLANK){
                                board[i][j] = num;
                            }         
                            push(&stacks[stack_row], i, j, num);
                        }
                    }
                    stack_row++;
                }
            }
        }

        printStacks(stacks, stack_row_size); //Print the stacks

        printBoard(board, board_size); // Print the board
        destroy_int(board, board_size); // Free the board
        for(i=0; i<stack_row_size; i++) destroy_node(&stacks[i]); // Free the stacks
        num_of_boards--; // Decrementor
    }

    return 0;
}
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //
// RESOURCES:
 