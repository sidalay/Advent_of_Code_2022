#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <tuple>

#define PART_ONE

void Organize(std::tuple<int,int,int> Instruction, std::array<std::stack<char>,9>& Stack) {
    #ifdef PART_ONE
    for (int x{}; x < std::get<0>(Instruction); ++x) {
        Stack.at(std::get<2>(Instruction) - 1).emplace(Stack.at(std::get<1>(Instruction) - 1).top());
        Stack.at(std::get<1>(Instruction) - 1).pop();
    }
    #else
    std::stack<char> Temp{};
    for (int x{}; x < std::get<0>(Instruction); ++x) {
        Temp.emplace(Stack.at(std::get<1>(Instruction) - 1).top());
        Stack.at(std::get<1>(Instruction) - 1).pop();
    }
    for (int x{}; x < std::get<0>(Instruction); ++x) {
        Stack.at(std::get<2>(Instruction) - 1).emplace(Temp.top());
        Temp.pop();
    }
    #endif
}

int main() 
{
    std::ifstream Input{"input.txt"};
    std::array<std::string, 8> Crates{{{},{},{},{},{},{},{},{}}};
    std::array<std::stack<char>, 9> Stack{{{},{},{},{},{},{},{},{},{}}};
    std::vector<std::string> Instructions{};
    std::vector<std::tuple<int,int,int>> Commands{};
    std::string Temp{};

    // Grab the mapping of crates
    for (int x{}; x < 8; ++x) {
        std::getline(Input,Crates[x]);
    }
    // Create crate stacks
    for (auto Line{Crates.rbegin()}; Line != Crates.rend(); ++Line) {
        if ((*Line)[1] != ' ') 
            Stack.at(0).emplace((*Line)[1]);
        if ((*Line)[5] != ' ') 
            Stack.at(1).emplace((*Line)[5]);
        if ((*Line)[9] != ' ') 
            Stack.at(2).emplace((*Line)[9]);
        if ((*Line)[13] != ' ') 
            Stack.at(3).emplace((*Line)[13]);                
        if ((*Line)[17] != ' ') 
            Stack.at(4).emplace((*Line)[17]);
        if ((*Line)[21] != ' ') 
            Stack.at(5).emplace((*Line)[21]);
        if ((*Line)[25] != ' ') 
            Stack.at(6).emplace((*Line)[25]);                
        if ((*Line)[29] != ' ') 
            Stack.at(7).emplace((*Line)[29]);
        if ((*Line)[33] != ' ') 
            Stack.at(8).emplace((*Line)[33]);
    }

    // Ignore the next two lines
    std::getline(Input,Temp);
    std::getline(Input,Temp);
    // Grab the instructions
    while (std::getline(Input, Temp)) {
        Instructions.emplace_back(Temp);
    }

    // Create Instruction Tuples<int,int,int>
    for (auto& i:Instructions) {
        std::string_view First {i.begin() + (i.find('e')+1),         i.begin() + (i.find('f')-1)};
        std::string_view Second{i.begin() + (i.find_last_of('m')+1), i.begin() + (i.find('t')-1)};
        std::string_view Third {i.begin() + (i.find_last_of('o')+1), i.end()};
        Commands.emplace_back(std::make_tuple(std::atoi(First.data()), std::atoi(Second.data()), std::atoi(Third.data())));
    }

    for (const auto& Command:Commands) {
        Organize(Command, Stack);
    }

    for (auto Line:Stack) {
        std::cout << Line.top();
        Line.pop();
    }
}