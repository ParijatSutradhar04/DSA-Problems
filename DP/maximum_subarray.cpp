#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int sum, start = 0, end = 0;
    sum = arr[0];
    int max_sum = sum;

    for (int i = 1; i < n; i++) {
        sum += arr[i];
        if (arr[i] > sum) {
            start = i;
            sum = arr[i];
            end = i;
        }
        else if (arr[i] > 0) {
            end = i;
        }
        max_sum = max(max_sum, sum);
    }

    cout << start << " " << end << " " << max_sum << endl;

    return 0;
}
