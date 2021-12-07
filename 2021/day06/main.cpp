#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>


uint64_t numFish(int timer, int days) {
    // pre calculated values
    static std::array<std::array<uint64_t, 256>, 9> values{};

    int daysArray = days - 1;
    if(days <= timer) {
       return 1;
    }
    if(values[timer][daysArray] != 0) {
        return values[timer][daysArray];
    }
    // calculate and save value
    values[timer][daysArray] = numFish(6, days - timer - 1) + numFish(8, days - timer - 1);
    return values[timer][daysArray];
}

uint64_t numFishV2(const std::vector<int>& fish, int days) {
    std::array<uint64_t , 9> fishTimers{};
    for(const auto f : fish) {
        fishTimers[f]++;
    }

    for(int i = 0; i < days; i++) {
        uint64_t newFish = fishTimers[0];
        std::rotate(fishTimers.begin(), fishTimers.begin() + 1, fishTimers.end());
        fishTimers[6] += newFish;
    }
    return std::accumulate(fishTimers.begin(), fishTimers.end(), static_cast<uint64_t>(0));
}

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()) {
        return 1;
    }

    std::string val;
    std::vector<int> fish;

    while(std::getline(inputFile, val, ',')) {
        fish.push_back(std::stoi(val));
    }

    // v2
    std::cout << "P1 v2 : " << numFishV2(fish, 80) << '\n';
    std::cout << "P2 v2 : " << numFishV2(fish, 256) << '\n';

    // p1
    std::vector<int> fishP1 = fish;
    for(int i = 0; i < 80; i++) {
        auto numberOfFish = fishP1.size();
        for(int j = 0; j < numberOfFish; j++) {
            if(fishP1[j] == 0) {
                fishP1[j] = 6;
                fishP1.push_back(8);
            } else {
                fishP1[j]--;
            }
        }
    }
    std::cout << "P1: " << fishP1.size() << std::endl;

    // p2
    uint64_t sum = 0;
    for(auto f: fish) {
        sum += numFish(f, 256);
    }

    std::cout << "P2: " << sum << std::endl;

    return 0;
}
