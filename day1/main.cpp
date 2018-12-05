#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()){
        std::cerr << "Error opening file : \"" << inputFilePath <<  "\"\n";
        return 0;
    }

    int resultingFrequency = 0, variation = 0, firstFreqTwice = 0;
    std::vector<int> allInputFreq;
    std::set<int> allResFreq = {resultingFrequency};
    bool foundFreqTwice = false;

    while(inputFile >> variation){
        allInputFreq.push_back(variation);
        resultingFrequency += variation;
        if(!foundFreqTwice){
            if(!allResFreq.insert(resultingFrequency).second){ // Insert fails in set if the value already exist
                // Found first frequency that appears twice
                foundFreqTwice = true;
                firstFreqTwice = resultingFrequency;
            }
        }
    }

    int answerProblem1 = resultingFrequency;

    // If no duplicate frequencies where found loop over the input frequencies and add to the resulting frequency
    for(int i = 0; !foundFreqTwice; i++){
        if(!allResFreq.insert(resultingFrequency += allInputFreq[i % allInputFreq.size()]).second){
            // Found first frequency that appears twice
            foundFreqTwice = true;
            firstFreqTwice = resultingFrequency;
        }
    }
    std::cout << "Resulting frequency : " << answerProblem1 << "\n";
    std::cout << "First frequency found twice : " << firstFreqTwice << "\n";
    return 0;
}