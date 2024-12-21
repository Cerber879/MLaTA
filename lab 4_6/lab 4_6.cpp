#include <iostream>
#include <vector>

using namespace std;

vector<int> findMinCoins(vector<int>& coins, int target) {
    vector<int> minCoins(target + 1, INT_MAX);
    minCoins[0] = 0;

    for (int i = 1; i <= target; i++) {
        for (int j = 0; j < coins.size(); j++) {
            if (coins[j] <= i) {
                int subResult = minCoins[i - coins[j]];
                std::cout << "coin - " << coins[j] << " sum - " << i << " subResult - " << subResult << std::endl;
                if (subResult != INT_MAX && subResult + 1 < minCoins[i]) {
                    std::cout << "     sum(i) - " << minCoins[i] << "  " << subResult + 1 << std::endl;
                    minCoins[i] = subResult + 1;
                }
            }
        }
    }

    std::cout << "-------------------------------" << std::endl;
    for (int j = 0; j < coins.size(); j++) {
        std::cout << coins[j] << " ";
    }
    std::cout << std::endl;
    for (int j = 0; j < minCoins.size(); j++) {
        std::cout << j << " " << minCoins[j] << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;

    vector<int> result;
    int remaining = target;
    while (remaining > 0) {
        for (int j = 0; j < coins.size(); j++) {
            std::cout << "coin - " << coins[j] << " remaining - " << remaining << std::endl;
            if (coins[j] <= remaining && minCoins[remaining - coins[j]] == minCoins[remaining] - 1) {
                std::cout << "     sum - " << minCoins[remaining - coins[j]] << " minSum - " << minCoins[remaining] - 1 << std::endl;
                result.push_back(coins[j]);
                remaining -= coins[j];
                break;
            }
        }
    }

    return result;
}

int main() {
    vector<int> coins = { 2, 3, 6 };
    int target = 10;

    vector<int> result = findMinCoins(coins, target);

    cout << result.size() << " " << target << endl;
    for (int coin : coins) {
        int count = 0;
        for (int r : result) {
            if (r == coin) count++;
        }
        if (count != 0) {
            cout << coin << " " << count << endl;
        }
    }

    return 0;
}