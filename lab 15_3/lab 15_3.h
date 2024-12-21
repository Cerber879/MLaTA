#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

const int MAX_MOTION = 2;

std::vector<std::pair<int, int>> ReadDates(std::istream& cin);
int ResultGame(int d, int m);
void PrintWinners(std::vector<std::pair<int, int>>& dates, std::ofstream& output);
