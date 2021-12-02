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

    enum Direction {
        forward,
        down,
        up
    };

    std::vector<std::pair<Direction, int>> data;
    int inputAmount = 0;
    std::string inputDirection;
    while(inputFile >> inputDirection && inputFile >> inputAmount) {
        Direction direction;
        if(inputDirection == "forward") {
            direction = forward;
        } else if(inputDirection == "up") {
            direction = up;
        } else if(inputDirection == "down") {
            direction = down;
        }
        data.emplace_back(direction, inputAmount);
    }

    // part 1
    int x = 0, y = 0;
    for(const auto& d : data) {
        int amount = d.second;
        switch (d.first) {
            case up:
                y -= amount;
                break;
            case down:
                y += amount;
                break;
            case forward:
                x += amount;
            break;
        }
    }

    std::cout << "x : " << x << ", y : " << y << ", answer : " << x * y << std::endl;


    // part 2

    x = y = 0;
    int aim = 0;
    for(const auto& d : data) {
        int amount = d.second;
        switch (d.first) {
            case up:
                aim -= amount;
                break;
            case down:
                aim += amount;
                break;
            case forward:
                x += amount;
                y += amount * aim;
                break;
        }
    }

    std::cout << "x : " << x << ", y : " << y << ", answer : " << x * y << std::endl;
    return 0;
}
