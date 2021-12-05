#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

struct Point {
    int x;
    int y;
};

struct Line {
    Point start;
    Point end;
};

bool operator==(const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const Line &l1, const Line &l2) {
    return l1.start == l2.start && l1.end == l2.end;
}


Point lineIntersection(const Line &line1, const Line &line2) {
    Point intersection{};
    // y = ax + b
    double a1 = (double) (line1.end.y - line1.start.y) / (line1.end.x - line1.start.x);
    double a2 = (double) (line2.end.y - line2.start.y) / (line2.end.x - line2.start.x);

    double b1 = line1.start.y - a1 * line1.start.x;
    double b2 = line2.start.y - a2 * line2.start.x;

    // we assume the intersection is always an int
    intersection.x = (b2 - b1) / (a1 - a2);
    intersection.y = a1 * intersection.x + b1;

    return intersection;
}

bool horizontalOrVerticalLine(const Line &line) {
    return line.start.x == line.end.x || line.start.y == line.end.y;
}

bool readLine(std::istream &istream, Line &newLine) {
    Point &p1 = newLine.start;
    Point &p2 = newLine.end;
    std::string temp;
    char tempC;
    int i = 0;
    while (istream.get(tempC)) {
        if (tempC != ' ' && tempC != '-' && tempC != '>' && tempC != ',' && tempC != '\n') {
            temp.push_back(tempC);
        } else if (!temp.empty()) {
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
        if (tempC == '\n' || istream.peek() == EOF) {
            return true;
        }
    }
    return false;
}

int main() {
    const auto INPUT_FILE_PATH = "../input.txt";

    auto inputFile = std::ifstream(INPUT_FILE_PATH);
    if (inputFile.fail()) {
        std::cerr << "error opening file : " << INPUT_FILE_PATH << std::endl;
        return 1;
    }


    std::vector<Line> lines;

    std::string value;

    Line tempLine{};
    while (readLine(inputFile, tempLine)) {
        lines.push_back(tempLine);
    }
    std::vector<Line> hvLines;
    for (auto &l: lines) {
        if (horizontalOrVerticalLine(l)) {
            hvLines.push_back(l);
        }
    }

    for(auto& l : hvLines) {
        lines.erase(find(lines.begin(), lines.end(), l));
    }


    std::vector<std::pair<Point, int>> intersections;

    // h/v lines
    for (auto &line: hvLines) {
        for (int x = std::min(line.start.x, line.end.x); x <= std::max(line.start.x, line.end.x); x++) {
            for (int y = std::min(line.start.y, line.end.y); y <= std::max(line.start.y, line.end.y); y++) {
                Point newPoint = {x, y};
                auto pos = std::find_if(intersections.begin(), intersections.end(),
                                        [newPoint](std::pair<Point, int> x) { return x.first == newPoint; });
                if (pos != intersections.end()) {
                    pos->second++;
                } else {
                    intersections.emplace_back(newPoint, 1);
                }
            }
        }
    }

    int countP1 = 0;
    for (auto &inter: intersections) {
        if (inter.second >= 2) {
            countP1++;
        }
    }

    std::cout << "P1 : " << countP1 << std::endl;

    // 45° lines
    for (auto &line: lines) {
        bool yPositive = false;
        int y = line.end.y;
        if(line.start.x < line.end.x) {
            y = line.start.y;
            if(line.start.y < line.end.y) {
                yPositive = true;
            }
        } else {
            if(line.end.y < line.start.y) {
                yPositive = true;
            }
        }
        for(int x = std::min(line.start.x, line.end.x); x <= std::max(line.start.x, line.end.x); x++) {
            Point newPoint = {x, y};
            // std::cout << x << "," << y << '\n';
            auto pos = std::find_if(intersections.begin(), intersections.end(),
                                    [newPoint](std::pair<Point, int> x) { return x.first == newPoint; });
            if (pos != intersections.end()) {
                pos->second++;
            } else {
                intersections.emplace_back(newPoint, 1);
            }
            if(yPositive) {
                y++;
            } else {
                y--;
            }
        }
    }
    
    int countP2 = 0;
    for (auto &inter: intersections) {
        if (inter.second >= 2) {
            countP2++;
        }
    }

    std::cout << "P2 : " << countP2 << std::endl;

    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
            Point newPoint = {x, y};
            auto pos = std::find_if(intersections.begin(), intersections.end(),
                                    [newPoint](std::pair<Point, int> x) { return x.first == newPoint; });
            if(pos == intersections.end()) {
                std::cout << '*';
            } else {
                std::cout << pos->second;
            }
        }
        std::cout << "\n";
    }
    return 0;
}
