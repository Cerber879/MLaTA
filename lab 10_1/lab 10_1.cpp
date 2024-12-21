// 10.1. Последовательность 1 (6)
// 
// В последовательности чисел a1, a2, a3, ... задан первый член, а остальные вычисляются 
// по формуле ai = (ai - 1)^2 mod M + 1. Найти N - й член последовательности.
// 
// Ограничения: 1 ≤ M ≤ 10000, 2 ≤ N ≤ 10^18, 0 ≤ a1 ≤ M.
// Ввод из файла INPUT.TXT.В первой строке находятся числа M, N и a1, разделённые пробелом.
// Вывод в файл OUTPUT.TXT.Вывести одно число - aN.

#include <iostream>
#include <fstream>
#include <vector>

const std::string INPUT_FILE("input.txt");
const std::string OUTPUT_FILE("output.txt");
const char WHITESPASE(' ');

using namespace std;

int calcNextMember(int m, int a) {
    return ((a * a) % m) + 1;
}

int main()
{
    setlocale(LC_ALL, "RU");
    std::ifstream inFile(INPUT_FILE);
    std::ofstream outFile(OUTPUT_FILE);

    int m, a1;
    long long n, n1;
    inFile >> m >> n >> a1;
    n1 = n;

    std::vector<int> sequen;
    sequen.push_back(a1);

    int start, end, len;

    while (true) {
        int num = calcNextMember(m, sequen.back());
        auto index = std::find(sequen.begin(), sequen.end(), num);
        if (index != sequen.end()) {
            start = std::distance(sequen.begin(), index);
            end = sequen.size() - 1;
            len = end - start + 1;
            break;
        }
        else {
            sequen.push_back(num);
        }
    }

    for (int t = 0; t < sequen.size(); ++t)
    {
        if (t == start)
            std::cout << "start: \n";
        std::cout << sequen[t] << "\n";

    }
    std::cout << "\n";

    if (start >= n) {
        outFile << sequen[n - 1] << endl;
        std::cout << sequen[n - 1] << endl;
    }
    else {
        std::cout << "расчет: n - " << n << " start - " << start << " len - " << len << "\n";
        std::cout << "n - start = " << n - start - 1 << " (n - start) % len = " << (n - start - 1) % len << "\n";
        n = (n - start - 1) % len;
        outFile << sequen[(start)+n] << endl;
        std::cout << sequen[(start)+n] << endl;
    }


    return 0;
}
