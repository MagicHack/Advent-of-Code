#include <iostream>
#include <set>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

const int GRID_SIZE = 300;

struct GridPower {
    int maxPower;
    int x;
    int y;
    int size;
};

int caclcultatePower(int x, int y, int serial){
    int rackId = x + 10;
    int powerLevel = rackId * y + serial;
    powerLevel *= rackId;
    powerLevel /= 100;
    powerLevel %= 10;
    return powerLevel - 5;
}

void printGrid(const int grid[300][300]){
    for(int y = 0; y < GRID_SIZE; y++){
        for(int x = 0; x < GRID_SIZE; x++){
            std::cout << grid[y][x] << "\t";
        }
        std::cout << "\n";
    }
}

GridPower gridMaxPower(const int cells[GRID_SIZE][GRID_SIZE], int s){
    int maxPower = 0;
    std::pair<int, int> coord = std::make_pair(0, 0);
    for(int y = 0; y < GRID_SIZE - s; y++){
        for(int x = 0; x < GRID_SIZE - s; x++){
            int power = 0;
            for(int i = 0; i < s; i++){
                for(int j = 0; j < s; j++){
                    power += cells[y + i][x + j];
                }
            }
            if(power > maxPower){
                maxPower = power;
                coord.first = x;
                coord.second = y;
            }
        }
    }
    return GridPower {maxPower, coord.first, coord.second, s};
}

int main() {
    int input = 2694;

    int cells[GRID_SIZE][GRID_SIZE];
    // Fill array
    for(int y = 0; y < GRID_SIZE; y++){
        for(int x = 0; x < GRID_SIZE; x++){
            cells[y][x] = caclcultatePower(x, y, input);
        }
    }

    // Part 1
    GridPower part1 = gridMaxPower(cells, 3);
    std::cout << "Part 1:\n" << "\tMax power is : " << part1.maxPower << "\n\tat : " << part1.x << "," << part1.y << "\n";

    // Part 2
    // Even with threading bruteforcing is kinda slow
    std::vector<std::future<GridPower>> threads;
    unsigned maxThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads : " << maxThreads << "\n";
    GridPower currentMax = {0, 0, 0, 0};
    for(int s = 0; s <= GRID_SIZE; s++){
        while(threads.size() >= maxThreads){ // Wait for a thread to finish
            for(int i = 0; i < threads.size(); i++){
                if(threads[i].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
                    GridPower power = threads[i].get();
                    if(power.maxPower > currentMax.maxPower){
                        currentMax = power;
                    }
                    threads.erase(threads.begin() + i);
                }
            }
        }
        threads.push_back(std::async(std::launch::async, gridMaxPower, cells, s)); // Launch thread
    }

    for(auto &thread : threads) {
        GridPower power = thread.get();
        if(power.maxPower > currentMax.maxPower){
            currentMax = power;
        }
    }
    std::cout << "Part 2:\n" << "\tMax power is : " << currentMax.maxPower << "\n\tat : " << currentMax.x << "," << currentMax.y << "\n";
    std::cout << "Grid size is " << currentMax.size << "x" << currentMax.size << "\n";

    return 0;
}