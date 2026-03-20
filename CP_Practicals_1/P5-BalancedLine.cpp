#include <iostream>
#include <deque>
using namespace std;

int main() {
    int Q;
    cout << "Enter number of operations (Q): ";
    cin >> Q;

    cout << "\nAvailable commands:" << endl;
    cout << "  push_front <number>  - add to front" << endl;
    cout << "  push_back  <number>  - add to back" << endl;
    cout << "  pop_front            - remove from front" << endl;
    cout << "  pop_back             - remove from back" << endl;
    cout << "\nEnter your operations:\n" << endl;

    deque<int> dq;
    while (Q--) {
        string op;
        cin >> op;
        if (op == "push_front") {
            int x; cin >> x;
            dq.push_front(x);
        }
        else if (op == "push_back") {
            int x; cin >> x;
            dq.push_back(x);
        }
        else if (op == "pop_front") {
            if (!dq.empty()) dq.pop_front();
        }
        else if (op == "pop_back") {
            if (!dq.empty()) dq.pop_back();
        }

        cout << "Deque now: ";
        for (int x : dq) cout << x << " ";
        cout << endl;
    }

    return 0;
}