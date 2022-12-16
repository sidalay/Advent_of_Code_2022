#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>

struct Position {
    char current{'z'};
    int steps{};
    int x{};
    int y{};
    std::vector<std::string> paths{};
};

bool The_End(Position& Start, char Next) {
    if (Next == 'E') {
        ++Start.steps;
        return true;
    } else {
        return false;
    }
}

bool Can_Move_To(Position& Start, char Next) {
    if (Start.paths.size() >= 2) {
        for (auto& path:Start.paths) {
            // if (Start.paths.back().compare(path));
        }
    }
    if ((Start.current)+1 <= Next) {
        return true;
    } else {
        return false;
    }
    // return (Start.current)+1 <= Next ? true : false;
}

int main() {
    std::ifstream Input{"input.txt"};
    std::string Buffer{};
    std::vector<std::string> HeightMap{};
    Position Pos{};

    while (std::getline(Input,Buffer)) {
        HeightMap.emplace_back(Buffer);
    }
    for (size_t y{}; y < HeightMap.size(); ++y) {
        if (HeightMap.at(y).find('S') != std::string::npos) {
            Pos.x = HeightMap.at(y).find('S');
            Pos.y = y;
            break;
        }
    }


}