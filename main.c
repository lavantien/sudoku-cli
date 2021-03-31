#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define SUBGRID_COUNT 3
#define BOARD_SIZE 9
#define GRID_LENGTH BOARD_SIZE

static int grid[BOARD_SIZE][BOARD_SIZE];
static int originalGrid[BOARD_SIZE][BOARD_SIZE];
static bool isUnsolvedCell[BOARD_SIZE][BOARD_SIZE];
static int possibility[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
static int possibilitySize[BOARD_SIZE][BOARD_SIZE];
static int maxPossibilitySize;
static int recursiveCount;
static int preSolveCount;

bool isFillable(const int x, const int y, const int k);
bool basicBacktracking(int x, int y);
void basicSolver(void);
bool preSolve(void);

int main(int argc, char** argv) {
	char temp[257];
	gets_s(temp, 257);
	int mode = atoi(temp);
	switch (mode) {
		case 1:
			for (int i = 0; i < BOARD_SIZE; ++i) {
				char row[BOARD_SIZE + 1];
				gets_s(row, BOARD_SIZE + 1);
				for (int j = 0; j < BOARD_SIZE; ++j) {
					char c = row[j];
					grid[i][j] = c == '.' ? 0 : c - '0';
				}
			}
			break;
		default:
			char stringOneLine[BOARD_SIZE * BOARD_SIZE + 1];
			gets_s(stringOneLine, BOARD_SIZE * BOARD_SIZE + 1);
			for (int i = 0; i < BOARD_SIZE; ++i) {
				for (int j = 0; j < BOARD_SIZE; ++j) {
					char c = stringOneLine[i * BOARD_SIZE + j];
					grid[i][j] = c == '.' ? 0 : c - '0';
				}
			}
			break;
	}
	memcpy(originalGrid, grid, sizeof originalGrid);

	clock_t start = clock();
	basicSolver();
	clock_t end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC;

	putchar('\n');
	switch (mode) {
		case 0:
		case 1:
			for (int i = 0; i < BOARD_SIZE; ++i) {
				for (int j = 0; j < BOARD_SIZE; ++j) {
					putchar(originalGrid[i][j] == 0 ? '.' : originalGrid[i][j] + '0');
					if (j == 2 || j == 5) {
						putchar('|');
					}
				}
				putchar('\n');
				if (i == 2 || i == 5) {
					puts("___ ___ ___");
				}
			}
			putchar('\n');
			for (int i = 0; i < BOARD_SIZE; ++i) {
				for (int j = 0; j < BOARD_SIZE; ++j) {
					putchar(grid[i][j] == 0 ? '.' : grid[i][j] + '0');
					if (j == 2 || j == 5) {
						putchar('|');
					}
				}
				putchar('\n');
				if (i == 2 || i == 5) {
					puts("___ ___ ___");
				}
			}
			printf("\nPre-solve count: %d\n", preSolveCount);
			printf("Recursive count: %d\n", recursiveCount);
			printf("Execution time: %lf\n", duration);
			break;
//			default:
//				for (int i = 0; i < BOARD_SIZE; ++i) {
//					for (int j = 0; j < BOARD_SIZE; ++j) {
//						putchar(grid[i][j]);
//					}
//				}
//				putchar('\n');
//				break;
	}

	return 0;
}

bool preSolve(void) {
    for (;;) {
        ++preSolveCount;
        int countEmptyCell = 0;
        int countSolvedCell = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (grid[i][j] == 0) {
                    ++countEmptyCell;
                    isUnsolvedCell[i][j] = true;
                    possibilitySize[i][j] = 0;
                    for (int k = 1; k <= BOARD_SIZE; ++k) {
                        if (isFillable(i, j, k)) {
                            possibility[i][j][possibilitySize[i][j]++] = k;
                        }
                    }
                    if (possibilitySize[i][j] > maxPossibilitySize) {
                        maxPossibilitySize = possibilitySize[i][j];
                    }
                    if (possibilitySize[i][j] == 1) {
                        ++countSolvedCell;
                        isUnsolvedCell[i][j] = false;
                        grid[i][j] = possibility[i][j][0];
                    }
                }
            }
        }

        if (countEmptyCell == 0) {
            return true;
        } else if (countEmptyCell > countSolvedCell && countSolvedCell == 0) {
            return false;
        }
    }
}

bool isFillable(const int x, const int y, const int k) {
	for (int i = 0; i < GRID_LENGTH; ++i) {
		int gridX = x / SUBGRID_COUNT * SUBGRID_COUNT + i / SUBGRID_COUNT;
		int gridY = y / SUBGRID_COUNT * SUBGRID_COUNT + i % SUBGRID_COUNT;
		if ((i != y && k == grid[x][i]) ||
				(i != x && k == grid[i][y]) ||
				(x != gridX && y != gridY && k == grid[gridX][gridY])) {
			return false;
		}
	}
	return true;
}

bool basicBacktracking(int x, int y) {
	++recursiveCount;
	if (y == GRID_LENGTH) {
		++x;
		y = 0;
		if (x == GRID_LENGTH) {
			return true;
		}
	}

	if (!isUnsolvedCell[x][y]) {
		return basicBacktracking(x, y + 1);
	} else {
		for (int k = 0; k < possibilitySize[x][y]; ++k) {
			if (isFillable(x, y, possibility[x][y][k])) {
				grid[x][y] = possibility[x][y][k];
				if (basicBacktracking(x, y + 1)) {
					return true;
				}
			}
		}
		grid[x][y] = 0;
	}

	return false;
}

void basicSolver(void) {
	preSolve();
	basicBacktracking(0, 0);
}
