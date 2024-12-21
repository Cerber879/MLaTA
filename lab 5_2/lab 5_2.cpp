#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

int find_max_win(int n, std::vector<int>& sectors, int a, int b, int k) {
    int max_win = 0;
    for (int i = 0; i < n; ++i) {
        int win = 0;
        for (int v = a; v <= b; ++v) {
            int j = i;
            while (v > k) {
                j = (j + 1) % n;
                v -= k;
            }
            win = std::max(win, sectors[j]);
        }
        max_win = std::max(max_win, win);
    }
    return max_win;
}

int main() 
{
    int n;
    fin >> n;
    std::vector<int> sectors(n);
    for (int i = 0; i < n; ++i) {
        fin >> sectors[i];
    }
    int a, b, k;
    fin >> a >> b >> k;

    fout << find_max_win(n, sectors, a, b, k) << std::endl;

    return 0;
}
