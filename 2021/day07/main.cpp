#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()) {
        return 1;
    }

    std::string val;
    std::vector<int> crabs;

    while(std::getline(inputFile, val, ',')) {
        crabs.push_back(std::stoi(val));
    }

    int maxPos = *std::max_element(crabs.begin(), crabs.end());

    // P1
    int minFuelConsumption = INT_MAX;
    for(int i = 0; i <= maxPos; i++) {
        int fuelConsumption = 0;
        for(auto c: crabs) {
            fuelConsumption += std::abs(c - i);;
        }
        minFuelConsumption = std::min(fuelConsumption, minFuelConsumption);
    }
    std::cout << "P1: " << minFuelConsumption << std::endl;

    // P2
    minFuelConsumption = INT_MAX;
    for(int i = 0; i <= maxPos; i++) {
        int fuelConsumption = 0;
        for(auto c: crabs) {
            int moveDistance =  std::abs(c - i);
            int moveCost = (moveDistance * (moveDistance + 1)) / 2;
            fuelConsumption += moveCost;
        }
        minFuelConsumption = std::min(fuelConsumption, minFuelConsumption);
    }

    std::cout << "P2: " << minFuelConsumption << std::endl;
}


