#include<bits/stdc++.h>
using namespace std;

void init(char **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
}

void print(char **board, int n) {
    static int count = 0;
    cout << "Solution " << ++count << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool check(char **board, int n, int row, int col) {
    // check row
    for (int i = 0; i < n; i++) {
        if (board[row][i] == 'Q') {
            return false;
        }
    }
    
    // check col
    for (int i = 0; i < n; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // check lower left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // check lower right diagonal
    for (int i = row, j = col; i < n && j < n; i++, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void n_queen(char **board, int n, int row) {
    if (row == n) {
        print(board, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (check(board, n, row, col)) {
            board[row][col] = 'Q';
            n_queen(board, n, row+1);
            board[row][col] = '.';
        }
    }
}

// Optimized solution to print only one solution of n-queen problem
void n_queen(char **board, int n, int row, int col) {
    if (row == n) {
        print(board, n);
        return;
    }

    if (col == n) {
        return;
    }

    if (check(board, n, row, col)) {
        board[row][col] = 'Q';
        n_queen(board, n, row+1, 0);
        board[row][col] = '.';
    }

    n_queen(board, n, row, col+1);
}
 
int main(){
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    char **board = new char*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new char[n];
    }
    init(board, n);
    n_queen(board, n, 0);

    return 0;
}
