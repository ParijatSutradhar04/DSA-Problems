#include<bits/stdc++.h>
using namespace std;

void gfft(vector<complex<double>> a, vector<complex<double>> f, bool invert) {
    int n = a.size();
    if (n == 1) {
        f[0] = a[0];
        return;
    }

    vector<complex<double>> e(n/2), o(n/2), ef(n/2), of(n/2);
    for (int i = 0; i < n/2; i++) {
        e[i] = a[2 * i];
        o[i] = a[2 * i + 1];
    }

    gfft(e, ef, invert);
    gfft(o, of, invert);

    int s = invert ? -1 : 1;

    complex<double> omega = polar(1.0, s * 2 * M_PI / n); // e^(s*2*pi*i/n)

    for(int i = 0; i < n/2; i++) {
        f[i] = ef[i] + omega * of[i];
        f[i + n/2] = ef[i] - omega * of[i];
        omega *= polar(1.0, s * 2 * M_PI / n);
    }
}
 
int main(){
    
    return 0;
}
