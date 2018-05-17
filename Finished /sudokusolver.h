#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QList>
#include <QPair>
#include <QString>

#define BLANK 0


// STRUCTURE
typedef struct node {
    int row;
    int col;
    int val;
    struct node *next;
} NODE;

typedef struct answers{
    int sudoku;
    int sudokuX;
    int sudokuY;
    int sudokuXY;
} ANSWERS;

typedef struct board_and_solutions{
    int board_size;
    int** board;
    QList<int**> solutions;
} BoardSolutions;


QList<BoardSolutions> *load_and_solve(QString filename);
bool isSudokuX(int **board, int board_size);
bool isSudokuY(int **board, int board_size);
bool isSudokuXY(int **board, int board_size);

#endif // SUDOKUSOLVER_H
