#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cctype>
#include <vector>

#define PART_ONE

#ifdef PART_ONE
int main()
{
    std::ifstream Input{"input.txt"};
    std::string Items{};
    int Sum{};

    while (std::getline(Input, Items)) {
        std::string_view FirstHalf{Items.begin(), Items.begin() + Items.size()/2};
        std::string_view SecondHalf{Items.begin() + Items.size()/2, Items.end()};
        bool Found{};
        char Item{};

        for (int i = 0; i < FirstHalf.size(); ++i) {
            for (int x = 0; x < SecondHalf.size(); ++x) {
                if (FirstHalf[i] == SecondHalf[x]) {
                    Item = FirstHalf[i];
                    Found = true;
                    break;
                }
            }
            if (Found) {break;}
        }
        Sum += islower(Item) ? Item - 96 : Item - 38;
    }
    std::cout << Sum << std::endl;
    return 0;
}
#else
int main()
{
    std::ifstream Input{"input.txt"};
    std::vector<std::string> Groups{};
    std::string Line{};
    int Sum{};
    char Badge{};
    Groups.reserve(300);

    while (Input) {
        std::getline(Input, Line);
        Groups.emplace_back(Line);
    }

    for (int i{0}; i < Groups.size(); i += 3) {
        bool Found{};

        for (int x{0}; x < Groups[i].size(); ++x) {
            for (int y{0}; y < Groups[i+1].size(); ++y) {
                if (Groups[i][x] == Groups[i+1][y]) {
                    for (int z{0}; z < Groups[i+2].size(); ++z) {
                        if (Groups[i+2][z] == Groups[i+1][y]) {
                            Badge = Groups[i+2][z];
                            Found = true;
                            break;
                        }
                    }
                    if (Found) {
                        Sum += islower(Badge) ? Badge - 96 : Badge - 38;
                        break;
                    }
                }
            }
            if (Found) {
                break;
            }
        }
    }
    std::cout << Sum << std::endl;
    return 0;
}
#endif