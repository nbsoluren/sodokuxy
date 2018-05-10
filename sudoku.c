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
    int i, j, l=0; // Iterators 
    int num_of_boards; // Number of iteration for test case
    int subgrid_size, board_size, **board; // Variables for the board
    int stack_row_size, stack_col_size; // Variables for the stacks
    NODE **stacks;
    int count_sudoku=0;
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
        int stack_row;

        do{
            stack_row=l;
            for(i=0; i<board_size; i++){
                for(j=0; j<board_size; j++){
                    if(board[i][j] == BLANK){
                        for(int num=1; num<board_size+1; num++){
                            if(isSafe(board, board_size, subgrid_size, i, j, num)){

                                // Push to stack 
                                printf("pushing %d to stack %d, i: %d, j: %d\n", num, stack_row+1, i,j);
                                push(&stacks[stack_row], i, j, num);

                                // if(stacks[stack_row]->next == NULL){ // Check if stack is empty
                                    populate(board, stacks, stack_row_size);
                                // }
                                // printBoard(board, board_size); // Print the board
                                    
                            }
                        }
                        stack_row++;
                    }
                }
            }
            count_sudoku++; // Solution Found! Increment counter!
            printf("\nSolution %d Found!\n", count_sudoku);    
            printBoard(board, board_size); // Print the board
            printStacks(stacks, stack_row_size); //Print the stacks

            for(l=stack_row_size-1; l>0; l--){
                if(stacks[l]->next != NULL){
                    board[stacks[l]->row][stacks[l]->col] = stacks[l]->next->val;
                    printf("popping head %d; replaced by %d\n", stacks[l]->val, stacks[l]->next->val);
                    
                    // Change rows and columns of replacing node 
                    stacks[l]->next->row = stacks[l]->row;
                    stacks[l]->next->col = stacks[l]->col;
                    
                    pop(&stacks[l]);
                }else{
                    board[stacks[l]->row][stacks[l]->col] = 0;
                    printf("popping head %d\n", stacks[l]->val);
                    pop(&stacks[l]);    
                }

                // printBoard(board, board_size); // Print the board
                if(stacks[l] != NULL) break; //Checks if there's a next value after popping
                
            }   
        }while(stacks[0]!=NULL);
        
        destroy_int(board, board_size); // Free the board
        printBoard(board, board_size); // Print the board
            
        // for(i=0; i<stack_row_size; i++) destroy_node(&stacks[i]); // Free the stacks
        num_of_boards--; // Decrementor
    }

    return 0;
}
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //
// RESOURCES:
 