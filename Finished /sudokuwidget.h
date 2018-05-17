#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPointer>
#include <QList>
#include <QGridLayout>
#include "sudokusolver.h"

typedef QList<QList<QPointer<QLineEdit>>> SudokuGrid;

namespace Ui {
class SudokuWidget;
}

class SudokuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuWidget(QWidget *parent = 0);
    ~SudokuWidget();
    int numberofboards;

private slots:
    void on_load_puzzle_clicked();

    void on_boardList_currentIndexChanged(int index);

    void on_solve_clicked();

    void on_next_clicked();

    void on_previous_clicked();

private:
    Ui::SudokuWidget *ui;
    QList<QList<QPointer<QLineEdit> > > *setupSudoku(int n);
    void applySudoku(SudokuGrid *grid, int **puzzle, int n);
    QList<BoardSolutions> *current_boards_and_solutions;
    SudokuGrid *grid;
    QGridLayout *sudokuLayout;

    BoardSolutions current_board;
    int current_solution = -1;
};

#endif // SUDOKUWIDGET_H
