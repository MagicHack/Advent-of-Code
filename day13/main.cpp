// TODO : Completetly rewrite this, works with the example but not my input
// Oh and it outputs the coordinates as (y,x)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum Direction {left = '<', right = '>', up = '^', down = 'v', crashed = 'X'};
enum RailType {horizontal = '-', vertical = '|', leftTurn = '\\', rightTurn = '/', intersection = '+', empty = ' '};

struct Cart{
    Direction dir;
    Direction nextTurn;
    bool hasMoved;
};

struct Rail{
    int x;
    int y;
    RailType type;
    Cart* cart;
};

typedef std::vector<std::vector<Rail>> Map;

Map fillMap(std::istream& input){
    Map map;
    std::string line;
    int y = 0;
    while(std::getline(input, line)){
        if(line.empty()) continue;
        map.push_back(std::vector<Rail>());
        int x = 0;
        for(auto r: line){
            Rail rail {x, y, empty, nullptr};
            switch(r){
                case left:
                    rail.type = horizontal;
                    rail.cart = new Cart{left, left, false};
                    break;
                case right:
                    rail.type = horizontal;
                    rail.cart = new Cart{right, left, false};
                    break;
                case up:
                    rail.type = vertical;
                    rail.cart = new Cart{down, left, false};
                    break;
                case down:
                    rail.type = vertical;
                    rail.cart = new Cart{down, left, false};
                    break;
                case horizontal:
                    rail.type = horizontal;
                    break;
                case vertical:
                    rail.type = vertical;
                    break;
                case leftTurn:
                    rail.type = leftTurn;
                    break;
                case rightTurn:
                    rail.type = rightTurn;
                    break;
                case intersection:
                    rail.type = intersection;
                    break;
                default:
                    rail.type = empty;
                    break;
            }

            map.back().push_back(rail);
            x++;
        }
        y++;
    }

    //std::cout << "Map size : " << map.front().size() << "x" << map.size() << "\n";
    return map;
}

void printMap(const Map& map){
    std::cout << "\t";
    for(int i = 0; i < map.front().size(); i++){
        std::cout << (i / 100) % 10;
    }
    std::cout << "\n\t";
    for(int i = 0; i < map.front().size(); i++){
        std::cout << (i / 10) % 10;
    }
    std::cout << "\n\t";
    for(int i = 0; i < map.front().size(); i++){
        std::cout << i % 10;
    }
    std::cout << "\n";
    int yPos = 0;
    for(auto& y: map){
        std::cout << yPos << "\t";
        for(auto& x: y){
            if(x.cart != nullptr){
                std::cout << char(x.cart->dir);
            } else {
                std::cout << char(x.type);
            }
        }
        std::cout << "\n";
        yPos++;
    }
}

void cleanUpMap(Map& map){ // Prevent memory leaks
    for(auto& line: map){
        for(auto& piece: line){
            if(piece.cart != nullptr){
                delete piece.cart;
                piece.cart = nullptr;
            }
        }
    }
}

void turnCart(Cart* c){
    switch(c->nextTurn){
        case left:
            c->nextTurn = up;
            switch(c->dir){
                case left:
                    c->dir = down;
                    break;
                case right:
                    c->dir = up;
                    break;
                case down:
                    c->dir = right;
                    break;
                case up:
                    c->dir = left;
                    break;
            }
            break;
        case up:
            c->nextTurn = right;
            // Continue in the same direction
            break;
        case right:
            c->nextTurn = left;
            switch(c->dir){
                case left:
                    c->dir = up;
                    break;
                case right:
                    c->dir = down;
                    break;
                case down:
                    c->dir = left;
                    break;
                case up:
                    c->dir = right;
                    break;
            }
            break;
    }
}

/* Ugly mess - could be rewritten with vectors for direction and be much cleaner
 * or even cleaned up a bit with a few functions
 */
bool tick(Map& map){
    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[y].size(); x++){
            if(map[y][x].cart != nullptr && !map[y][x].cart->hasMoved){
                Cart* c = map[y][x].cart;
                switch(c->dir){
                    case left:
                        switch(map[y][x - 1].type){
                            case leftTurn:
                                c->dir = up;
                                break;
                            case rightTurn:
                                c->dir = down;
                                break;
                            case intersection:
                                turnCart(c);
                                break;
                        }
                        if(map[y][x - 1].cart != nullptr && map[y][x - 1].cart->hasMoved){
                            delete map[y][x].cart;
                            map[y][x].cart = nullptr;
                            map[y][x - 1].cart->dir = crashed;
                            std::cout << "Crash : " << y << "," << x - 1 << "\n";
                            return false;
                        } else {
                            map[y][x - 1].cart = map[y][x].cart;
                            map[y][x].cart = nullptr;
                            c->hasMoved = true;
                        }
                        
                        break;
                    case right:
                        switch(map[y][x + 1].type){
                            case leftTurn:
                                c->dir = down;
                                break;
                            case rightTurn:
                                c->dir = up;
                                break;
                            case intersection:
                                turnCart(c);
                                break;
                        }
                        if(map[y][x + 1].cart != nullptr && map[y][x + 1].cart->hasMoved){
                            delete map[y][x].cart;
                            map[y][x].cart = nullptr;
                            map[y][x + 1].cart->dir = crashed;
                            std::cout << "Crash : " << y << "," << x + 1 << "\n";
                            return false;
                        } else {
                            map[y][x + 1].cart = map[y][x].cart;
                            map[y][x].cart = nullptr;
                            c->hasMoved = true;
                        }
                        break;
                    case up:
                        switch(map[y - 1][x].type) {
                            case leftTurn:
                                c->dir = left;
                                break;
                            case rightTurn:
                                c->dir = right;
                                break;
                            case intersection:
                                turnCart(c);
                                break;
                        }
                        if(map[y - 1][x].cart != nullptr && map[y - 1][x].cart->hasMoved){
                            delete map[y][x].cart;
                            map[y][x].cart = nullptr;
                            map[y - 1][x].cart->dir = crashed;
                            std::cout << "Crash : " << y - 1 << "," << x << "\n";
                            return false;
                        } else {
                            map[y - 1][x].cart = map[y][x].cart;
                            map[y][x].cart = nullptr;
                            c->hasMoved = true;
                        }
                        break;
                    case down:
                        switch(map[y + 1][x].type){
                            case leftTurn:
                                c->dir = right;
                                break;
                            case rightTurn:
                                c->dir = left;
                                break;
                            case intersection:
                                turnCart(c);
                                break;
                        }
                        if(map[y + 1][x].cart != nullptr && map[y + 1][x].cart->hasMoved){
                            delete map[y][x].cart;
                            map[y][x].cart = nullptr;
                            map[y + 1][x].cart->dir = crashed;
                            std::cout << "Crash : " << y + 1 << "," << x << "\n";
                            return false;
                        } else {
                            map[y + 1][x].cart = map[y][x].cart;
                            map[y][x].cart = nullptr;
                            c->hasMoved = true;  
                        }
                        break;
                }
            }
        }
    }
    // Reset movement flag on carts
    for(auto& y: map){
        for(auto& x: y){
            if(x.cart != nullptr){
                x.cart->hasMoved = false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]){
    std::string inputFilePath = "../input.txt";
    std::string exampleInputFilePath = "../exampleInput.txt";

    std::ifstream inputFile(inputFilePath);
    if(inputFile.fail()){
        std::cerr << "Error opening the file " << inputFilePath << "\n";
        return 0;
    }

    Map map = fillMap(inputFile);
    int ticks = 0;
    while(tick(map)){
        ticks++;
        // wait for a crash to happen
    }
    std::cout << "Crash after " << ticks << " ticks\n";
    printMap(map);
    cleanUpMap(map);

    return 0;
}