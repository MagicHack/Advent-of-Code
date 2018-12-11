#include <iostream>
#include <set>

const int GRID_SIZE = 300;

int caclcultatePower(int x, int y, int serial){
    int rackId = x + 10;
    int powerLevel = rackId * y + serial;
    powerLevel *= rackId;
    powerLevel /= 100;
    powerLevel %= 10;
    return powerLevel - 5;
}

void printGrid(int grid[300][300]){
    for(int y = 0; y < GRID_SIZE; y++){
        for(int x = 0; x < GRID_SIZE; x++){
            std::cout << grid[y][x] << "\t";
        }
        std::cout << "\n";
    }
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
    int maxPower = 0;
    std::pair<int, int> coord;
    int size = 0;
    for(int s = 0; s <= GRID_SIZE; s++){
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
                    size = s;
                }
            }
        }
    }


    std::cout << "Max power is " << maxPower << " at (" << coord.first << "," << coord.second << ")\n";
    std::cout << "Grid size is " << size << "x" << size << "\n";

    return 0;
}