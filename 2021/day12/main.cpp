#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct Node {
    bool big;
    std::string name;
    std::vector<Node*> connected;
};

int numPathP1(Node* node, std::vector<Node*> visited) {
    auto nVisited = std::find(visited.begin(), visited.end(), node) != visited.end();
    if(!node->big && nVisited) {
        return 0;
    }
    if(node->name == "end") {
        return 1;
    }
    if(!nVisited) {
        visited.push_back(node);
    }
    int numPaths = 0;
    for(auto n : node->connected) {
        numPaths += numPathP1(n, visited);
    }
    return numPaths;
}

int numPathP2(Node* node, std::vector<Node*> visited, bool twice) {
    auto nVisited = std::find(visited.begin(), visited.end(), node) != visited.end();
    if(!node->big && nVisited && twice) {
        return 0;
    }
    if(node->name == "end") {
        return 1;
    }
    if(!nVisited) {
        visited.push_back(node);
    } else if(!node->big) {
        twice = true;
    }
    int numPaths = 0;
    for(auto n : node->connected) {
        if(n->name != "start") {
            numPaths += numPathP2(n, visited, twice);
        }
    }
    return numPaths;
}

int main() {
    const std::string inputFilePath = "../input.txt";
    //const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        std::cout << "err";
        return 1;
    }

    std::vector<Node*> nodes;
    std::string line;
    while(std::getline(inputFile, line)) {
        auto pos = line.find('-');
        std::string start =  line.substr(0, pos);
        std::string end = line.substr(pos+1);

        auto s = std::find_if(nodes.begin(), nodes.end(), [start](const Node* n){return n->name == start;});
        auto e = std::find_if(nodes.begin(), nodes.end(), [end](const Node* n){return n->name == end;});
        Node* startNode;
        Node* endNode;
        bool sExist = false;
        bool eExist = false;
        if(e == nodes.end()) {
            if(std::all_of(end.begin(), end.end(), [](char c){ return std::isupper(c); })) {
                endNode = new Node{true, end};
            } else {
                endNode = new Node{false, end};
            }
        } else {
            endNode = *e;
            eExist = true;
        }
        if(s == nodes.end()) {
            if(std::all_of(start.begin(), start.end(), [](char c){ return std::isupper(c); })) {
                startNode = new Node{true, start};
            } else {
                startNode = new Node{false, start};
            }
        } else {
            startNode = *s;
            sExist = true;
        }
        startNode->connected.push_back(endNode);
        endNode->connected.push_back(startNode);
        if(!sExist) {
            nodes.push_back(startNode);
        }
        if(!eExist) {
            nodes.push_back(endNode);
        }
    }


    for(auto n : nodes) {
        if(n->name == "start") {
            std::cout << "Paths p1 : " << numPathP1(n, std::vector<Node *>{}) << "\n";
            break;
        }
    }

    for(auto n : nodes) {
        if(n->name == "start") {
            std::cout << "Paths p2 : " << numPathP2(n, std::vector<Node *>{}, false) << "\n";
            break;
        }
    }

    // free allocated memory
    for(auto& n : nodes) {
        delete n;
        n = nullptr;
    }
    nodes.clear();
    return 0;
}
