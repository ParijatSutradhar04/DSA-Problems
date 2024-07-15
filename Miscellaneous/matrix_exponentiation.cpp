#include<bits/stdc++.h>
using namespace std;

int** multiply(int **A, int **B, int rA, int cA, int rB, int cB) {
    int **C = new int*[rA];
    for (int i=0; i<rA; i++) {
        C[i] = new int[cB];
    }

    if (cA != rB) {
        cout << "Multiplication not possible" << endl;
        return C;
    }

    for (int i=0; i<rA; i++) {
        for (int j=0; j<cB; j++) {
            int p = 0;
            for (int k=0; k<cA; k++) {
                p += A[i][k] * B[k][j];
            }
            C[i][j] = p;
        }
    }
    return C;
}

int **power(int **A, int n, int rA, int cA) {
    if (n == 1) {
        return A;
    }
    int **C = power(A, n/2, rA, cA);
    if (n%2 == 0) {
        return multiply(C, C, rA, cA, rA, cA);
    }
    else {
        return multiply(A, multiply(C, C, rA, cA, rA, cA), rA, cA, rA, cA);
    }
}

int* fibonacci(int n) {
    int **Q = new int*[2];
    for (int i=0; i<2; i++) {
        Q[i] = new int[2];
        if (i == 0) {
            Q[i][0] = 1;
            Q[i][1] = 1;
        }
        else {
            Q[i][0] = 1;
            Q[i][1] = 0;
        }
    }
    int **Qn = power(Q, n-1, 2, 2);
    int *F = new int[3];
    F[0] = Qn[0][0];
    F[1] = Qn[0][1];
    F[2] = Qn[1][1];
    return F;
}

void matrixMultiplication() {
    cout<<"Enter the number of rows and columns of matrix A: ";
    int rA, cA;
    cin >> rA >> cA;
    cout<<"Enter the number of rows and columns of matrix B: ";
    int rB, cB;
    cin >> rB >> cB;

    int **A = new int*[rA];
    int **B = new int*[rB];
    for (int i=0; i<rA; i++) {
        A[i] = new int[cA];
    }
    for (int i=0; i<rB; i++) {
        B[i] = new int[cB];
    }

    cout << "Enter the elements of matrix A: " << endl;
    for (int i=0; i<rA; i++) {
        for (int j=0; j<cA; j++) {
            cin >> A[i][j];
        }
    }
    cout << "Enter the elements of matrix B: " << endl;
    for (int i=0; i<rB; i++) {
        for (int j=0; j<cB; j++) {
            cin >> B[i][j];
        }
    }

    // Print A and B
    cout << "Matrix A: " << endl;
    for (int i=0; i<rA; i++) {
        for (int j=0; j<cA; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix B: " << endl;
    for (int i=0; i<rB; i++) {
        for (int j=0; j<cB; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    int **C = multiply(A, B, rA, cA, rB, cB);
    cout << "The product of the two matrices is: " << endl;
    for (int i=0; i<rA; i++) {
        for (int j=0; j<cB; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}
 
int main(){
    // matrixMultiplication();
    int n;
    cout << "Enter the number: ";
    cin >> n;
    int *F = fibonacci(n);
    cout << "The fibonacci of " << n + 1 << " is: " << F[0] << endl;
    cout << "The fibonacci of " << n << " is: " << F[1] << endl;
    cout << "The fibonacci of " << n - 1 << " is: " << F[2] << endl;
    return 0;
}
