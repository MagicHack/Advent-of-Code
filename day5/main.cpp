#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int react(std::string polymer);

int main(int argc, char* argv[]) {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()){
        std::cerr << "Error opening file \"" << inputFilePath << "\"n";
        return 0;
    }

    std::string line;
    std::string polymer;
    while(std::getline(inputFile, line)){
        polymer += line;
    }

    int startingUnits = polymer.size();
    int remainingUnits = react(polymer);

    std::cout << "Part 1:\n" << "\tStarting units : " << startingUnits << "\n\tRemaining units : " << remainingUnits << "\n";
    std::vector<int> polymerSizes = {remainingUnits};
    // Part 2
    for(char c = 'A'; c <= 'Z'; c++){
        std::string polymerCopy = polymer;

        polymerCopy.erase(std::remove(polymerCopy.begin(), polymerCopy.end(), c), polymerCopy.end());
        polymerCopy.erase(std::remove(polymerCopy.begin(), polymerCopy.end(), std::tolower(c)), polymerCopy.end());

        polymerSizes.push_back(react(polymerCopy));
    }
    
    int minimumSize = *std::min_element(polymerSizes.begin(), polymerSizes.end());
    std::cout << "Part 2:\n" << "\tMinimum units : " << minimumSize << "\n";

    return 0;
}

int react(std::string polymer){
    bool destroyed;
    do{
        destroyed = false;
        for(int i = 0; i < polymer.size() - 1; i++){
            if(polymer[i] != polymer[i + 1] && std::tolower(polymer[i]) == std::tolower(polymer[i + 1])){
                polymer.erase(i, 2);
                destroyed = true;
                break;
            }
        }
    } while(destroyed);

    return polymer.size();
}