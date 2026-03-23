#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    int N, K;
    cout << "=== Sliding Window Maximum ===" << endl;
    cout << "Finds the maximum value in every window of size K as it slides across the array." << endl;
    cout << endl;
    cout << "Array size (N): ";
    cin >> N;
    cout << "Window size (K): ";
    cin >> K;

    cout << "Enter " << N << " integers (space separated): ";
    vector<int> A(N);
    for (auto& x : A) cin >> x;

    deque<int> dq;

    cout << endl;
    cout << "Maximum in each window of size " << K << ":" << endl;
    cout << "  ";

    bool first = true;
    for (int i = 0; i < N; i++) {
        while (!dq.empty() && dq.front() < i - K + 1)
            dq.pop_front();

        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= K - 1) {
            if (!first) cout << "  ";
            cout << A[dq.front()];
            first = false;
        }
    }
    cout << endl;

    return 0;
}