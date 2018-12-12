#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

int part1(std::vector<std::string>& lines){
    int n2 = 0, n3 = 0;
    for(auto l: lines){
        bool has2occurences = false;
        bool has3occurences = false;
        for(char c = 'a'; c <= 'z'; c++){
            long count = std::count(l.begin(), l.end(), c);
            switch(count){
                case 2:
                    has2occurences = true;
                    break;
                case 3:
                    has3occurences = true;
                    break;
                default:
                    break;
            }
            if(has2occurences && has3occurences) break;
        }
        if(has2occurences) n2++;
        if(has3occurences) n3++;
    }
    int checksum = n2 * n3;
    return checksum;
}

std::string part2(std::vector<std::string>& lines){
    for(auto l: lines){
        for(auto l2: lines){
            std::string same;
            int diffs = 0;
            for(int i = 0; i < l.size(); i++){
                if(l[i] == l2[i]){
                    same += l[i];
                } else {
                    diffs++;
                    if(diffs > 1) break;
                }
            }
            if(diffs == 1){
                return same;
            }
        }
    }
    return "Nothing found...";
}

int main() {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);
    if(inputFile.fail()){
        std::cerr << "Error opening the file " << inputFilePath << "\n";
        return 0;
    }

    std::string line;
    std::vector<std::string> lines;
    while(std::getline(inputFile, line)){
        if(line.empty()) continue;
        lines.push_back(line);
    }

    std::cout << "Part 1 :\n\tChecksum : " << part1(lines) << "\n";
    std::cout << "Part 2 :\n\tCommon letters : " << part2(lines) << "\n";
    return 0;
}