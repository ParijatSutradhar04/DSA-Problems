#include<bits/stdc++.h>
using namespace std;

float* add(float* A, float* B, int n) {
    float* C = new float[n];
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

float* sub(float* A, float* B, int n) {
    float* C = new float[n];
    for (int i = 0; i < n; i++) {
        C[i] = A[i] - B[i];
    }
    return C;
}

float* polymul(float* A, float* B, int n) {
    float* C = new float[2*n - 1];
    for (int i = 0; i < 2*n - 1; i++) {
        C[i] = 0;
    }
    int t = n/2;
    if (n == 1) {
        C[0] = A[0]*B[0];
        return C;
    }
    float* A0 = new float[t];
    float* A1 = new float[t];
    float* B0 = new float[t];
    float* B1 = new float[t];
    float* C0 = new float[2*t - 1];
    float* C1 = new float[2*t - 1];
    float* C2 = new float[2*t - 1];
    // C = A0*B0 + (A0*B1 + A1*B0)*x^t + A1*B1*x^2t
    for (int i = 0; i < t; i++) {
        A0[i] = A[i];
        A1[i] = A[i + t];
        B0[i] = B[i];
        B1[i] = B[i + t];
    }
    C0 = polymul(A0, B0, t);
    C1 = polymul(A1, B1, t);
    A0 = add(A0, A1, t);
    B0 = add(B0, B1, t);
    C2 = polymul(A0, B0, t);
    C2 = sub(C2, C0, 2*t - 1);
    C2 = sub(C2, C1, 2*t - 1);
    for (int i = 0; i < 2*t - 1; i++) {
        C[i] = C0[i];
        C[i + t] = C1[i];
        C[i + 2*t] = C2[i];
    }

    return C;
}
 
int main(){
    
    return 0;
}
