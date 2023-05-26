#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isNumberInRow(const vector<vector<int>>& grid, int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool isNumberInColumn(const vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {
    return !isNumberInRow(grid, row, num) && !isNumberInColumn(grid, col, num);
}

bool isValidUser(const vector<vector<int>>& grid, int row, int col, int num, const unordered_set<int>& userMoves) {
    return grid[row][col] == 0 || userMoves.count(row * 9 + col) > 0;
}

void generateGrid(vector<vector<int>>& grid) {
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        int count = rand() % 3 + 1; // Número de elementos a serem gerados nesta linha
        int generated = 0; // Número de elementos gerados até agora
        while (generated < count) {
            int j = rand() % 9; // Coluna aleatória

            int num;
            do {
                num = rand() % 9 + 1; // Número aleatório
            } while (!isValid(grid, i, j, num));

            grid[i][j] = num;
            generated++;
        }
    }
}

void removePreviousMove(vector<vector<int>>& grid, int row, int col) {
    if (row >= 0 && row < 9 && col >= 0 && col < 9 && grid[row][col] != 0) {
        grid[row][col] = 0;
    }
}

bool checker(const vector<vector<int>>& grid, int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == grid[row][col] && i != col) {
            return true;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == grid[row][col] && i != row) {
            return true;
        }
    }

    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grid[i][j] == grid[row][col] && (i != row || j != col)) {
                return true;
            }
        }
    }

    return false;
}

void removeElement(vector<vector<int>>& grid, int row, int col, unordered_set<int>& userMoves) {
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        int position = row * 9 + col;
        if (grid[row][col] == 0) {
            cout << "Position (" << row + 1 << ", " << col + 1 << ") is already empty." << endl;
        } else if (userMoves.count(position) > 0) {
            grid[row][col] = 0;
            userMoves.erase(position);
            cout << "Element at position (" << row + 1 << ", " << col + 1 << ") removed." << endl;
        } else {
            cout << "Cannot remove a number generated by the program or inserted by the user." << endl;
        }
    } else {
        cout << "Invalid position." << endl;
    }
}

int main() {
    vector<vector<int>> grid(9, vector<int>(9));
    unordered_set<int> userMoves; // Positions where the user inserted numbers
    generateGrid(grid);

    cout << "Sudoku Game" << endl << endl;

    int previousRow = -1;
    int previousCol = -1;

    while (true) {
        int choice;
        printGrid(grid);
        cout << endl << "1. Insert number\n2. Remove previous move\n3. Remove element at position\n4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int row, col, num;
            cout << "Enter row & col (space-separated): ";
            cin >> row >> col;

            cout << "Number (1-9): ";
            cin >> num;
            cout << endl;

            if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
                cout << "Invalid input! Please try again." << endl;
                continue;
            }

            if (!isValidUser(grid, row - 1, col - 1, num, userMoves)) {
                cout << "Invalid move! Please try again." << endl;
                continue;
            }

            grid[row - 1][col - 1] = num;
            previousRow = row - 1;
            previousCol = col - 1;
            userMoves.insert((row - 1) * 9 + (col - 1));

            // Check if the game is won
            bool gameWon = true;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (grid[i][j] == 0) {
                        gameWon = false;
                        break;
                    }
                }
            }

            if (gameWon) {
                cout << "Congratulations! You won the game." << endl;
                break;
            }
        } else if (choice == 2) {
            if (previousRow != -1 && previousCol != -1) {
                removePreviousMove(grid, previousRow, previousCol);
                previousRow = -1;
                previousCol = -1;
                cout << "Previous move removed." << endl;
            } else {
                cout << "No previous move found." << endl;
            }
        } else if (choice == 3) {
            int row, col;
            cout << "Enter row & col (space-separated): ";
            cin >> row >> col;
            cout << endl;
            removeElement(grid, row - 1, col - 1, userMoves);
        } else if (choice == 4) {
            exit(0);
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
