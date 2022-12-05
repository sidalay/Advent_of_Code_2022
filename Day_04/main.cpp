#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

// #define PART_ONE

int main()
{
    std::ifstream Input{"input.txt"};
    std::string Elf_One{};
    std::string Elf_Two{};
    int Total{};

    while (std::getline(Input, Elf_One, ',') && std::getline(Input, Elf_Two)) {
        auto it = std::find(Elf_One.begin(), Elf_One.end(), '-');
        auto itTwo = std::find(Elf_Two.begin(), Elf_Two.end(), '-');
        std::string_view First{Elf_One.begin(), it - 1};
        std::string_view Second{it + 1, Elf_One.end() - 1};
        std::string_view Third{Elf_Two.begin(), itTwo - 1};
        std::string_view Fourth{itTwo + 1, Elf_Two.end() - 1};
        std::array<int, 4> Ranges{
            std::atoi(First.data()), 
            std::atoi(Second.data()), 
            std::atoi(Third.data()), 
            std::atoi(Fourth.data())
        };

        #ifdef PART_ONE
        // First Elf is fully contained
        if ((Ranges[0] >= Ranges[2]) && (Ranges[1] <= Ranges[3])) {
            ++Total;
        }
        // Second Elf is fully contained
        else if ((Ranges[0] <= Ranges[2]) && (Ranges[1] >= Ranges[3])) {
            ++Total;
        }
        #else
        // Elf is partially contained
        if ((Ranges[0] <= Ranges[3]) && (Ranges[1] >= Ranges[2])) {
            ++Total;
        }
        #endif
    }
    
    std::cout << Total << std::endl;

    Input.close();
    return 0;
}