// ---------------------------------------------------------------------------------- //
// CONSTANTS
#define BLANK 0
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //
// STRUCTURE
typedef struct node{
    int row;
    int col;
    int val;
}NODE;
// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //
// FUNCTIONS

// Function that prints a Matrix
void printBoard(int **board, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			printf("%2d ", *(*(board+i)+j));
		}
		printf("\n");
	}
}

// Frees dynamically allocated board
void destroy(int **board, int board_size){
  for(int i=0; i<board_size; i++){
    int *currentIntPtr = board[i];
    free(currentIntPtr);
  }
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
void pop(NODE stack[], int stack_size){
	int i, val = stack[0].val; // Get TOS
	for(i=1; i<stack_size-1; i++){ // Move elements of the stack to the left
		stack[i-1] = stack[i];
	}
}

// Push Function
void push(NODE stack[], int index, int num){
	stack[index].val = num;
}

void fillUp(){

}

// ---------------------------------------------------------------------------------- //

void printMatrix(NODE **matrix, int row, int col){
	int i, j;

	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%d ", (matrix[i][j]).val);
		}
		printf("\n");
	}
}