#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

#define PART_ONE

bool IsDifferent(std::string_view Line, int Index, int Span) {
    int Range{Span-1};
    for (int x{}; x <= Range; ++x) {
        if (Index < Line.size() - 1) {
            if (Line.find_first_of(Line.at(Index + x), Index+(x+1)) <= Index + Range) {
                return false;
            }
        }
    }
    return true;
}

int main() 
{
    std::ifstream Input{"input.txt"};
    std::string Line{};
    std::getline(Input, Line);
    int Index{};
    
    #ifdef PART_ONE
    int Span{4};
    #else
    int Span{14};
    #endif

    while (!IsDifferent(Line, Index, Span)) {
        ++Index;
    }

    std::cout << Index + Span << std::endl;
    Input.close();
    return 0;
}