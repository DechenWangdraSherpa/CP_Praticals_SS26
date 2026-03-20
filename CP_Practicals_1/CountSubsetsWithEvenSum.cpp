#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N);
    cout << "Enter " << N << " elements: ";
    for (int i = 0; i < N; i++) cin >> arr[i];

    int total = 1 << N;
    int count = 0;

    cout << "\nChecking all subsets for even sum:\n" << endl;

    for (int mask = 0; mask < total; mask++) {
        int sum = 0;
        cout << "{ ";
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                cout << arr[i] << " ";
                sum += arr[i];
            }
        }
        cout << "} sum = " << sum;

        if (sum % 2 == 0) {
            cout << " (even)";
            count++;
        }
        cout << endl;
    }

    cout << "\nTotal subsets with even sum: " << count << endl;

    return 0;
}