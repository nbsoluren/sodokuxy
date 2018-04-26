files = sudoku.c

sudoku: $(files)
		gcc -o sudoku sudoku.c
		./sudoku
		rm -f sudoku
clean:
		rm -f sudoku
