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
	struct node *next;
}NODE;
// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //
// FUNCTIONS

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
		int* total1 = malloc(board_size * sizeof(int));
		int* total2 = malloc(board_size * sizeof(int));

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
		//Traverses the linked list to find the tail
		NODE *newnode = (NODE *) malloc(sizeof(NODE));
		newnode->row = row;
		newnode->col = col;
		newnode->val = num;

		// Connects the new node to the tail of the linked list
		// viewer->next = newnode;
		//Points the pointer to NULL to avoid dangling
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
// ---------------------------------------------------------------------------------- //
