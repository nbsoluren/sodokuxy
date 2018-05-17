#include "sudokuwidget.h"
#include "ui_sudokuwidget.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QSizePolicy>
#include <QFont>
#include <QDebug>
#include <QList>
#include <QComboBox>
#include <QWidget>
#include <QMessageBox>

SudokuWidget::SudokuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SudokuWidget)
{
    ui->setupUi(this);

    // Setup sudoku widget contents on sudoku widget

//    // Setup sample puzzle
//    int *puzzle[3];
//    int row1[3] = {1, 2, 3};
//    int row2[3] = {2, 3, 1};
//    int row3[3] = {3, 1, 2};
//    puzzle[0] = row1;
//    puzzle[1] = row2;
//    puzzle[2] = row3;

    // Apply sample puzzle to UI
//    this->applySudoku(grid, (int**)puzzle, 3);
//    qDebug() << ui->boardList->currentText();
    this->sudokuLayout = new QGridLayout();
    ui->sudoku->setLayout(this->sudokuLayout);
}

SudokuWidget::~SudokuWidget()
{
    delete ui;
}


QList<QList<QPointer<QLineEdit>>> *SudokuWidget::setupSudoku(int n) {
    // 2D Array of QLineEdit pointers
    QLayoutItem *child;
    while ((child = this->sudokuLayout->takeAt(0)) != 0) {
        child->widget()->deleteLater();
    };

    SudokuGrid *grid = new SudokuGrid;

    for (int row = 0; row < n; row++) {
        QList<QPointer<QLineEdit>> column;

        for (int col = 0; col < n; col++) {
            QLineEdit *line_edit = new QLineEdit();

            // Setup line editor font/style and validator
            line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            line_edit->setAlignment(Qt::AlignHCenter);
            line_edit->setText("1");
            line_edit->setFont(QFont("sans", 16));
            line_edit->setValidator(new QIntValidator(1, 9));

            this->sudokuLayout->addWidget(line_edit, row, col);
            column.append(line_edit);
        }

        grid->append(column);
    }

    return grid;
}

void SudokuWidget::applySudoku(SudokuGrid *grid, int **puzzle, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Blank editable string if 0, otherwise the number as string as read only
            if (puzzle[row][col] == 0) {
                grid->at(row)[col]->setText("");
                grid->at(row)[col]->setReadOnly(false);
            } else {
                grid->at(row)[col]->setText(QString::number(puzzle[row][col]));
                grid->at(row)[col]->setReadOnly(true);
            }

        }
    }
}

void SudokuWidget::on_load_puzzle_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                            this,
                            tr("Open File"),
                            "~/Desktop", //default folder you wan to open
                            "All files (*.*);;Boards (*.in)"
                            );

    this->current_boards_and_solutions = load_and_solve(filename);

    ui->boardList->clear();
    this->current_solution = -1;


    int index = 0;
    for(BoardSolutions board: *this->current_boards_and_solutions) {
        QString message = " Board " + QString::number(++index) + " (" + QString::number(board.solutions.size()) + " sols)";
        ui->boardList->addItem(message);
    }
}

void SudokuWidget::on_boardList_currentIndexChanged(int index)
{
    if(index >= this->current_boards_and_solutions->size() || index < 0) {
        return;
    }

    this->current_board = this->current_boards_and_solutions->at(index);
    this->current_solution = 0;

    this->grid = this->setupSudoku(this->current_board.board_size);
    this->applySudoku(this->grid, this->current_board.board, this->current_board.board_size);
}

void SudokuWidget::on_solve_clicked()
{
    this->current_solution = 0;

    if(this->current_solution >= this->current_board.solutions.size()) {
        QMessageBox::warning(0, "No solution", "There is no solution for current puzzle.");
        return;
    }

    this->applySudoku(this->grid, this->current_board.solutions.at(this->current_solution), this->current_board.board_size);
    bool boolX = isSudokuX(current_board.board, current_board.board_size);
    bool boolY = isSudokuY(current_board.board, current_board.board_size);
    bool boolXY = isSudokuXY(current_board.board, current_board.board_size);
    QString X = boolX? "true" : "false";
    QString Y = boolY? "true" : "false";
    QString XY = boolXY? "true" : "false";
    ui->status->setText("SudokuX: "+ X + "   SudokuY: "+ Y + "    SudokuXY: "+ XY);
}

void SudokuWidget::on_next_clicked()
{
    if(this->current_solution+1 >= this->current_board.solutions.size()) {
        QMessageBox::warning(0, "No solution", "There is no more solution for current puzzle.");
        return;
    }

    this->current_solution++;
    this->applySudoku(this->grid, this->current_board.solutions.at(this->current_solution), this->current_board.board_size);
    bool boolX = isSudokuX(current_board.board, current_board.board_size);
    bool boolY = isSudokuY(current_board.board, current_board.board_size);
    bool boolXY = isSudokuXY(current_board.board, current_board.board_size);
    QString X = boolX? "true" : "false";
    QString Y = boolY? "true" : "false";
    QString XY = boolXY? "true" : "false";
    ui->status->setText("SudokuX: "+ X + "   SudokuY: "+ Y + "    SudokuXY: "+ XY);
}

void SudokuWidget::on_previous_clicked()
{
    if(this->current_solution-1 < 0) {
        QMessageBox::warning(0, "No solution", "There is no more solution for current puzzle.");
        return;
    }

    this->current_solution--;
    this->applySudoku(this->grid, this->current_board.solutions.at(this->current_solution), this->current_board.board_size);
    bool boolX = isSudokuX(current_board.board, current_board.board_size);
    bool boolY = isSudokuY(current_board.board, current_board.board_size);
    bool boolXY = isSudokuXY(current_board.board, current_board.board_size);
    QString X = boolX? "true" : "false";
    QString Y = boolY? "true" : "false";
    QString XY = boolXY? "true" : "false";
    ui->status->setText("SudokuX: "+ X + "   SudokuY: "+ Y + "    SudokuXY: "+ XY);
}
