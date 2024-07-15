#include<bits/stdc++.h>
using namespace std;

void allButMe(float *A, float*B, int n){
    if (n == 1) {
        B[0] = 1;
        return;
    }
    int m = n/2; 
    allButMe(A, B, m);
    allButMe(A+m, B+m, n-m);
    float s = A[0] * B[0];
    float t = A[m] * B[m];
    for (int i = 0; i < m; i++) {
        B[i] *= t;
    }
    for (int i = m; i < n; i++) {
        B[i] *= s;
    }
}
 
int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    float A[n], B[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    allButMe(A, B, n);

    cout << "The array after multiplying all elements except the current element is: ";
    for (int i = 0; i < n; i++) {
        cout << B[i] << " ";
    }
    
    return 0;
}