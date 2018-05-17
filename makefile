files = sudoku.c v1sudoku.c

sudoku: $(files)
		gcc -o sudoku sudoku.c
		./sudoku
		rm -f sudoku
v1sudoku: $(files)
		gcc -o v1sudoku v1sudoku.c
		./v1sudoku
		rm -f v1sudoku
clean:
		rm -f sudoku
