#include <iostream>
#include <fstream>
#include <vector>


int main() {
    const auto INPUT_FILE_PATH = "../input.txt";

    auto inputFile = std::ifstream(INPUT_FILE_PATH);
    if(inputFile.fail()) {
        std::cerr << "error opening file : " << INPUT_FILE_PATH << std::endl;
        return 1;
    }

    std::vector<int> data;
    int value = 0;
    int previous = -1;
    int cntIncreasedP1 = 0;
    while(inputFile >> value) {
        data.push_back(value);
        if(previous != -1 && value > previous) {
            cntIncreasedP1++;
        }
        previous = value;
    }
    std::cout << "Part 1: " << cntIncreasedP1 << std::endl;

    // part 2
    const int windowSize = 3;
    int cntIncreaseP2 = 0;
    for(size_t i = 3; i < data.size(); i++) {
        int window1 = 0;
        int window2 = 0;
        for(int j = 1; j <= windowSize; j++) {
            window1 += data[i - j];
        }
        for(int j = 0; j < windowSize; j++) {
            window2 += data[i - j];
        }
        if(window2 > window1) {
            cntIncreaseP2++;
        }
        // std::cout << window2 << " : " << window1 << std::endl;
    }

    std::cout << "Part 2: " << cntIncreaseP2 << std::endl;

    return 0;
}
