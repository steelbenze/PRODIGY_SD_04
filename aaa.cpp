#include <bits/stdc++/h>
using namespace std;

// Size of the Sudoku grid
const int N = 9;

// Function prototypes
bool findUnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
void printGrid(int grid[N][N]);

int main() {
    // Example Sudoku grid
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved successfully!" << endl;
        cout << "Solution:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle!" << endl;
    }

    return 0;
}

// Searches the grid to find an entry that is still unassigned
bool findUnassignedLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Checks whether it will be legal to assign num to the given row,col location
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if num is not already present in current row, current column, and current 3x3 subgrid
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num || grid[(row - row % 3) + (x / 3)][(col - col % 3) + (x % 3)] == num) {
            return false;
        }
    }
    return true;
}

// Recursively solves the Sudoku puzzle
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there are no unassigned locations, Sudoku puzzle is solved
    if (!findUnassignedLocation(grid, row, col)) {
        return true; // Success
    }

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if it's safe to place the digit in the current position
        if (isSafe(grid, row, col, num)) {
            // Assign the digit to the current location
            grid[row][col] = num;

            // If it leads to a solution, return true
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing the current digit doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no digit can be placed in the current location, return false
    return false;
}

// Prints the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}
