#include <iostream>
#include <fstream>
#include <vector>

class Point {
public:
    Point(int x = 0, int y = 0, int vx = 0, int vy = 0) : x_(x), y_(y), vx_(vx), vy_(vy) {};
    void move() {
        x_ += vx_;
        y_ += vy_;
    }
    void moveBack(){
        x_ -= vx_;
        y_ -= vy_;
    }
    void print(){
        std::cout << "Pos(" << x_ << ", " << y_ << ")\tVel(" << vx_ << ", " << vy_ << ")\n";
    }
    int x_, y_, vx_, vy_;
};

Point parsePoint(std::string line);

class Sky {
public:
    Sky() = default;
    void addPoint(Point p){
        points_.push_back(p);
    }

    void print(){
        Point maxSize = getMaxSizeXY();
        Point minXY = getMinXY();
        std::vector<std::vector<char>> skyPrint(maxSize.y_ + 1, std::vector<char>(maxSize.x_ + 1, '.')); // Fill 2d vector with dots

        // Replace the dots by # where the points are
        for(auto p: points_){
            int x = p.x_ - minXY.x_;
            int y = p.y_ - minXY.y_;
            skyPrint[y][x] = '#';
        }

        for(auto y: skyPrint){
            for(auto x: y){
                std::cout << x;
            }
            std::cout << "\n";
        }
    }

    Point getMaxSizeXY(){
        int maxX = points_[0].x_, maxY = points_[0].y_, minX = points_[0].x_, minY = points_[0].y_;
        for(auto p: points_){
            if(p.x_ > maxX) maxX = p.x_;
            if(p.y_ > maxY) maxY = p.y_;

            if(p.x_ < minX) minX = p.x_;
            if(p.y_ < minY) minY = p.y_;
        }
        return Point(abs(maxX - minX), abs(maxY - minY));
    }

    Point getMinXY(){
        int maxX = points_[0].x_, maxY = points_[0].y_, minX = points_[0].x_, minY = points_[0].y_;
        for(auto p: points_){
            if(p.x_ > maxX) maxX = p.x_;
            if(p.y_ > maxY) maxY = p.y_;

            if(p.x_ < minX) minX = p.x_;
            if(p.y_ < minY) minY = p.y_;
        }
        return Point(minX, minY);
    }

    void move(){
        for(auto& p: points_){
            p.move();
        }
    }

    void moveBack(){
        for(auto& p: points_){
            p.moveBack();
        }
    }

private:
    std::vector<Point> points_;
};

int main() {
    std::string inputFilePath = "../input.txt";
    std::ifstream inputFile(inputFilePath);
    if(inputFile.fail()){
        std::cerr << "Error opening file : " << inputFilePath << "\n";
        return 0;
    }

    Sky sky = Sky();
    std::string line;
    while(std::getline(inputFile, line)){
        if(line.empty()){
            continue;
        }
        sky.addPoint(parsePoint(line));
    }

    int seconds = 0;
    Point maxSize = sky.getMaxSizeXY();
    Point currentSize = maxSize;
    while (currentSize.x_ <= maxSize.x_ && currentSize.y_ <= maxSize.y_){
        maxSize = currentSize;
        seconds++;
        sky.move();
        currentSize = sky.getMaxSizeXY();
    }
    sky.moveBack();
    seconds--;
    std::cout << "Max size is :" << maxSize.x_ << "x" << maxSize.y_<< "\nAfter " << seconds << " seconds" << "\n";
    sky.print();
    return 0;
}


Point parsePoint(std::string line){
    Point p = Point();
    p.x_ = std::stoi(line.substr(line.find('<') + 1, line.find(',') - line.find('<') - 1));
    p.y_ = std::stoi(line.substr(line.find(',') + 1, line.find('>') - line.find(',') - 1));
    line = line.substr(line.find('>') + 1);
    p.vx_ = std::stoi(line.substr(line.find('<') + 1, line.find(',') - line.find('<') - 1));
    p.vy_ = std::stoi(line.substr(line.find(',') + 1, line.find('>') - line.find(',') - 1));
    return p;
}