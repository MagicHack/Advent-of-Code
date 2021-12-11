#include <iostream>
#include <vector>
#include <fstream>
#include <string>

auto directions = {-1, 0, 1};

void updateFlashed(int x, int y, std::vector<std::vector<int>>& octopuses, std::vector<std::vector<bool>>& flashes) {
    if(flashes[y][x]) {
        return;
    }
    if(octopuses[y][x] > 9) {
        flashes[y][x] = true;
        for (auto d: directions) {
            for (auto d2: directions) {
                if (d == 0 && d2 == 0) {
                    continue;
                }
                int y1 = y + d;
                int x1 = x + d2;
                if (y1 >= 0 && y1 < octopuses.size() && x1 >= 0 && x1 < octopuses[y].size()) {
                    octopuses[y1][x1]++;
                    if (octopuses[y1][x1] > 9) {
                        updateFlashed(x1, y1, octopuses, flashes);
                    }
                }
            }
        }
    }
}

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        std::cout << "err";
        return 1;
    }

    std::vector<std::vector<int>> octopuses;
    std::string line;
    int numOctopus = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> vals;
        for (auto c: line) {
            numOctopus++;
            vals.push_back(std::stoi(std::string(1, c)));
        }
        octopuses.push_back(vals);
    }


    int numFlashes = 0;

    for(int i = 0; i < 1'000'000'000; i++) {
        std::vector<std::vector<bool>> flashed(octopuses.size(), std::vector<bool>(octopuses[0].size(), false));

        // increment all energy by one
        for (auto & octopus : octopuses) {
            for (int & o : octopus) {
                o++;
            }
        }
        // for flashing octo, update all adjacent
        for (int y = 0; y < octopuses.size(); y++) {
            for (int x = 0; x < octopuses[y].size(); x++) {
                updateFlashed(x, y, octopuses, flashed);
            }
        }
        int numFlashesStep = 0;
        for(auto& y : octopuses) {
            for(auto& x : y) {
                if(x > 9) {
                    numFlashesStep++;
                    x = 0;
                }
            }
        }
        if(i < 100) {
            numFlashes += numFlashesStep;
        }
        if(numFlashesStep == numOctopus) {
            std::cout << "P2 : step " << i + 1 << "\n";
            break;
        }
    }

    std::cout << "P1 : " << numFlashes << "\n";
    return 0;
}
