#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K;
    cout << "Enter N (number of booths), M (starting coins), K (max skips): " << flush;
    cin >> N >> M >> K;
    
    vector<int> toll(N + 1);
    cout << "Enter toll amounts for " << N << " booths: " << flush;
    for (int i = 1; i <= N; i++) {
        cin >> toll[i];
    }
    
    vector<vector<int>> dp(M + 1, vector<int>(K + 1, INT_MAX));
    vector<vector<int>> next_dp(M + 1, vector<int>(K + 1, INT_MAX));
    
    dp[M][0] = 0;
    
    for (int i = 2; i <= N; i++) {
        for (int c = 0; c <= M; c++) {
            for (int s = 0; s <= K; s++) {
                next_dp[c][s] = INT_MAX;
            }
        }
        
        for (int coins = 0; coins <= M; coins++) {
            for (int skips = 0; skips <= K; skips++) {
                if (dp[coins][skips] == INT_MAX) continue;
                
                int currentTime = dp[coins][skips];
                
                if (coins >= toll[i]) {
                    int newCoins = coins - toll[i];
                    if (currentTime + 1 < next_dp[newCoins][skips]) {
                        next_dp[newCoins][skips] = currentTime + 1;
                    }
                }
                
                if (skips < K) {
                    if (currentTime + 2 < next_dp[coins][skips + 1]) {
                        next_dp[coins][skips + 1] = currentTime + 2;
                    }
                }
            }
        }
        
        dp = next_dp;
    }
    
    int minTime = INT_MAX;
    for (int coins = 0; coins <= M; coins++) {
        for (int skips = 0; skips <= K; skips++) {
            if (dp[coins][skips] < minTime) {
                minTime = dp[coins][skips];
            }
        }
    }
    
    cout << "\nMinimum time to reach booth " << N << ": ";
    if (minTime == INT_MAX) {
        cout << "-1 (impossible)\n";
    } else {
        cout << minTime << "\n";
    }
    
    return 0;
}