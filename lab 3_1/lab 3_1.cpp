#include <iostream>
#include <fstream>
using namespace std;

const int MAXN = 36;
long long dp[MAXN][3][3];

int main() {

    int n;
    cin >> n;

    dp[0][0][0] = 1;
    dp[1][0][1] = dp[1][0][2] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2];
                if (j == 1 && k == 2)
                    dp[i][j][k] -= dp[i - 2][0][0];
            }
        }
    }

    cout << dp[n][1][2] << endl;

    return 0;
}
