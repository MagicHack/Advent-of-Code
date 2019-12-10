#include <iostream>
#include <fstream>
#include <vector>

void readProgram(std::istream &input, std::vector<int> &programm) {
    // We assume one int, one char
    int code;
    char separator;
    bool isCode = true;
    while (!input.eof()) {
        if (isCode) {
            isCode = false;
            input >> code;
            programm.push_back(code);
        } else {
            isCode = true;
            input >> separator;
        }
    }
}

void printProgramm(std::vector<int> &program) {
    for (int i = 0; i < program.size(); i++) {
        if (i % 4 == 0) {
            std::cout << "\n";
        }
        std::cout << program[i] << ", ";
    }
}

enum Opcode {
    ADD = 1, MUL = 2, END = 99
};

// Execute one instruction of Intcode
bool step(std::vector<int> &program, int &instructionPointer) {
    int position1 = program[instructionPointer + 1];
    int position2 = program[instructionPointer + 2];
    int positionResult = program[instructionPointer + 3];
    switch (program[instructionPointer]) {
        case ADD:
            program[positionResult] = program[position1] + program[position2];
            break;
        case MUL:
            program[positionResult] = program[position1] * program[position2];
            break;
        case END:
            return false;
        default:
            std::cout << "unknown\n";
            break;
    }
    instructionPointer += 4;
    // printProgramm(program);
    return true;
}

int execute(std::vector<int> program) {
    int instructionPointer = 0;
    while (step(program, instructionPointer));
    return program[0];
}

int main() {
    // std::string inputPath = "../example.txt";
    std::string inputPath = "../input.txt";
    std::ifstream inputFile(inputPath);
    if (inputFile.fail()) {
        std::cerr << "Error opening file : " << inputPath;
        return 0;
    }

    std::vector<int> originalProgram;
    readProgram(inputFile, originalProgram);

    auto program = originalProgram;

    // Part 1
    // Values to replace
    program[1] = 12;
    program[2] = 2;
    std::cout << "Part 1 : " << execute(program) << "\n";

    // Part 2
    int expectedResult = 19690720;
    int verb = 0, noun = 0;
    [&] {
        for(noun = 0; noun <= 99; noun++) {
            for(verb = 0; verb <= 99; verb++) {
                program = originalProgram;
                program[1] = noun;
                program[2] = verb;
                if(execute(program) == expectedResult) {
                    return;
                }
            }
        }
    }();
    std::cout << "Part 2 : " << 100 * noun + verb;
    return 0;
}
