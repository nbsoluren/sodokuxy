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

// ---------------------------------------------------------------------------------- //
