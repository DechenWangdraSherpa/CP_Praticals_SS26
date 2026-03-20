#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "Enter the size of the array: ";
    int N;
    cin >> N;

    vector<int> arr(N);
    cout << "Enter the numbers: ";
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int sum = 0;
    int mx = arr[0], mn = arr[0];

    for(int x : arr) {
        sum += x;
        mx = max(mx, x);
        mn = min(mn, x);
    }

    cout << "Max: " << mx << endl;
    cout << "Min: " << mn << endl;
    cout << "Sum: " << sum << endl;

    return 0;
}