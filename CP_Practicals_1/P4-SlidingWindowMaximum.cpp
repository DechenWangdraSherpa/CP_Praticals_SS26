#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    int N, K;
    cout << "Enter the size of the array: ";
    cin >> N;
    cout << "Enter the window size: ";
    cin >> K;

    vector<int> arr(N);
    cout << "Enter the elements: ";
    for(int i = 0; i < N; i++) cin >> arr[i];

    cout << "Maximum of each window: ";
    deque<int> dq;
    for(int i = 0; i < N; i++) {

        if(!dq.empty() && dq.front() == i - K)
            dq.pop_front();

        while(!dq.empty() && arr[dq.back()] < arr[i])
            dq.pop_back();

        dq.push_back(i);

        if(i >= K - 1)
            cout << arr[dq.front()] << " ";
    }

    return 0;
}