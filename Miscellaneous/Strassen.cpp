// Strassen's algorithm for matrix multiplication
// Time complexity: O(n^2.81)

#include<bits/stdc++.h> 
using namespace std;

int** addMatrix(int** A, int** B, int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

int** subtractMatrix(int** A, int** B, int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }

    return result;
}

int** strassenMultiply(int** A, int** B, int n) {
    if (n == 1) {
        int** result = new int*[1];
        result[0] = new int[1];
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    // Split matrices into quadrants
    int mid = n / 2;
    int** a11 = new int*[mid];
    int** a12 = new int*[mid];
    int** a21 = new int*[mid];
    int** a22 = new int*[mid];
    int** b11 = new int*[mid];
    int** b12 = new int*[mid];
    int** b21 = new int*[mid];
    int** b22 = new int*[mid];

    for (int i = 0; i < mid; i++) {
        a11[i] = new int[mid];
        a12[i] = new int[mid];
        a21[i] = new int[mid];
        a22[i] = new int[mid];
        b11[i] = new int[mid];
        b12[i] = new int[mid];
        b21[i] = new int[mid];
        b22[i] = new int[mid];
    }

    // Dividing the matrices in 4 sub-matrices:
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + mid];
            a21[i][j] = A[i + mid][j];
            a22[i][j] = A[i + mid][j + mid];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + mid];
            b21[i][j] = B[i + mid][j];
            b22[i][j] = B[i + mid][j + mid];
        }
    }

    // Calculating sub matrices for Strassen's products:
    int** s1 = subtractMatrix(b12, b22, mid); // s1 = b12 - b22
    int** s2 = addMatrix(a11, a12, mid); // s2 = a11 + a12
    int** s3 = addMatrix(a21, a22, mid); // s3 = a21 + a22
    int** s4 = subtractMatrix(b21, b11, mid); // s4 = b21 - b11
    int** s5 = addMatrix(a11, a22, mid); // s5 = a11 + a22
    int** s6 = addMatrix(b11, b22, mid); // s6 = b11 + b22
    int** s7 = subtractMatrix(a12, a22, mid); // s7 = a12 - a22
    int** s8 = addMatrix(b21, b22, mid); // s8 = b21 + b22
    int** s9 = subtractMatrix(a11, a21, mid); // s9 = a11 - a21
    int** s10 = addMatrix(b11, b12, mid); // s10 = b11 + b12

    // Calculating Strassen's products:
    int **p1 = strassenMultiply(a11, s1, mid); // p1 = a11 * s1
    int **p2 = strassenMultiply(s2, b22, mid); // p2 = s2 * b22
    int **p3 = strassenMultiply(s3, b11, mid); // p3 = s3 * b11
    int **p4 = strassenMultiply(a22, s4, mid); // p4 = a22 * s4
    int **p5 = strassenMultiply(s5, s6, mid); // p5 = s5 * s6
    int **p6 = strassenMultiply(s7, s8, mid); // p6 = s7 * s8
    int **p7 = strassenMultiply(s9, s10, mid); // p7 = s9 * s10

    // Calculating the result sub matrix:
    int** c11 = addMatrix(subtractMatrix(addMatrix(p5, p4, mid), p2, mid), p6, mid); // c11 = p5 + p4 - p2 + p6
    int** c12 = addMatrix(p1, p2, mid); // c12 = p1 + p2
    int** c21 = addMatrix(p3, p4, mid); // c21 = p3 + p4
    int** c22 = subtractMatrix(subtractMatrix(addMatrix(p5, p1, mid), p3, mid), p7, mid); // c22 = p5 + p1 - p3 - p7

    // Combining the result sub matrices:
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
    }
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            result[i][j] = c11[i][j];  // top left
            result[i][j + mid] = c12[i][j]; // top right
            result[i + mid][j] = c21[i][j]; // bottom left 
            result[i + mid][j + mid] = c22[i][j]; // bottom right
        }
    }
    return result;
}

// Now implementing the algorithm in a way that partition happens without copying the entries of the matrices, using index calculations instead.
// This is done to reduce the space complexity of the algorithm.

int** addMatrix(int** A, int** B, int n, int rowA, int colA, int rowB, int colB) {
    int** result = new int*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[rowA + i][colA + j] + B[rowB + i][colB + j];
        }
    }
    return result;
}

int** subtractMatrix(int** A, int** B, int n, int rowA, int colA, int rowB, int colB) {
    int** result = new int*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[rowA + i][colA + j] - B[rowB + i][colB + j];
        }
    }
    return result;
}

void strassenMultiply(int** A, int** B, int** result, int n, int rowA, int colA, int rowB, int colB) {
    if (n == 1) {
        result[0][0] = A[rowA][colA] * B[rowB][colB];
        return;
    }

    // Split matrices into quadrants
    int mid = n / 2;

    // Calculating sub matrices for Strassen's products:
    int** s1 = subtractMatrix(B, B, mid, rowB, colB + mid, rowB + mid, colB + mid); // s1 = b12 - b22
    int** s2 = addMatrix(A, A, mid, rowA, colA, rowA, colA + mid); // s2 = a11 + a12
    int** s3 = addMatrix(A, A, mid, rowA + mid, colA, rowA + mid, colA + mid); // s3 = a21 + a22
    int** s4 = subtractMatrix(B, B, mid, rowB + mid, colB, rowB, colB); // s4 = b21 - b11
    int** s5 = addMatrix(A, A, mid, rowA, colA, rowA + mid, colA + mid); // s5 = a11 + a22
    int** s6 = addMatrix(B, B, mid, rowB, colB, rowB + mid, colB + mid); // s6 = b11 + b22
    int** s7 = subtractMatrix(A, A, mid, rowA, colA + mid, rowA + mid, colA + mid); // s7 = a12 - a22
    int** s8 = addMatrix(B, B, mid, rowB + mid, colB, rowB + mid, colB + mid); // s8 = b21 + b22
    int** s9 = subtractMatrix(A, A, mid, rowA, colA, rowA + mid, colA); // s9 = a11 - a21
    int** s10 = addMatrix(B, B, mid, rowB, colB, rowB, colB + mid); // s10 = b11 + b12

    // Calculating Strassen's products:
    int** p1 = new int*[mid];
    int** p2 = new int*[mid];
    int** p3 = new int*[mid];
    int** p4 = new int*[mid];
    int** p5 = new int*[mid];
    int** p6 = new int*[mid];
    int** p7 = new int*[mid];

    for (int i = 0; i < mid; i++) {
        p1[i] = new int[mid];
        p2[i] = new int[mid];
        p3[i] = new int[mid];
        p4[i] = new int[mid];
        p5[i] = new int[mid];
        p6[i] = new int[mid];
        p7[i] = new int[mid];
    }

    strassenMultiply(A, s1, p1, mid, rowA, colA, 0, 0); // p1 = a11 * s1
    strassenMultiply(s2, B, p2, mid, 0, 0, rowB, colB + mid); // p2 = s2 * b22
    strassenMultiply(s3, B, p3, mid, 0, 0, rowB + mid, colB + mid); // p3 = s3 * b11
    strassenMultiply(A, s4, p4, mid, rowA + mid, colA, 0, 0); // p4 = a22 * s4
    strassenMultiply(s5, s6, p5, mid, 0, 0, 0, 0); // p5 = s5 * s6
    strassenMultiply(s7, s8, p6, mid, 0, 0, 0, 0); // p6 = s7 * s8
    strassenMultiply(s9, s10, p7, mid, 0, 0, 0, 0); // p7 = s9 * s10

    // Calculating the result sub matrix:
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            result[rowA + i][colA + j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j]; // c11 = p5 + p4 - p2 + p6
            result[rowA + i][colA + j + mid] = p1[i][j] + p2[i][j]; // c12 = p1 + p2
            result[rowA + i + mid][colA + j] = p3[i][j] + p4[i][j]; // c21 = p3 + p4
            result[rowA + i + mid][colA + j + mid] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j]; // c22 = p5 + p1 - p3 - p7
        }
    }

    // Cleanup
    for (int i = 0; i < mid; i++) {
        delete[] p1[i];
        delete[] p2[i];
        delete[] p3[i];
        delete[] p4[i];
        delete[] p5[i];
        delete[] p6[i];
        delete[] p7[i];
    }
    delete[] p1;
    delete[] p2;
    delete[] p3;
    delete[] p4;
    delete[] p5;
    delete[] p6;
    delete[] p7;
    delete[] s1;
    delete[] s2;
    delete[] s3;
    delete[] s4;
    delete[] s5;
    delete[] s6;
    delete[] s7;
    delete[] s8;
    delete[] s9;
    delete[] s10;
}


int main() {
    cout << "Enter the size of the matrices: ";
    int n;
    cin >> n;
    cout << "Enter the elements of the first matrix: ";
    int** A = new int*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    cout << "Enter the elements of the second matrix: ";
    int** B = new int*[n];
    for (int i = 0; i < n; i++) {
        B[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }

    int** result = strassenMultiply(A, B, n);
    cout << "The product of the matrices is: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "[ ";
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}