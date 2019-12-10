#include <iostream>
#include <fstream>
#include <vector>

void readProgram(std::istream& input, std::vector<int>& programm) {
    // We assume one int, one char
    int code;
    char separator;
    bool isCode = true;
    while(!input.eof()) {
        if(isCode) {
            isCode = false;
            input >> code;
            programm.push_back(code);
        } else {
            isCode = true;
            input >> separator;
        }
    }
}

void printProgramm(std::vector<int>& program) {
    for(int i = 0; i < program.size(); i++) {
        if(i % 4 == 0) {
            std::cout << "\n";
        }
        std::cout << program[i] << ", ";
    }
}

enum Opcode {ADD = 1, MUL = 2, END = 99};

bool step(std::vector<int>& program, int& instructionPointer) {
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

void execute(std::vector<int> program) {
    int instructionPointer = 0;
    while(step(program, instructionPointer));
    std::cout << "Value at pos 0 : " << program[0] << "\n";
}

int main() {
    // std::string inputPath = "../example.txt";
    std::string inputPath = "../input.txt";
    std::ifstream inputFile(inputPath);
    if(inputFile.fail()) {
        std::cerr << "Error opening file : " << inputPath;
        return 0;
    }

    std::vector<int> programm;
    readProgram(inputFile, programm);

    // Values to replace
    programm[1] = 12;
    programm[2] = 2;

    execute(programm);
    return 0;
}
