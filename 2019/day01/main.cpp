#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int fuelOneModule (int mass) {
    return mass / 3 - 2;
}

void testFuelOneModule() {
    std::cout << std::boolalpha;
    std::cout << (fuelOneModule(12) == 2) << "\n";
    std::cout << (fuelOneModule(14) == 2) << "\n";
    std::cout << (fuelOneModule(1969) == 654) << "\n";
    std::cout << (fuelOneModule(100756) == 33583) << "\n";
}

int calculateAllFuel(std::vector<int>& modulesMass) {
    int totalFuel = 0;
    for(auto mass : modulesMass) {
        totalFuel += fuelOneModule(mass);
    }
    return totalFuel;
}

int main() {
    std::string inputPath = "../input.txt";
    std::ifstream inputFile;
    inputFile.open(inputPath);
    if(inputFile.fail()) {
        std::cerr << "Error opening file " << inputPath;
        return 0;
    }

    std::vector<int> modulesMass;
    int mass;
    while(inputFile >> mass) {
        modulesMass.push_back(mass);
    }
    // testFuelOneModule();
    std::cout << "Total fuel needed : " << calculateAllFuel(modulesMass);
    return 0;
}

