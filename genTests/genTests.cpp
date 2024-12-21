    #include <iostream>
#include <fstream>
#include <vector>
#include <random>

int main() {
    std::ofstream outFile("output.txt");
    const int N = 1000000;
    std::vector<int> input_data(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < N; ++i) {
        input_data[i] = dis(gen);
    }

    for (int i = 0; i < N; ++i) {
        outFile << input_data[i];
        if (i < N - 1) {
            outFile << " ";
        }
    }
    outFile << std::endl;

    return 0;
}