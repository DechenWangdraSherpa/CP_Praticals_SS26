#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;
    
public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, node * 2, start, mid);
        build(arr, node * 2 + 1, mid + 1, end);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(node * 2, start, mid, idx, val);
        } else {
            update(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) {
            return -1e9; 
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftMax = query(node * 2, start, mid, l, r);
        int rightMax = query(node * 2 + 1, mid + 1, end, l, r);
        return max(leftMax, rightMax);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K, Q;
    cout << "Enter N, K, Q: " << flush;
    cin >> N >> K >> Q;
    
    vector<int> arr(N + 1); 
    cout << "Enter initial array of " << N << " integers: " << flush;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    
    SegmentTree segTree(N);
    segTree.build(arr, 1, 1, N);
    
    cout << "\nProcessing queries...\n" << flush;
    
    for (int q = 0; q < Q; q++) {
        int type;
        cout << "\nEnter query type (1 or 2): " << flush;
        cin >> type;
        
        if (type == 1) {
            int pos, val;
            cout << "Enter position and new value: " << flush;
            cin >> pos >> val;
            segTree.update(1, 1, N, pos, val);
            cout << "Updated arr[" << pos << "] = " << val << "\n" << flush;
        } 
        else if (type == 2) {
            int i;
            cout << "Enter ending index (window of size " << K << " ending at i): " << flush;
            cin >> i;
            
            int start = i - K + 1;
            if (start < 1) {
                cout << "Error: Window of size " << K << " cannot end at index " << i 
                     << " (needs at least " << K << " elements)\n" << flush;
                continue;
            }
            
            int maxVal = segTree.query(1, 1, N, start, i);
            cout << "Maximum in window [" << start << ", " << i << "]: " << maxVal << "\n" << flush;
        }
    }
    
    return 0;
}