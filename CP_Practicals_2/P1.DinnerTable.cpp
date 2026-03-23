#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cout << "=== Dinner Table Arrangement ===" << endl;
    cout << endl;
    cout << "How many test cases? ";
    cin >> T;

    while (T--) {
        cout << endl;
        int N;
        cout << "How many friends at the table? ";
        cin >> N;

        vector<int> allergy(N, 0);
        for (int i = 0; i < N; i++) {
            cout << endl;
            cout << "  Friend " << i + 1 << ":" << endl;
            cout << "    How many allergies do they have? ";
            int M;
            cin >> M;
            if (M > 0) {
                cout << "    Enter " << M << " allergy ID(s) (numbers 1-30, space separated): ";
                while (M--) {
                    int x;
                    cin >> x;
                    allergy[i] |= (1 << (x - 1));
                }
            }
        }

        if (N == 1) {
            cout << endl << "Result: YES" << endl;
            continue;
        }

        auto compatible = [&](int i, int j) {
            return (allergy[i] & allergy[j]) == 0;
        };


        int FULL = (1 << N) - 1;
        vector<vector<bool>> dp(1 << N, vector<bool>(N, false));
        dp[1][0] = true;

        for (int mask = 1; mask < (1 << N); mask++) {
            for (int last = 0; last < N; last++) {
                if (!dp[mask][last]) continue;
                for (int next = 1; next < N; next++) {
                    if (mask & (1 << next)) continue;       // already seated
                    if (!compatible(last, next)) continue;  // allergy conflict
                    dp[mask | (1 << next)][next] = true;
                }
            }
        }

        bool found = false;
        for (int last = 1; last < N; last++) {
            if (dp[FULL][last] && compatible(last, 0)) {
                found = true;
                break;
            }
        }

        cout << endl;
        cout << "Result: " << (found ? "YES - a valid seating exists" : "NO - no valid seating possible") << endl;
    }

    return 0;
}