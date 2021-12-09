#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>

struct Point {
    int x;
    int y;
};

const auto directions = {-1, 1};

int bassinSize(const std::vector<std::vector<int>> &data, const Point &p, std::vector<std::vector<bool>> &mp) {
    // check if not part of another bassin
    if (mp[p.y][p.x]) {
        return 0;
    }
    mp[p.y][p.x] = true;
    int currentHeigth = data[p.y][p.x];
    int size = 1;
    for (const auto d: directions) {
        int i = p.y - d;
        int j = p.x - d;
        if (i >= 0 && i < data.size()) {
            int heigth = data[i][p.x];
            if (heigth < 9 && heigth > currentHeigth) {
                size += bassinSize(data, {p.x, i}, mp);
            }
        }
        if (j >= 0 && j < data[p.y].size()) {
            int heigth = data[p.y][j];
            if (heigth < 9 && heigth > currentHeigth) {
                size += bassinSize(data, {j, p.y}, mp);
            }
        }
    }
    return size;
}

int main() {


    const std::string inputFilePath = "../input.txt";
    //const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        std::cout << "err";
        return 1;
    }

    std::string val;
    std::vector<std::vector<int>> data;
    while (inputFile >> val) {
        std::vector<int> vals;
        for (auto c: val) {
            vals.push_back(std::stoi(std::string(1, c)));
        }
        data.push_back(vals);
    }


    std::vector<int> lowPoints;
    std::vector<Point> basins;
    for (int y = 0; y < data.size(); y++) {
        for (int x = 0; x < data[y].size(); x++) {
            bool lower = true;
            for (auto d: directions) {
                int currentHeigth = data[y][x];

                // up down
                int i = y + d;
                if (i >= 0 && i < data.size()) {
                    if (data[i][x] < currentHeigth) {
                        lower = false;
                    }
                }

                //left right
                int j = x + d;
                if (j >= 0 && j < data[y].size()) {
                    if (data[y][j] < currentHeigth) {
                        lower = false;
                    }
                }

            }
            if (lower) {
                if (data[y][x] != 9) { // not sure why the nines are there xD
                    lowPoints.push_back(data[y][x]);
                    basins.push_back({x, y});
                }
            }
        }
    }

    int riskLevel = 0;
    for (auto l: lowPoints) {
        riskLevel += l + 1;
    }
    std::cout << "P1 : " << riskLevel << std::endl;


    std::vector<int> bassinSizes;
    bassinSizes.reserve(basins.size());
    std::vector<std::vector<bool>> markedPoints(data.size(), std::vector<bool>(data[0].size(), false));

    for (auto b: basins) {
        int size = bassinSize(data, b, markedPoints);
        bassinSizes.push_back(size);
    }

    std::sort(bassinSizes.begin(), bassinSizes.end());
    std::cout << "P2 : " << std::accumulate(bassinSizes.end() - 3, bassinSizes.end(), 1, std::multiplies<>()) << "\n";

    return 0;
}
