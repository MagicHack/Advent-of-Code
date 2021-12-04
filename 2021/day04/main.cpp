#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

const int BINGO_SIZE = 5;

struct BingoCase {
    int number;
    bool marked;
};

class BingoBoard {
private:
    std::vector<std::vector<BingoCase>> rows_;
    int lastMarked_ = -1;
public:
    BingoBoard() = default;

    bool markNumber(int num) {
        lastMarked_ = num;
        for (auto &row: rows_) {
            for (auto &bCase: row) {
                if (bCase.number == num) {
                    bCase.marked = true;
                }
            }
        }
        return isWinner();
    }

    bool isWinner() {
        // check if rows_ are winning
        for (const auto &row: rows_) {
            bool winningRow = true;
            for (const auto &c: row) {
                if (!c.marked) {
                    winningRow = false;
                    break;
                }
            }
            if (winningRow) {
                return winningRow;
            }
        }
        // check if columns are winning
        for (std::size_t i = 0; i < rows_.size(); i++) {
            bool winningCol = true;
            for (const auto &row: rows_) {
                if (!row[i].marked) {
                    winningCol = false;
                    break;
                }
            }
            if (winningCol) {
                return winningCol;
            }
        }
        return false;
    }

    /**
     * Adds a new row to the bingo board
     * @param row row to add
     * @return true if the row was added or false if it's already full
     */
    bool addRow(const std::vector<int> &row) {
        if (rows_.size() < BINGO_SIZE) {
            std::vector<BingoCase> newRow;
            newRow.reserve(row.size());

            for (const auto x: row) {
                newRow.push_back({x, false});
            }
            rows_.push_back(newRow);
            return true;
        }
        return false;
    }

    std::size_t getNumRows() {
        return rows_.size();
    }

    int getScore() {
        int score = 0;
        for(const auto& r : rows_) {
            for(const auto& c : r) {
                if(!c.marked) {
                    score += c.number;
                }
            }
        }
        return score * lastMarked_;
    }

    friend std::ostream& operator<<(std::ostream& os, const BingoBoard& b);

};


// overload << to easily print bingo boards
std::ostream& operator<<(std::ostream& os, const BingoBoard& b) {
    for(const auto& r : b.rows_) {
        for(const auto& c : r) {
            os << c.number;
            if(c.marked) {
                os << '*';
            }
            os << ' ';
        }
        os << "\n";
    }
    return os;
}

int main() {
    const auto INPUT_FILE_PATH = "../input.txt";

    auto inputFile = std::ifstream(INPUT_FILE_PATH);
    if (inputFile.fail()) {
        std::cerr << "error opening file : " << INPUT_FILE_PATH << std::endl;
        return 1;
    }

    // "random" numbers to use
    std::vector<int> rngNumbers;

    std::vector<int> row;

    // read , separated numbers for "rng"
    std::string firstLine;
    std::getline(inputFile, firstLine);
    std::stringstream flStream(firstLine);

    std::string num;
    while (std::getline(flStream, num, ',')) {
        rngNumbers.push_back(std::stoi(num));
    }

    std::vector<BingoBoard> boards = {BingoBoard()};

    int val = 0;
    // Read all bingo boards
    while (inputFile >> val) {
        if (row.size() < BINGO_SIZE) {
            row.push_back(val);
        } else {
            // add full row to board
            if(!boards.back().addRow(row)) {
                auto newBoard = BingoBoard();
                newBoard.addRow(row);
                boards.push_back(newBoard);
            }
            row.clear();
            row.push_back(val);
        }
    }
    // add last row
    boards.back().addRow(row);

    std::unique_ptr<BingoBoard> lastWinner = nullptr;

    for(auto x : rngNumbers) {
        for(auto& b : boards) {
            // don't mark already winning boards
            if(!b.isWinner()) {
                if(b.markNumber(x)) {
                    if(lastWinner == nullptr) {
                        std::cout << "Part 1: first winning board\n\tScore: " << b.getScore()
                        << "\n" << b << "\n";
                    }
                    lastWinner = std::make_unique<BingoBoard>(b);
                }
            }
        }
    }

    std::cout << "Part 2: last winner\n\tScore: " << lastWinner->getScore() << "\n\n" << *lastWinner;

    return 0;
}
