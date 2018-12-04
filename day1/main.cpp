#include <iostream>
#include <fstream>

int main() {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()){
        std::cerr << "Error opening file : \"" << inputFilePath <<  "\"\n";
        return 0;
    }

    int resultingFrequency = 0;
    int variation = 0;
    while(inputFile >> variation){
        resultingFrequency += variation;
    }
    std::cout << resultingFrequency << "\n";
    return 0;
}