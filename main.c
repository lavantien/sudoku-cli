#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/* ================================ GLOBAL ================================ */

typedef struct {
    int rowStart;
    int colStart;
} Square;

static int board[9][9];
static int tempBoard[9][9];
static bool isUnsolvedCell[9][9];
static int possibility[9][9][9];
static int possibilitySize[9][9];
static int debugRepCount;
static int maxPossibilitySize;

/* =============================== PROTOTYPE ============================== */

bool checkRow(const int num, const int row);
bool checkCol(const int num, const int col);
bool checkSquare(const int num, const int row, const int col);
Square getCurrSquare(const int row, const int col);
void solve(void);
bool preSolve(void);
bool resolver(const int num, const int i, const int j);
bool isNaturalNumber(const char c);
void resetTempBoard(void);
void printReadable(void);
void debugPrintIntArray(const char* str, const int* arr, const int size);
void debugPrintPossibilityTable(void);

/* ================================= MAIN ================================= */

int main(int argc, char** argv) {
    if (argc > 1 && strncmp(argv[1], "0", 1) == 0) {
        for (int i = 0; i < 9 * 9; ++i) {
            if (isNaturalNumber(argv[2][i])) {
                board[i / 9][i % 9] = tempBoard[i / 9][i % 9] = argv[2][i] - 48;
            }
        }
        puts("\nOriginal state:");
        printReadable();
        clock_t start = clock();
        solve();
        clock_t end = clock();
        double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        puts("Solved state:");
        printReadable();
        printf("Rep count: %d\n", debugRepCount);
        printf("Time spent solving: %lfs\n", cpuTimeUsed);
    } else if (argc > 1) {
        switch (argv[1][0]) {
        case '1':
            puts("Easy difficulty!");
            break;
        case '2':
            puts("Medium difficulty!");
            break;
        case '3':
            puts("Hard difficulty!");
            break;
        case '4':
            puts("Extreme difficulty!");
            break;
        default:
            puts("Haven't implemented yet!");
            break;
        }
    } else {
        puts("\nmain <selection> [...]");
        puts("\nselection:");
        puts("\n0: solve input sudoku.");
        puts("Command: main 0 <one line sudoku with `.` as empty cell>\n");
        puts("1 -> 4: generate sudoku with appropriate difficulty.");
        puts("Command: main 2 [<format selection>]\n");
        puts("\tformat selection:");
        puts("\t0 or default: readable");
        puts("\t1 or others: oneline\n");
    }
    return 0;
}

/* ============================ IMPLEMENTATION ============================ */

bool checkRow(const int num, const int row) {
    for (int j = 0; j < 9; ++j) {
        if (num == board[row][j]) {
            // DEBUG
            // printf("-row%d%d %d\n", row, j, num);
            return false;
        }
    }
    return true;
}

bool checkCol(const int num, const int col) {
    for (int i = 0; i < 9; ++i) {
        if (num == board[i][col]) {
            // DEBUG
            // printf("-col%d%d %d\n", i, col, num);
            return false;
        }
    }
    return true;
}

bool checkSquare(const int num, const int row, const int col) {
    Square currSquare = getCurrSquare(row, col);
    for (int i = currSquare.rowStart; i < currSquare.rowStart + 3; ++i) {
        for (int j = currSquare.colStart; j < currSquare.colStart + 3; ++j) {
            if (num == board[i][j]) {
                // DEBUG
                // printf("-square%d%d %d\n", i, j, num);
                return false;
            }
        }
    }
    return true;
}

Square getCurrSquare(const int row, const int col) {
    Square currSquare;
    currSquare.rowStart = row / 3 * 3;
    currSquare.colStart = col / 3 * 3;
    return currSquare;
}

void solve(void) {
    printf("\n%s\n\n", "Solving... It may take a while!");
    bool isSolved = preSolve();
    if (!isSolved) {

    }
}

bool preSolve(void) {
    for (;;) {
        ++debugRepCount;
        int countEmptyCell = 0;
        int countSolvedCell = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    ++countEmptyCell;
                    isUnsolvedCell[i][j] = true;
                    possibilitySize[i][j] = 0;
                    for (int k = 1; k <= 9; ++k) {
                        if (checkRow(k, i) && checkCol(k, j) &&
                            checkSquare(k, i, j)) {
                            possibility[i][j][possibilitySize[i][j]++] = k;
                        }
                    }
                    if (possibilitySize[i][j] > maxPossibilitySize) {
                        maxPossibilitySize = possibilitySize[i][j];
                    }
                    if (possibilitySize[i][j] == 1) {
                        ++countSolvedCell;
                        isUnsolvedCell[i][j] = false;
                        board[i][j] = tempBoard[i][j] = possibility[i][j][0];
                        // DEBUG
                        // printf("--(%d,%d)=%d\n", i, j,
                        //     possibility[i][j][0]);
                    }
                    // DEBUG
                    // char str[30];
                    // sprintf(str, "(%d,%d) ", i, j);
                    // debugPrintIntArray(str, possibility[i][j],
                    //     possibilitySize[i][j]);
                }
            }
        }
        // DEBUG
        debugPrintPossibilityTable();
        if (countEmptyCell == 0) {
            return true;
        } else if (countEmptyCell > countSolvedCell && countSolvedCell == 0) {
            return false;
        }
    }
}

bool resolver(const int num, const int i, const int j) {
    resetTempBoard();
    return false;
}

bool isNaturalNumber(const char c) {
    if (c >= 49 && c <= 57) {
        return true;
    }
    return false;
}

void resetTempBoard(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; ++j) {
            if (isUnsolvedCell[i][j]) {
                tempBoard[i][j] = 0;
            }
        }
    }
}

void printReadable(void) {
    putchar('\n');
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (isNaturalNumber(board[i][j] + 48)) {
                printf(" %d", board[i][j]);
            } else {
                printf(" %c", '.');
            }
            if (j % 3 == 2 && j != 8) {
                printf(" %c", '|');
            }
        }
        putchar('\n');
        if (i % 3 == 2 && i != 8) {
            printf("%s\n", "-------|-------|-------");
        }
    }
    putchar('\n');
}

void debugPrintIntArray(const char* str, const int* arr, const int size) {
    printf("%s", str);
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

void debugPrintPossibilityTable(void) {
    printf("Rep %d - Possibility table:\n\n", debugRepCount);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            putchar('(');
            if (possibilitySize[i][j] > 1) {
                for (int k = 0; k < possibilitySize[i][j] - 1; ++k) {
                    printf("%d ", possibility[i][j][k]);
                }
            }
            if (possibilitySize[i][j] != 0) {
                printf("%d", possibility[i][j][possibilitySize[i][j] - 1]);
            }
            if (possibilitySize[i][j] < maxPossibilitySize) {
                for (int h = possibilitySize[i][j] != 0 ? possibilitySize[i][j] : 1; h < maxPossibilitySize; ++h) {
                    if (possibilitySize[i][j] == 0) {
                        printf("%s", "--");
                    } else {
                        printf("%s", "  ");
                    }
                }
                if (possibilitySize[i][j] == 0) {
                    putchar('-');
                }
            }
            printf("%s", ") ");
            if (j % 3 == 2 && j != 8) {
                printf("%c ", 186);
            }
        }
        putchar('\n');
        if (i % 3 == 2 && i != 8) {
            for (int h = 0; h < ((maxPossibilitySize + 1) * 2) * 9 + 3; ++h) {
                if (h == ((maxPossibilitySize + 1) * 2) * 3 ||
                    h == ((maxPossibilitySize + 1) * 2) * 6 + 2) {
                    putchar(206);
                } else {
                    putchar(205);
                }
            }
            putchar('\n');
        }
    }
    putchar('\n');
}

/*
COMPLETED:
- Solved simple sudokus
*/

/*
TODO:
- Figure out how to solve a easy+ sudoku, maybe A* search?
- Starting from a cell which has least number of possibility?
*/

/*
LINKS:
- https://qqwing.com/generate.html
- https://www.learn-sudoku.com/basic-techniques.html
*/
