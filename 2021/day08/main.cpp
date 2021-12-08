#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <sstream>
#include <numeric>

#define TOP 0
#define LT  1
#define RT  2
#define MID 3
#define LB  4
#define RB  5
#define BOT 6

auto xd() {
    // SMOrc
    std::array<std::string, 7 * 6 * 5 * 4 * 3 * 2 * 1> possiblePatterns;
    std::string pattern = "abcdefg";
    int i = 0;
    do {
        possiblePatterns[i] = pattern;
        i++;
    } while (std::next_permutation(pattern.begin(), pattern.end()));

    return possiblePatterns;
}

int main() {
    const std::string inputFilePath = "../input.txt";
    // const std::string inputFilePath = "../ex.txt";

    std::ifstream inputFile(inputFilePath);

    if (inputFile.fail()) {
        return 1;
    }

    std::string val;
    std::string outputVal;
    std::vector<std::string> signal;
    std::vector<std::string> output;


    while (std::getline(inputFile, val, '|') && std::getline(inputFile, outputVal)) {
        if (val.empty() || outputVal.empty()) {
            continue;
        }
        signal.push_back(val);
        output.push_back(outputVal);
    }

    std::array<int, 10> numSegments = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    std::array<int, 10> numCount{};

    for (const auto &o: output) {
        std::stringstream outStream(o);
        std::string digit;
        while (outStream >> digit) {
            if (digit.size() == numSegments[1]) {
                numCount[1]++;
            } else if (digit.size() == numSegments[4]) {
                numCount[4]++;
            } else if (digit.size() == numSegments[7]) {
                numCount[7]++;
            } else if (digit.size() == numSegments[8]) {
                numCount[8]++;
            }
        }
    }

    std::cout << "P1 : " << std::accumulate(numCount.begin(), numCount.end(), 0) << "\n";

    // p2
    auto possiblePatterns = xd();

    int sum = 0;
    int outIndex = 0;
    for (const auto &v: signal) {
        std::stringstream sstream(v);
        std::string digit;
        std::vector<std::string> commands;
        while (sstream >> digit) {
            std::sort(digit.begin(), digit.end());
            commands.push_back(digit);
        }

        for (auto &p: possiblePatterns) {
            std::array<std::string, 10> digitsPatterns;
            std::stringstream ss0;
            ss0 << p[TOP] << p[LT] << p[RT] << p[LB] << p[RB] << p[BOT];
            digitsPatterns[0] = ss0.str();

            std::stringstream ss1;
            ss1 << p[RT] << p[RB];
            digitsPatterns[1] = ss1.str();

            std::stringstream ss2;
            ss2 << p[TOP] << p[RT] << p[MID] << p[LB] << p[BOT];
            digitsPatterns[2] = ss2.str();

            std::stringstream ss3;
            ss3 << p[TOP] << p[RT] << p[MID] << p[RB] << p[BOT];
            digitsPatterns[3] = ss3.str();

            std::stringstream ss4;
            ss4 << p[LT] << p[RT] << p[MID] << p[RB];
            digitsPatterns[4] = ss4.str();

            std::stringstream ss5;
            ss5 << p[TOP] << p[LT] << p[MID] << p[RB] << p[BOT];
            digitsPatterns[5] = ss5.str();

            std::stringstream ss6;
            ss6 << p[TOP] << p[LT] << p[MID] << p[LB] << p[RB] << p[BOT];
            digitsPatterns[6] = ss6.str();

            std::stringstream ss7;
            ss7 << p[TOP] << p[RT] << p[RB];
            digitsPatterns[7] = ss7.str();

            std::stringstream ss8;
            ss8 << p[TOP] << p[LT] << p[RT] << p[MID] << p[LB] << p[RB] << p[BOT];
            digitsPatterns[8] = ss8.str();

            std::stringstream ss9;
            ss9 << p[TOP] << p[LT] << p[RT] << p[MID] << p[RB] << p[BOT];
            digitsPatterns[9] = ss9.str();

            for (auto &dp: digitsPatterns) {
                std::sort(dp.begin(), dp.end());
            }

            int numMatch = 0;
            for (auto &c: commands) {
                for (auto &dp: digitsPatterns) {
                    if (c == dp) {
                        numMatch++;
                        break;
                    }
                }
            }
            if (numMatch >= commands.size()) {
                std::stringstream outStream(output[outIndex]);
                std::string out;
                int num = 0;
                while (outStream >> out) {
                    std::sort(out.begin(), out.end());
                    for (int i = 0; i < digitsPatterns.size(); i++) {
                        if (out == digitsPatterns[i]) {
                            num = num * 10 + i;
                        }
                    }
                }
                sum += num;
                break;
            }
        }
        outIndex++;
    }
    std::cout << "P2 : " << sum << "\n";
    return 0;
}
