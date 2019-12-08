#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
struct Point{
    int x;
    int y;
};

struct Claim{
    int id;
    Point pos;
    int width;
    int height;
};

struct SquareInch{
    int numClaims;
    std::vector<int> ids;
};

Claim parseClaim(const std::string& line){
    int id = std::stoi(line.substr(1, line.find('@')));
    int x = std::stoi(line.substr(line.find('@') + 1, line.find(',')));
    int y = std::stoi(line.substr(line.find(',') + 1, line.find(':')));
    int width = std::stoi(line.substr(line.find(':') + 1, line.find('x')));
    int height = std::stoi(line.substr(line.find('x') + 1));
    return {id, {x, y}, width, height};
}

Point maxSize(const std::vector<Claim>& claims){
    int maxX = 0, maxY = 0;
    for(auto& c : claims){
        int x = c.pos.x + c.width;
        int y = c.pos.y + c.height;
        if(x > maxX) maxX = x;
        if(y > maxY) maxY = y;
    }
    return {maxX, maxY};
}

void populateFabric(std::vector<std::vector<SquareInch>>& fabric, std::vector<Claim>& claims){
    for(auto& c : claims){
        for(int y = c.pos.y; y < c.pos.y + c.height; y++){
            for(int x = c.pos.x; x < c.pos.x + c.width; x++){
                fabric[y][x].ids.push_back(c.id);
                fabric[y][x].numClaims++;
            }
        }
    }
}

int countNumMultipleClaims(std::vector<std::vector<SquareInch>>& fabric){
    int num = 0;
    for(auto& y : fabric){
        for(auto& x: y){
            if(x.numClaims > 1) num++;
        }
    }
    return num;
}

int findIdNonOverlapping(std::vector<std::vector<SquareInch>>& fabric, std::vector<Claim>& claims){
    for(auto& c: claims){
        bool overlap = false;
        for(auto& y: fabric){
            for(auto& x: y){
                if(find(x.ids.begin(), x.ids.end(), c.id) != x.ids.end()){
                    if(x.ids.size() > 1) overlap = true;
                }
                if(overlap) break;
            }
            if(overlap) break;
        }
        if(!overlap){
            return c.id;
        }
    }
    return 0;
}

int main() {
    std::string inputFilePath = "../input.txt";
    // std::string inputFilePath = "../example.txt";

    std::ifstream inputFile(inputFilePath);
    if(inputFile.fail()){
        std::cerr << "Error opening the file " << inputFilePath << "\n";
        return 0;
    }

    std::vector<Claim> claims;
    std::string line;
    while(getline(inputFile, line)){
        if(line.empty()) continue;
        claims.push_back(parseClaim(line));
    }

    Point size = maxSize(claims);

    std::vector<std::vector<SquareInch>> fabric(size.y, std::vector<SquareInch>(size.x, {0}));

    populateFabric(fabric, claims);

    // Part 1
    int result = countNumMultipleClaims(fabric);
    std::cout << "Number of square inches with 2 claims or more : " << result << "\n";
    // Part 2
    int idNonOverlapping = findIdNonOverlapping(fabric, claims);
    std::cout << "Id of the claim that isn't overlapping with any other claims : " << idNonOverlapping << "\n";

    return 0;
}
