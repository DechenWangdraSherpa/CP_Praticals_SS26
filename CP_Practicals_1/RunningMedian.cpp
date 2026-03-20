#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int N;
    cout << "Enter number of elements : ";
    cin >> N;

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cout << "Enter " << N << " numbers one by one:\n" << endl;

    for (int i = 0; i < N; i++) {
        int x;
        cout << "Enter number " << (i + 1) << ": ";
        cin >> x;

        if (maxHeap.empty() || x <= maxHeap.top())
            maxHeap.push(x);
        else
            minHeap.push(x);

        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        cout << "Median after " << (i + 1) << " number(s): ";
        if (maxHeap.size() == minHeap.size())
            cout << (maxHeap.top() + minHeap.top()) / 2.0 << endl;
        else
            cout << maxHeap.top() << endl;

        cout << endl;
    }

    return 0;
}
