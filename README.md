# sudoku-cli
A CLI tool for creating and solving sudoku at any difficulty.

#### Build:
Run `make` in terminal.

#### Run:
Run `./main` in terminal.

main {selection} [...]

selection:

0: solve input sudoku.
Command: main 0 <one line sudoku with `.` as empty cell>

1 -> 4: generate sudoku with appropriate difficulty.
Command: main 2 [{format selection}]

        format selection:
        0 or default: readable
        1 or others: oneline
