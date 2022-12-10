#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <set>
#include <utility>
#include <vector>

struct Coordinate {
    int x{};
    int y{};
    std::set<std::pair<int,int>> Positions{{0,0}};
};

void move_tail(Coordinate& Tail, Coordinate& Head) {
    Coordinate Quadrant{Head.x - Tail.x, Head.y - Tail.y};
    if (abs(Quadrant.x) < 2 && abs(Quadrant.y) < 2) {
        return;
    }
    if (Quadrant.x > 0 && Quadrant.x <= 2) {
        Tail.x += 1;
    } else if (Quadrant.x < 0 && Quadrant.x >= -2) {
        Tail.x -= 1;
    }
    if (Quadrant.y > 0 && Quadrant.y <= 2) {
        Tail.y += 1;
    } else if (Quadrant.y < 0 && Quadrant.y >= -2) {
        Tail.y -= 1;
    }
    Tail.Positions.emplace(Tail.x, Tail.y);
}

int main() {
    std::ifstream Input{"input.txt"};
    std::vector<Coordinate> Knots{{},{},{},{},{},{},{},{},{},{}};
    std::string Buffer;
    while (std::getline(Input, Buffer)) {
        std::string_view Direction{Buffer.data(),1};
        std::string_view Spaces{Buffer.begin()+2,Buffer.end()};
        int Move{std::atoi(Spaces.data())};

        for (int x{}; x < Move; ++x) {
            if (Direction == "L") {
                Knots.at(0).x -= 1;
            }
            else if (Direction == "U") {
                Knots.at(0).y -= 1;
            }
            else if (Direction == "R") {
                Knots.at(0).x += 1;
            }
            else if (Direction == "D") {
                Knots.at(0).y += 1;
            }
            for (int y{1}; y < Knots.size(); ++y) {
                move_tail(Knots.at(y), Knots.at(y-1));
            }
        }
    }
    std::cout << "Part 1: " << Knots.at(1).Positions.size() 
              << "\nPart 2: " << Knots.at(9).Positions.size() << std::endl;
    Input.close();
    return 0;
}