#include <iostream>
#include <vector>
#include <tuple>

#define Operation   std::get<0>(m_Properties)
#define Op_Value    std::get<1>(m_Properties)
#define Test_Value  std::get<2>(m_Properties)
#define Monkey_One  std::get<3>(m_Properties)
#define Monkey_Two  std::get<4>(m_Properties)

#define PART_ONE

struct Monkey {
    std::vector<size_t> m_Items{};
    std::tuple<char,int,int,int,int> m_Properties{};
    size_t m_Inspections{};

    void PassItems(std::vector<Monkey>& Monkeys) {
        size_t Size{m_Items.size()};
        for (size_t x{}; x < Size; ++x) {
            if (Operation ==  '+') {
                m_Items.at(0) += Op_Value;
            } else if (Operation == '*') {
                if (Op_Value == -1) {
                    m_Items.at(0) *= m_Items.at(0);
                } else {
                    m_Items.at(0) *= Op_Value;
                }
            }
            #ifdef PART_ONE
            m_Items.at(0) /= 3;
            #else
            m_Items.at(0) %= 9'699'690;
            #endif
            if (m_Items.at(0) % Test_Value == 0) {
                Monkeys.at(Monkey_One).ReceiveItem(m_Items.at(0));
            } else {
                Monkeys.at(Monkey_Two).ReceiveItem(m_Items.at(0));  
            }
            m_Items.erase(m_Items.begin());
            ++m_Inspections;
        }
    }
    void ReceiveItem(size_t Item) {
        m_Items.emplace_back(Item);
    }
};

int main() {
    int Rounds{};
    std::vector<size_t> Inspections{};
    std::vector<Monkey> Monkeys{
        {{89,73,66,57,64,80},       {'*',3,13,6,2}},
        {{83,78,81,55,81,59,69},    {'+',1,3,7,4}},
        {{76,91,58,85},             {'*',13,7,1,4}},
        {{71,72,74,76,68},          {'*',-1,2,6,0}}, // Operation: new = old * old
        {{98,85,84},                {'+',7,19,5,7}},
        {{78},                      {'+',8,5,3,0}},
        {{86,70,60,88,88,78,74,83}, {'+',4,11,1,2}},
        {{81,58},                   {'+',5,17,3,5}}
    };
    #ifdef PART_ONE
    while (Rounds < 20) {
    #else
    while (Rounds < 10000) {
    #endif
        for (auto& Monkey:Monkeys) {
            Monkey.PassItems(Monkeys);
        }
        ++Rounds;
    }
    for (auto& Monkey:Monkeys)  {
        Inspections.emplace_back(Monkey.m_Inspections);
    }
    std::sort(Inspections.begin(), Inspections.end());
    std::cout << '\n' << *(Inspections.end()-2) * Inspections.back() << std::endl;
    return 0;
}