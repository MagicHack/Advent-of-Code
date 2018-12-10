#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>

int react(std::string polymer);
int part2Thread(std::string polymer, char c);
int reactFaster(const std::string& polymer);

int main(int argc, char* argv[]) {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);

    if(inputFile.fail()){
        std::cerr << "Error opening file \"" << inputFilePath << "\"n";
        return 0;
    }

    std::string line;
    std::string polymer;
    while(std::getline(inputFile, line)){
        polymer += line;
    }
    // Part 1
    int startingUnits = polymer.size();
    int remainingUnits = reactFaster(polymer);

    std::cout << "Part 1:\n" << "\tStarting units : " << startingUnits << "\n\tRemaining units : " << remainingUnits << "\n";

    // Part 2
    std::vector<int> polymerSizes = {remainingUnits};
    std::vector<std::future<int>> threads;

    unsigned maxThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads : " << maxThreads << "\n";

    for(char c = 'A'; c <= 'Z'; c++){
        while(threads.size() >= maxThreads){ // Wait for a thread to finish
            for(int i = 0; i < threads.size(); i++){
                if(threads[i].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
                    polymerSizes.push_back(threads[i].get());
                    threads.erase(threads.begin() + i);
                }
            }
        }
        threads.push_back(std::async(std::launch::async, part2Thread, polymer, c)); // Launch thread
    }

    // Fetch results from remaining threads
    for(auto &thread : threads) {
        polymerSizes.push_back(thread.get());
    }
    
    int minimumSize = *std::min_element(polymerSizes.begin(), polymerSizes.end());
    std::cout << "Part 2:\n" << "\tMinimum units : " << minimumSize << "\n";

    return 0;
}

int part2Thread(std::string polymer, char c) {
    polymer.erase(std::remove(polymer.begin(), polymer.end(), c), polymer.end());
    polymer.erase(std::remove(polymer.begin(), polymer.end(), std::tolower(c)), polymer.end());
    return reactFaster(polymer);
}
// Second solution : much faster - threading is kinda usuless now
int reactFaster(const std::string& polymer){
    std::string result = "-"; // begin with a lenght of one so [end() - 1] does not segfault
    for(auto c: polymer) {
        if(c != *(result.end() - 1) && tolower(c) == tolower(*(result.end() - 1))){
            result.pop_back();
        } else{
            result.push_back(c);
        }
    }
    return result.size() - 1;
}
// First solution : works but very slowly
int react(std::string polymer){
    bool destroyed;
    do{
        destroyed = false;
        for(int i = 0; i < polymer.size() - 1; i++){
            if(polymer[i] != polymer[i + 1] && std::tolower(polymer[i]) == std::tolower(polymer[i + 1])){
                polymer.erase(i, 2);
                destroyed = true;
                break;
            }
        }
    } while(destroyed);

    return polymer.size();
}
