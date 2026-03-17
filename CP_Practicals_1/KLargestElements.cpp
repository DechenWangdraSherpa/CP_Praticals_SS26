#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int main() {
    int N, K;
    cout << "Enter number of elements: ";
    cin >> N;
    cout << "Enter how many top elements to print: ";
    cin >> K;

    vector<int> arr(N);
    cout << "Enter " << N << " elements: ";
    for (int i = 0; i < N; i++) cin >> arr[i];

    priority_queue<int> pq;
    for (int x : arr) pq.push(x);

    cout << "\nTop " << K << " largest elements: ";
    for (int i = 0; i < K; i++) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    return 0;
}