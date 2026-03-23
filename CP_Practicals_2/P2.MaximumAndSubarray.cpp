#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkPossible(int candidate, const vector<int>& arr, int K) {
    int n = arr.size();
    vector<int> windowBits(32, 0); // Count of 1s for each bit in current window
    
    for (int i = 0; i < K; i++) {
        for (int bit = 0; bit < 32; bit++) {
            if (arr[i] & (1 << bit)) {
                windowBits[bit]++;
            }
        }
    }
    
    bool found = true;
    for (int bit = 0; bit < 32; bit++) {
        if (candidate & (1 << bit)) {
            if (windowBits[bit] != K) { // Need all K elements to have this bit set
                found = false;
                break;
            }
        }
    }
    if (found) return true;
    
    for (int i = K; i < n; i++) {
        for (int bit = 0; bit < 32; bit++) {
            if (arr[i - K] & (1 << bit)) {
                windowBits[bit]--;
            }
        }
        
        for (int bit = 0; bit < 32; bit++) {
            if (arr[i] & (1 << bit)) {
                windowBits[bit]++;
            }
        }
        
        bool windowValid = true;
        for (int bit = 0; bit < 32; bit++) {
            if (candidate & (1 << bit)) {
                if (windowBits[bit] != K) {
                    windowValid = false;
                    break;
                }
            }
        }
        if (windowValid) return true;
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cout << "Enter number of test cases: " << flush;
    cin >> T;
    
    for (int testCase = 1; testCase <= T; testCase++) {
        cout << "\n=== Test Case " << testCase << " ===\n" << flush;
        
        int N, K;
        cout << "Enter N and K: " << flush;
        cin >> N >> K;
        
        vector<int> arr(N);
        cout << "Enter " << N << " integers: " << flush;
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        
        int result = 0;
        
        for (int bit = 31; bit >= 0; bit--) {
            int candidate = result | (1 << bit);
            if (checkPossible(candidate, arr, K)) {
                result = candidate;
            }
        }
        
        cout << "Maximum AND value: " << result << "\n" << flush;
        cout << "----------------------------------------\n" << flush;
    }
    
    return 0;
}