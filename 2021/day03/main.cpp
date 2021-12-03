#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

int binStrToInt(std::string& str) {
    int num = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '1') {
            num |= 1 << (str.size() - i - 1);
        }
    }
    return num;
}

std::vector<int> cntBits(std::vector<std::string>& data) {
    std::vector<int> bits_cnt(data[0].size(), 0);
    for(auto& x : data) {
        for(int i = 0; i < bits_cnt.size(); i++) {
            if(x[i] == '1') {
                bits_cnt[i]++;
            }
        }
    }
    return bits_cnt;
}

int main() {
    const auto INPUT_FILE_PATH = "../input.txt";

    auto inputFile = std::ifstream(INPUT_FILE_PATH);
    if(inputFile.fail()) {
        std::cerr << "error opening file : " << INPUT_FILE_PATH << std::endl;
        return 1;
    }

    std::vector<std::string> data;
    std::string val;
    while(inputFile >> val) {
        data.push_back(val);
    }

    std::vector<int> bits_cnt(data[0].size(), 0);
    for(auto& x : data) {
        for(int i = 0; i < bits_cnt.size(); i++) {
            if(x[i] == '1') {
                bits_cnt[i]++;
            }
        }
    }

    int gama = 0;
    int epsilon = 0;
    for(int i = 0; i < bits_cnt.size() ; i++) {
        int mostCommonBit = bits_cnt[i] > data.size() / 2;
        std::cout << i << " : " << mostCommonBit << ", cnt : " << bits_cnt[i]  << std::endl;
        if(bits_cnt[i] > data.size() / 2) {
            gama |= (1 << (bits_cnt.size() - i - 1));
        } else {
            epsilon |= (1 << (bits_cnt.size() - i - 1));
        }
    }

    std::cout << "gama: " << gama << ", epsilon: " << epsilon << ", power: " << gama * epsilon << std::endl;

    // part 2
    std::vector<std::string> oxygen = data;
    std::vector<std::string> co2 = data;
    auto oxygenBitCnt = bits_cnt;
    auto co2BitCnt = bits_cnt;


    for (int i = 0; i < oxygenBitCnt.size(); i++) {
        double half = oxygen.size() / 2.0;
        char wantedBit = '0';
        if(oxygenBitCnt[i] >= half) {
            wantedBit = '1';
        }
        //std::cout << "i : " << i << ", wantedBit : " << wantedBit << "\n";
        for(auto& v : oxygen) {
            // std::cout << v << "\n";
        }

        std::vector<std::string> goodVals;
        for (auto & j : oxygen) {
            if(j[i] == wantedBit) {
                goodVals.push_back(j);
            }
        }
        if(goodVals.empty()) {
            goodVals.push_back(oxygen.back());
        }
        oxygen = goodVals;
        oxygenBitCnt = cntBits(oxygen);
    }

    for (int i = 0; i < co2BitCnt.size(); i++) {
        double half = co2.size() / 2.0;
        char wantedBit = '0';
        if(co2BitCnt[i] < half) {
            wantedBit = '1';
        }
        //std::cout << "i : " << i << ", wantedBit : " << wantedBit << "\n";
        for(auto& v : co2) {
            // std::cout << v << "\n";
        }

        std::vector<std::string> goodVals;
        for (auto & j : co2) {
            if(j[i] == wantedBit) {
                goodVals.push_back(j);
            }
        }
        if(goodVals.empty()) {
            goodVals.push_back(co2.back());
        }
        co2 = goodVals;
        co2BitCnt = cntBits(co2);
    }


    int oxygenNum = binStrToInt(oxygen.front());
    int co2Num = binStrToInt(co2.front());
    int rating = oxygenNum * co2Num;

    std::cout << "ox: " << oxygenNum << ", CO2: " << co2Num << ", rating: " << rating << std::endl;
    return 0;
}
