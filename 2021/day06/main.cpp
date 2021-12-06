#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>


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
        std::cout << "day  " << i << " : " << fishP1.size() << std::endl;
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
