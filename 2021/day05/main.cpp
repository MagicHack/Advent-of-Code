#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

struct Point {
    int x;
    int y;
};

bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

struct Line {
    Point start;
    Point end;
};

/*Point lineIntersection(const Line& line1, const Line& line2) {
    Point intersection{};
    // y = ax + b
    double a1 = (line1.end.y - line1.start.y) / (line1.end.x - line1.start.x);
    double a2 = (line2.end.y - line2.start.y) / (line2.end.x - line2.start.x);

    double b1 = line1.start.y - a1 * line1.start.x;
    double b2 = line2.start.y - a2 * line2.start.x;

    intersection.x = (b2 - b1) / (a1 - a2);
    intersection.y = a1 * intersection.x + b1;

    return intersection;
}*/

bool horizontalOrVerticalLine(const Line& line) {
    return  line.start.x == line.end.x || line.start.y == line.end.y;
}

bool readLine(std::istream& istream, Line& newLine) {
    Point& p1 = newLine.start;
    Point& p2 = newLine.end;
    std::string temp;
    char tempC;
    int i = 0;
    while (istream.get(tempC)) {
        if (tempC != ' ' && tempC != '-' && tempC != '>' && tempC != ',' && tempC != '\n') {
            temp.push_back(tempC);
        } else if(!temp.empty()){
            int num = std::stoi(temp);
            temp.clear();
            switch (i) {
                case 0:
                    p1.x = num;
                    break;
                case 1:
                    p1.y = num;
                    break;
                case 2:
                    p2.x = num;
                    break;
                case 3:
                    p2.y = num;
                    break;
                default:
                    std::cout << "dank" << std::endl;
                    break;
            }
            i++;
        }
        if (tempC == '\n') {
            return true;
        }
    }
    return false;
}

int main() {
    const auto INPUT_FILE_PATH = "../input.txt";

    auto inputFile = std::ifstream(INPUT_FILE_PATH);
    if(inputFile.fail()) {
        std::cerr << "error opening file : " << INPUT_FILE_PATH << std::endl;
        return 1;
    }


    std::vector<Line> lines;

    std::string value;

    Line tempLine{};
    while(readLine(inputFile, tempLine)) {
        lines.push_back(tempLine);
    }
    std::vector<Line> hvLines;
    for(auto& l : lines) {
        if(horizontalOrVerticalLine(l)) {
            hvLines.push_back(l);
        }
    }

    std::vector<std::pair<Point, int>> intersections;
    for(std::size_t i = 0; i < hvLines.size(); i++) {
        for(std::size_t j = 0; j < hvLines.size(); j++) {
            if(i == j) {
                continue;
            }
            Line& line1 = hvLines[i];
            Line& line2 = hvLines[j];
            // check each point of each line xD
            for(int x = std::min(line1.start.x, line1.end.x); x <= std::max(line1.start.x, line1.end.x); x++) {
                for(int y = std::min(line1.start.y, line1.end.y); y <= std::max(line1.start.y, line1.end.y); y++) {
                    for(int x2 = std::min(line2.start.x, line2.end.x); x2 <= std::max(line2.start.x, line2.end.x); x2++) {
                        for(int y2 = std::min(line2.start.y, line2.end.y); y2 <= std::max(line2.start.y, line2.end.y); y2++) {
                            if(x == x2 && y == y2) {
                                Point currentIntersection = {x, y};
                                bool found = false;
                                for(auto& p : intersections) {
                                    if(p.first == currentIntersection) {
                                        p.second++;
                                        found = true;
                                        break;
                                    }
                                }
                                if(!found) {
                                    intersections.emplace_back(currentIntersection, 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int count = 0;
    for(auto& inter : intersections) {
        if(inter.second >= 2) {
            count++;
        }
    }

    std::cout << count;
    return 0;
}
