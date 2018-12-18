#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <array>

const char OPEN = '.';
const char TREE = '|';
const char LUMBERYARD = '#';

struct NumTileType {
    int numOpen;
    int numTrees;
    int numLumberyard;
};

class Map {
public:
    Map () : minutes_(0) {};
    // Operator overload for input
    friend std::istream& operator>>(std::istream& is, Map& map){
        std::string line;
        int y = 0;
        while(std::getline(is, line)){
            map.map_.push_back(std::vector<char>());
            for(auto c: line){
                map.map_[y].push_back(c);
            }
            y++;
        }
        return is;
    }
    // Operator overload for output
    friend std::ostream& operator<<(std::ostream& os, const Map& map){
        os << "State at minute " << map.minutes_ << ":\n";
        for(auto y: map.map_){
            for(auto x: y){
                os << x;
            }
            os << "\n";
        }
        return os;
    }

    NumTileType checkAdjacent(int x, int y){
        NumTileType adj = {0, 0, 0};
        std::array<std::pair<int, int>, 8> posAdjacent {std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(1, 0), std::make_pair(1, -1), std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0)};
        for(auto& p: posAdjacent){
            int xA = x + p.first;
            int yA = y + p.second;
            if(xA >= 0 && xA < map_[0].size() && yA >= 0 && yA < map_.size()){ // check if not out of bounds
                switch(map_[yA][xA]){
                    case OPEN:
                        adj.numOpen++;
                        break;
                    case TREE:
                        adj.numTrees++;
                        break;
                    case LUMBERYARD:
                        adj.numLumberyard++;
                        break;
                    default:
                        break;
                }
            }
        }
        return adj;
    }

    NumTileType countTileType(){
        NumTileType num = {0, 0, 0};
        for(auto y: map_){
            for(auto x: y){
                switch(x){
                    case OPEN:
                        num.numOpen++;
                        break;
                    case TREE:
                        num.numTrees++;
                        break;
                    case LUMBERYARD:
                        num.numLumberyard++;
                        break;
                    default:
                        break;
                }
            }
        }
        return num;
    }

    int getRessourceValue(){
        auto ressources = countTileType();
        return ressources.numTrees * ressources.numLumberyard;
    }

    int getMinute(){
        return minutes_;
    }
    // Simulate one minute on the map
    void tick(){
        minutes_++;
        auto newMap = map_;
        for(int y = 0; y < map_.size(); y++){
            for(int x = 0; x < map_[y].size(); x++){
                auto adj = checkAdjacent(x, y);
                switch(map_[y][x]){
                    case OPEN:
                        if(adj.numTrees >= 3){
                            newMap[y][x] = TREE;
                        }
                        break;
                    case TREE:
                        if(adj.numLumberyard >= 3){
                            newMap[y][x] = LUMBERYARD;
                        }
                        break;
                    case LUMBERYARD:
                        if(adj.numLumberyard < 1 || adj.numTrees < 1){
                            newMap[y][x] = OPEN;
                        }
                        break;
                }
            }
        }
        map_ = newMap;
    }

private:
    std::vector<std::vector<char>> map_;
    int minutes_;
};


int main(int argc, char* argv[]){
    std::string inputFilePath = "../input.txt";
    //std::string inputFilePath = "../example.txt";

    std::ifstream inputFile(inputFilePath);
    if(inputFile.fail()){
        std::cerr << "Error opening the file " << inputFilePath << "\n";
        return 0;
    }

    Map map = Map();
    inputFile >> map;

    while(map.getMinute() < 10){
        map.tick();
    }

    std::cout << "Ressource value after ten minutes : " << map.getRessourceValue() << "\n";
    
    return 0;
}