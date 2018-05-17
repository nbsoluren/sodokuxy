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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <QDebug>
#include "sudokusolver.h"


#define BLANK 0


// Function that prints a Matrix
void printBoard(int **board, int size){
    printf("BOARD----------------------\n");
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            printf("%2d ", *(*(board+i)+j));
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

// Frees dynamically allocated board
void destroy_int(int **board, int board_size){
  for(int i=0; i<board_size; i++){
    int *currentIntPtr = board[i];
    free(currentIntPtr);
  }
}

//Creates a function that frees the linked list when the program terminates
void destroy_node(NODE **head){
    if(*head==NULL){
        free(*head);
    }else{
        while(*head!=NULL){
            destroy_node(head);
        }
    }
}
//checks if it has given duplicate values in all rows
bool isDupeRow(int **board, int board_size ){
    int x, r, a[board_size];
    for(x=0;x<board_size;x++){//traverse columns
        for(r=0;r<board_size;r++){
            //put in an array
            a[r]=board[r][x];
        }
        //check if there are repeated values
        int *count = (int *)calloc(sizeof(int), (board_size - 2));
        for(int i=0;i<board_size;i++){
            if(a[i] !=0){
                if(count[a[i]] == 1){
                    return true;
                }else{
                    count[a[1]]++;
                }
            }

        }
    }
    return false;
}
//checks if it has given duplicate values in all columns
bool isDupeCol(int **board, int board_size ){
    int x, r, a[board_size];
    for(x=0;x<board_size;x++){//traverse rows
        for(r=0;r<board_size;r++){
            //put in an array
            a[r]=board[x][r];
        }
        //check if there are repeated values
        int *count = (int *)calloc(sizeof(int), (board_size - 2));
        for(int i=0;i<board_size;i++){
            if(a[i] !=0){
                if(count[a[i]] == 1){
                    return true;
                }else{
                    count[a[1]]++;
                }
            }

        }
    }
    return false;
}


//check if unsolvable due to duplicate values in row, column
bool hasDupes(int **board, int board_size ,int subgrid_size){
    if(isDupeRow(board,board_size)==true && isDupeCol(board, board_size)==true){
        return true;
    }return false;
}

// Checks if number is already used in the row
bool usedInRow(int **board, int board_size, int row, int num){
    int col;
    for(col=0; col<board_size; col++){ //For-loop that traverses through the rows
        if(board[row][col] == num) return true; // Return true if number is found
    }
    return false;
}

// Checks if number is already used in the column
bool usedInCol(int **board, int board_size, int col, int num){
    int row;
    for(row=0; row<board_size; row++){ //For-loop that traverses through the columns
        if(board[row][col] == num) return true; // Return true if number is found
    }
    return false;
}

// Checks if number is already used in the grid
bool usedInBox(int **board, int subgrid_size, int boxStartRow, int boxStartCol, int num){
    int row, col;
    for(row=0; row<subgrid_size; row++){ // Traverse through the grid
        for(col=0; col<subgrid_size; col++){
            if(board[row+boxStartRow][col+boxStartCol] == num)
                return true; // Return true if number is found
        }
    }
    return false;
}
//Checks if sudoku x
bool isSudokuX(int **board, int board_size){
    int x,y,a1[board_size],a2[board_size];

    //put the numbers \ diagonal in an array
    for(x=0;x<board_size;x++){
        a1[x]=board[x][x];

    }
    //put the numbers in / diagonal in an array
    for(x=0;x<board_size;x++){
        a2[x]=board[x][board_size-(x+1)];
    }

    //check if numbers are repeating
    int *count = (int *)calloc(sizeof(int), (board_size - 2));
    int *count2 = (int *)calloc(sizeof(int), (board_size - 2));
    for(x=0;x<board_size;x++){
        if(count[a1[x]] == 1){
            return false;
        }else{

            count[a1[x]]++;
        }

    }
    for(y=0;y<board_size;y++){
        if(count2[a2[y]] == 1){
            return false;
        }else{
            count2[a2[y]]++;
        }

    }
    return true;
}
//Check if Sudoku Y
bool isSudokuY(int **board, int board_size){
    int half = (board_size/2);
    int x,a1[half],a2[half],b3[half+1];

    if(board_size % 2== 0){
        return false;
    }else{
        //put upper diagonals in an 2 diff arrays
        for(x=0;x<(half);x++){
            a1[x]=board[x][x];

        }

        for(x=0;x<(half);x++){
            a2[x]=board[(half)-(x+1)][half+(x+1)];
        }
        //put lower part of y in an array
        for(x=0;x<(half+1);x++){
            b3[x]=board[x+half][half];
        }



        //check if numbers are repeating
        int *count = (int *)calloc(sizeof(int), (board_size - 2));
        int *count2 = (int *)calloc(sizeof(int), (board_size - 2));

        //concat
        int* total1 = (int*)malloc(board_size * sizeof(int));
        int* total2 = (int*)malloc(board_size * sizeof(int));

        memcpy(total1,a1,(half)*sizeof(int));
        memcpy(total1 + half,b3,(half+1)*sizeof(int));

        memcpy(total2,a2,(half)*sizeof(int));
        memcpy(total2 + half,b3,(half+1)*sizeof(int));


        for(x=0;x<board_size;x++){
            if(count[total1[x]] == 1){
                return false;
            }else{
                count[total1[x]]++;
            }
        }

        for(x=0;x<board_size;x++){
            if(count2[total2[x]] == 1){
                return false;
            }else{
                count2[total2[x]]++;
            }
        }

        return true;

    }

}
bool isSudokuXY(int **board, int board_size){
    if(isSudokuX(board,board_size)==true && isSudokuY(board,board_size)==true){
        return true;
    }return false;
}

// Checks if number is safe to input to the board
bool isSafe(int **board, int board_size, int subgrid_size, int row, int col, int num){
    return !usedInRow(board, board_size, row, num) &&
                 !usedInCol(board, board_size, col, num) &&
                 !usedInBox(board, subgrid_size, row-row%subgrid_size, col-col%subgrid_size, num);
}

// Checks if the board is already complete
int findBlank(int **board, int board_size){
    int i, j, counter=0;
    for(i=0; i<board_size; i++){
        for(j=0; j<board_size; j++){
            if(board[i][j] == BLANK) counter++;
        }
    }

    return counter;
}

// Pop Function
void pop(NODE **head){
    if(*head!=NULL){//Checks if the list is not empty
        NODE *toDelete = *head; //Declares a pointer that points to the head
        *head = (*head)->next; //Points the head to the next node
        free(toDelete); //Deletes the node
    }
}

// Push Function
void push(NODE **head, int row, int col, int num){
    // Variable Declaration
    NODE *viewer = *head;

    if(*head == NULL){ //Checks if the list is empty
        *head = (NODE *) malloc(sizeof(NODE));
        (*head)->row = row;
        (*head)->col = col;
        (*head)->val = num;

        //Points the pointer to NULL to avoid dangling
        (*head)->next = NULL;
    }else{
        NODE *newnode = (NODE *) malloc(sizeof(NODE));
        newnode->row = row;
        newnode->col = col;
        newnode->val = num;

        newnode->next = viewer;
        *head = newnode;
    }
}

//Creates a function that views the contents of the linked list
void view(NODE **head){
    //Variable Declaration
    NODE *viewer = *head;
    if(viewer!=NULL){
        //Traverses the linked list until the tail is found
        while(viewer!=NULL){
            printf("%2d", viewer->val);
            viewer=viewer->next;
        }
    }
}

void printStacks(NODE **stacks, int stack_row_size){
    printf("\nSTACKS---------------------\n");
    for(int i=0; i<stack_row_size; i++){
        view(&stacks[i]);
        printf("\n");
    }
    printf("---------------------------\n");
}

void populate(int **board, NODE **stacks, int stack_row_size){
    NODE *viewer;

    // Populate the board using the Top of Stacks
    for(int l=0; l<stack_row_size; l++){
        viewer = stacks[l];
        if(viewer!=NULL){
            //Traverses the linked list until the tail is found
            while(viewer!=NULL){
                if(board[viewer->row][viewer->col] == 0)
                    board[viewer->row][viewer->col] = viewer->val;
                viewer=viewer->next;
            }
        }
    }
}

int backtrack(int **board, NODE **stacks, int stack_row_size, int board_size){
    // Populate the board using the Top of Stacks
    int l=0;
    for(l=stack_row_size-1; l>=0; l--){
        if(stacks[l]->next != NULL){
            board[stacks[l]->row][stacks[l]->col] = stacks[l]->next->val;
            // printf("popping head %d; replaced by %d\n", stacks[l]->val, stacks[l]->next->val);
            pop(&stacks[l]);
        }else if(stacks[l]->next == NULL){
            board[stacks[l]->row][stacks[l]->col] = 0;
            // printf("popping head %d\n", stacks[l]->val);
            pop(&stacks[l]);
        }
        if(stacks[l] != NULL) break; //Checks if there's a next value after popping
    }
    // printBoard(board, board_size); // Print the board
    return l; //return the index of last popped number
}


int **copy_board(int **board, int size) {
     int **copy = new int*[size];

     for (int row= 0; row< size; row++) {
         copy[row] = new int[size];

         for (int col = 0; col < size; col++) {
             copy[row][col] = board[row][col];
         }
     }

     return copy;
}


ANSWERS solve(int **board, int board_size, int subgrid_size, NODE **stacks, int stack_row_size, BoardSolutions *board_and_solutions){
    int stack_row=0;
    int safe=0; // Checker if there is a safe number detected
    int l=-1, i, j; // Iterators
    ANSWERS counters;
    counters.sudoku=0, counters.sudokuX=0, counters.sudokuY=0, counters.sudokuXY=0;


    do{
        stack_row=l+1;
        for(i=0; i<board_size; i++){
            for(j=0; j<board_size; j++){
                if(board[i][j] == BLANK){
                    for(int num=board_size; num>0; num--){
                        if(isSafe(board, board_size, subgrid_size, i, j, num)){
                            // Push to stack
//                            printf("pushing %d to stack %d, i: %d, j: %d\n", num, stack_row+1, i,j);
                            push(&stacks[stack_row], i, j, num);
                            // printBoard(board, board_size); // Print the board
//                            printStacks(stacks, stack_row_size);
                            safe++;
                        }
                    }
                    populate(board, stacks, stack_row_size); // Populate the board using Tops of Stacks
                    if(safe == 0){
                        // printf("No safe numbers found!\n");
                        // printf("premature backtrack\n");
                        stack_row = backtrack(board, stacks, stack_row, board_size);
//                        printStacks(stacks, stack_row_size);

                        if(stack_row >= 0 && stack_row <= stack_row_size){
                            i = stacks[stack_row]->row;
                            j = stacks[stack_row]->col;
                        }else{
                            return counters;
                        }
                    }
                    safe=0;
                    stack_row++;
                }
            }
        }
        counters.sudoku++; // Solution Found! Increment counter!
        printf("\nSolution %d Found!\n", counters.sudoku);

        if(isSudokuX(board, board_size) == true) counters.sudokuX++;
        if(isSudokuY(board, board_size) == true) counters.sudokuY++;
        if(isSudokuXY(board, board_size) == true) counters.sudokuXY++;

        printBoard(board, board_size); // Print the board

        // Add solution to solutions list
        board_and_solutions->solutions.append(copy_board(board, board_size));

//         printStacks(stacks, stack_row_size);
        l = backtrack(board, stacks, stack_row_size, board_size);
    }while(stacks[0]!=NULL);

    return counters;
}

QList<BoardSolutions> *load_and_solve(QString filename){

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

    // List of all boards and all their solutions
    QList<BoardSolutions> *all_boards_and_solutions = new QList<BoardSolutions>();


    // ------------------------------------------------------------------------------ //
    // ACCESSING INPUT FILE
    fp = fopen(filename.toStdString().c_str(), "r"); // File open

    if(!fp) {
        printf("FAILED TO OPEN FILE");
        return all_boards_and_solutions;
    }

    fscanf(fp, "%d\n", &num_of_boards); // Scans number of boards

    // Array for storing of answers
    ANSWERS *answers = (ANSWERS *) malloc(num_of_boards * sizeof(ANSWERS));
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

        printf("Scanned board:");
        printBoard(board, board_size);
    // ------------------------------------------------------------------------------ //

        /*
            The implementation of stack will be an array of linked list where:
                SIZE_OF_ARRAY == number of stacks or number of blank spaces on the board
                NUMBER_OF_NODES == max number of options or board size
            The Top Of Stack (TOS) is the first element of each row in the array.
        */

        stack_row_size = findBlank(board, board_size);
        stack_col_size = board_size;


        // <Board, List<Solutions>> Pair
        BoardSolutions *board_and_solutions = new BoardSolutions();

        // Save original puzzle
        board_and_solutions->board_size = board_size;
        board_and_solutions->board = copy_board(board, board_size);

        // Dynamically allocate the stacks
        stacks = (NODE **) malloc(stack_row_size * (sizeof(NODE*)));

        // Make stacks null
        for(int stack_index = 0; stack_index < stack_row_size; stack_index++) {
            stacks[stack_index] = NULL;
        }

        ANSWERS counters = solve(board, board_size, subgrid_size, stacks, stack_row_size, board_and_solutions);

        printf("Finished looking for solutions.\n\n");

        if(counters.sudoku == 0) {
            printf("No solutions found!\n");
        } else {
            printf("Number of solution/s found: %d\n", counters.sudoku);
        }

        destroy_int(board, board_size); // Free the board

        // printBoard(board, board_size); // Print the board
        // for(i=0; i<stack_row_size; i++) destroy_node(&stacks[i]); // Free the stacks

        all_boards_and_solutions->append(*board_and_solutions);

        num_of_boards--; // Decrementor
        answers[answer_iter++] = counters;
    }

    printf("\nNumber of Solutions for all Test Cases:\n");
    for(i=0; i<answer_iter; i++){
        printf("\nBoard: %d \nSudoku: %d \nSudokuX: %d \nSudokuY: %d \nSudokuXY: %d\n", i+1, answers[i].sudoku, answers[i].sudokuX, answers[i].sudokuY, answers[i].sudokuXY);
    }

    return all_boards_and_solutions;
}
