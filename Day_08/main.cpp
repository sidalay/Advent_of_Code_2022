#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

#define todigit(c) (c-'0')

struct Coordinate {
    int x{};
    int y{};
};

bool Is_Visible(Coordinate Pos, std::vector<std::string>& Trees) {
    const int MaxRow{static_cast<int>(Trees.size())};
    const int MaxColumn{static_cast<int>(Trees.at(0).size())};
    bool Above{true};
    bool Below{true};
    bool Left {true};
    bool Right{true};

    if (Pos.x == 0 || Pos.x == MaxRow-1) {
        return true;
    } else if (Pos.y == 0 || Pos.y == MaxColumn-1) {
        return true;
    } else {
        for (int Row{}; Row < MaxRow ; ++Row) {
            if (Row != Pos.x) {
                if (Row < Pos.x) {
                    if (todigit(Trees.at(Pos.x).at(Pos.y)) <= todigit(Trees.at(Row).at(Pos.y))) {
                        Above = false;
                    }
                } else {
                    if (todigit(Trees.at(Pos.x).at(Pos.y)) <= todigit(Trees.at(Row).at(Pos.y))) {
                        Below = false;
                    }
                }
            } else {
                for (int Col{}; Col < MaxColumn; ++Col) {
                    if (Col != Pos.y) {
                        if (Col < Pos.y) {
                            if (todigit(Trees.at(Pos.x).at(Pos.y)) <= todigit(Trees.at(Row).at(Col))) {
                                Left = false;
                            }
                        } else {
                            if (todigit(Trees.at(Pos.x).at(Pos.y)) <= todigit(Trees.at(Row).at(Col))) {
                                Right = false;
                            }

                        }
                    }
                }
            }
        }
    }
    if (Above || Below || Left || Right) {
        return true;
    } else {
        return false;
    }
}

int Best_Tree(Coordinate Pos, std::vector<std::string> Trees) {
    const int MaxRow{static_cast<int>(Trees.size())};
    const int MaxColumn{static_cast<int>(Trees.at(0).size())};
    int Above{};
    int Below{};
    int Left{};
    int Right{};
    
    for (int Row{Pos.x-1}; Row >= 0; --Row) {
        if (todigit(Trees.at(Pos.x).at(Pos.y)) > todigit(Trees.at(Row).at(Pos.y))) {
            ++Above;
        } else {
            ++Above;
            break;
        }
    }
    for (int Row{Pos.x+1}; Row < MaxRow; ++Row) {
        if (todigit(Trees.at(Pos.x).at(Pos.y)) > todigit(Trees.at(Row).at(Pos.y))) {
            ++Below;
        } else {
            ++Below;
            break;
        }
    }
    for (int Col{Pos.y-1}; Col >= 0; --Col) {
        if (todigit(Trees.at(Pos.x).at(Pos.y)) > todigit(Trees.at(Pos.x).at(Col))) {
            ++Left;
        } else {
            ++Left;
            break;
        }
    }
    for (int Col{Pos.y+1}; Col < MaxColumn; ++Col) {
        if (todigit(Trees.at(Pos.x).at(Pos.y)) > todigit(Trees.at(Pos.x).at(Col))) {
            ++Right;
        } else {
            ++Right;
            break;
        }
    }
    
    return Above * Below * Left * Right;
}

int main() {
    std::ifstream Input{"input.txt"};
    std::string Buffer{};
    std::vector<std::string> Trees{};
    std::vector<int> ScenicScore{};
    int Sum{0};
    while (std::getline(Input,Buffer)) {
        Trees.emplace_back(Buffer);
    }
    
    for (int Row{}; Row < Trees.size(); ++Row) {
        for (int Col{}; Col < Buffer.size(); ++Col) {
            Coordinate Pos{Row, Col};
            // Part 1 Solution
            if (Is_Visible(Pos, Trees)) {
                ++Sum;
            }
            // Part 2 Solution
            ScenicScore.emplace_back(Best_Tree(Pos, Trees));
        }   
    }
    std::cout << Sum << '\n';
    std::sort(ScenicScore.begin(), ScenicScore.end());
    std::cout << ScenicScore.back() << std::endl;
    Input.close();
    return 0;
}