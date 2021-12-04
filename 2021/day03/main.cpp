#include <iostream>
#include <fstream>
#include <vector>
#include <string>


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

    std::vector<int> bits_cnt = cntBits(data);

    std::string gamaStr(bits_cnt.size(), '0');
    for(int i = 0; i < bits_cnt.size() ; i++) {
        if(bits_cnt[i] > data.size() / 2) {
            gamaStr[i] = '1';
        }
    }

    unsigned int gama = std::stoi(gamaStr, nullptr, 2);
    unsigned int bitsToShift = (sizeof(gama) * 8 - bits_cnt.size());
    // invert gama to get epsilon and remove the extra ones at the start of the number
    unsigned int epsilon = (~gama << bitsToShift) >> bitsToShift;

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


    int oxygenNum = std::stoi(oxygen.front(), nullptr, 2);
    int co2Num = std::stoi(co2.front(), nullptr, 2);
    int rating = oxygenNum * co2Num;

    std::cout << "Oxygen: " << oxygenNum << ", CO2: " << co2Num << ", rating: " << rating << std::endl;
    return 0;
}
