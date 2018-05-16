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

// HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "natalie.h"

//constants
#define BLANK 0
#define N 4

bool inRow(int *board, int boardsize, int row, int num){
  int i;
  for(i = N*(row-1); i<(N*row)-1; i+=N)
    if(num == board[i]) return true;
  return false;
}

bool inCol(int *board, int boardsize, int col, int num){
  int i;
  for(i = col-1; i<(col-1)+(N*(N-1)); i+=N)
    if(num == board[i]) return true;
  return false;
}

bool inBox(int *board, int boardsize, int boxr, int boxc, int num){
  int i;
  // for( i = box-1; i<(box-1)+sqrt(N)-1; i++)
  //   if(num == board[i]) return true;
  // for( i = box-1+N; i<(box-1)+N+sqrt(N)-1; i++)
  //   if(num == board[i]) return true;
  // return false;
  for( i = 0; i<sqrt(N); i++)
    if(num == board[i+boxr]) return true;
  for( i = 0; i<sqrt(N); i++)
    if(num == board[i+boxc+N]) return true;
  return false;
}


bool isOk(int *board, int boardsize, int i, int num){
  int row = (int) ceilf((i+1)/(float)N);
  int col = ((i+1)%N == 0) ? N: (i+1)%4;
  int subg= sqrt(N);
  return !inRow(board, boardsize, row, num) &&
         !inCol(board, boardsize, col, num) &&
         !inBox(board, boardsize, row-row%subg,col-col%subg, num);
}

void fillZero(int *board, int boardsize){
  int i;
  for(i =0; i<N*N; i++){
    board[i] = 0;
  }
}

void displayBoard(int *board, int boardsize){
  int i;
  for(i =0; i<N*N; i++){
    printf("%d ", board[i]);
  }
  printf("\n");

}






//main Function
int main(){
  int board[N*N];
  fillZero(board,N*N);
  displayBoard(board, N*N);
  if(isOk(board, N, 5, 3)) board[5] = 3;
  displayBoard(board, N*N);
  if(isOk(board, N, 0, 3)) board[0] = 3;
  else printf("nope.\n");
  displayBoard(board, N*N);
  if(isOk(board, N, 4, 3)) board[4] = 3;
  else printf("nope.\n");
  displayBoard(board, N*N);



  return 0;

}
