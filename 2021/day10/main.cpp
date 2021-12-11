#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        std::cerr << "Err file";
        return 1;
    }
    std::vector<std::string> data;
    std::string line;
    while(std::getline(inputFile, line)) {
        data.push_back(line);
    }

    std::array<char, 4> openingChars{'(', '[', '{', '<'};
    std::array<char, 4> closingChars{')', ']', '}', '>'};

    std::array<int, 4> invalidCharScores{3, 57, 1197, 25137};

    int invalidScore = 0;
    std::vector<uint64_t> completionScores;
    for(const auto& l : data) {
        std::vector<char> expectedClosingStack;
        bool corrupted = false;
        for(const auto& c : l) {
            for(int i = 0; i < openingChars.size(); i++) {
                if(c == openingChars[i]) {
                    expectedClosingStack.push_back(closingChars[i]);
                } else if(c == closingChars[i]) {
                    if(!expectedClosingStack.empty() && expectedClosingStack.back() == c) {
                        expectedClosingStack.pop_back();
                    } else {
                        // std::cout << "Score : " << invalidCharScores[i] << " " << c << " invalid expected : " << expectedClosingStack.back() << " " << l << "\n";
                        invalidScore += invalidCharScores[i];
                        corrupted = true;
                        break;
                    }
                }
            }
            if(corrupted) {
                break;
            }
        }
        if(!corrupted) {
            uint64_t completionScore = 0;
            while (!expectedClosingStack.empty()) {
                int cScore = 0;
                switch (expectedClosingStack.back()) {
                    case ')':
                        cScore = 1;
                        break;
                    case ']':
                        cScore = 2;
                        break;
                    case '}':
                        cScore = 3;
                        break;
                    case '>':
                        cScore = 4;
                        break;
                }
                completionScore = completionScore * 5 + cScore;
                expectedClosingStack.pop_back();
            }
            completionScores.push_back(completionScore);
        }

    }

    std::sort(completionScores.begin(), completionScores.end());

    uint64_t midScore = completionScores[completionScores.size() / 2];

    std::cout << "P1 score : " << invalidScore << "\n";
    std::cout << "P2 mid score : " << midScore << "\n";
    return 0;
}
