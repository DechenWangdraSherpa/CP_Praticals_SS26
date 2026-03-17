#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int N;
    cin >> N;

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(int i = 0; i < N; i++) {
        int x; cin >> x;

        if(maxHeap.empty() || x <= maxHeap.top())
            maxHeap.push(x);
        else
            minHeap.push(x);

        // balance heaps
        if(maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if(minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // print median
        if(maxHeap.size() == minHeap.size())
            cout << (maxHeap.top() + minHeap.top()) / 2.0 << endl;
        else
            cout << maxHeap.top() << endl;
    }

    return 0;
}