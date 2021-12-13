#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Direction {
    up,
    left
};

struct Fold {
    Direction direction;
    int position;
};
void foldLeft(const int pos, std::vector<std::vector<bool>>& paper) {
    std::vector<std::vector<bool>> newPaper;
    newPaper.resize(paper.size());
    for(int y = 0; y < paper.size(); y++) {
        newPaper[y].resize(pos);
        for(int x = 0; x < pos; x++) {
            int xPos = pos * 2 - x;
            if(xPos < paper[y].size()) {
                newPaper[y][x] = paper[y][x] || paper[y][xPos];
            } else {
                newPaper[y][x] = paper[y][x];
            }
        }
    }
    paper = newPaper;
}

void foldUp(const int pos, std::vector<std::vector<bool>>& paper) {
    std::vector<std::vector<bool>> newPaper;
    newPaper.resize(pos);
    for(int y = 0; y < pos; y++) {
        newPaper[y].resize(paper[y].size());
        for(int x = 0; x < paper[y].size(); x++) {
            int yPos = pos * 2 - y;
            if(yPos < paper.size()) {
                newPaper[y][x] = paper[y][x] || paper[yPos][x];
            } else {
                newPaper[y][x] = paper[y][x];
            }
        }
    }
    paper = newPaper;
}

void fold(const Fold& fold, std::vector<std::vector<bool>>& paper) {
    if(fold.direction == left) {
        foldLeft(fold.position, paper);
    } else {
        foldUp(fold.position, paper);
    }
}

void printPaper(const std::vector<std::vector<bool>>& paper) {
    for(const auto& y : paper) {
        for (const auto& x : y) {
            if(x) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        std::cout << "err";
        return 1;
    }
    std::vector<std::vector<bool>> paper(10, std::vector<bool>(10, false));
    std::vector<Fold> folds;
    std::string line;
    while(std::getline(inputFile, line)) {
        if(line.empty()) {
            continue;
        }
        auto pos = line.find(',');
        if(pos == std::string::npos ) {
            auto equal = line.find('=');
            std::string direction = line.substr(equal - 1, 1);
            int position = std::stoi(line.substr(equal + 1));
            Direction d = direction == "x" ? left : up;
            folds.push_back({d, position});
        } else {
            unsigned int x = std::stoi(line.substr(0, pos));
            unsigned int y = std::stoi(line.substr(pos + 1));
            if(paper.size() <= y) {
                paper.resize(y + 1);
            }
            if(paper[y].size() <= x) {
                auto newSize = std::max(x+1, paper[0].size());
                for(auto& l : paper) {
                    l.resize(newSize);
                }
            }
            paper[y][x] = true;
        }
    }

    bool first = true;

    for(auto& f : folds) {
        fold(f, paper);
        if(first) {
            first = false;
            int numDots = 0;
            for(const auto& y : paper) {
                for (const auto& x : y) {
                    if(x) {
                        numDots++;
                    }
                }
            }
            std::cout << "P1 : " << numDots << "\n";
        }
    }

    // P2 : you need to read the output
    printPaper(paper);
    return 0;
}
