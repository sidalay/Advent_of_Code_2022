#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

// #define PART_ONE

enum HAND {
    A = 1, B = 2, C = 3,
    X = 1, Y = 2, Z = 3
};

#ifdef PART_ONE
    int RoundResults(std::pair<HAND,HAND>& Round) {
        if ((Round.first == HAND::A) && (Round.second == HAND::X)) {
            return Round.second + 3;
        }
        else if ((Round.first == HAND::A) && (Round.second == HAND::Y)) {
            return Round.second + 6;
        }
        else if ((Round.first == HAND::A) && (Round.second == HAND::Z)) {
            return Round.second + 0;    
        }
        else if ((Round.first == HAND::B) && (Round.second == HAND::X)) {
            return Round.second + 0;
        }
        else if ((Round.first == HAND::B) && (Round.second == HAND::Y)) {
            return Round.second + 3;
        }
        else if ((Round.first == HAND::B) && (Round.second == HAND::Z)) {
            return Round.second + 6;
        }
        else if ((Round.first == HAND::C) && (Round.second == HAND::X)) {
            return Round.second + 6;
        }
        else if ((Round.first == HAND::C) && (Round.second == HAND::Y)) {
            return Round.second + 0;
        }
        else if ((Round.first == HAND::C) && (Round.second == HAND::Z)) {
            return Round.second + 3;
        }
        return 0;
    }
#else
    int RoundResults(std::pair<HAND,HAND>& Round) {
        switch(Round.second) {
            case HAND::X:
                if (Round.first == HAND::A) {
                    return 3 + 0;
                }
                else if (Round.first == HAND::B) {
                    return 1 + 0;
                }
                else if (Round.first == HAND::C) {
                    return 2 + 0;
                }
            case HAND::Y:
                if (Round.first == HAND::A) {
                    return 1 + 3;
                }
                else if (Round.first == HAND::B) {
                    return 2 + 3;
                }
                else if (Round.first == HAND::C) {
                    return 3 + 3;
                }
            case HAND::Z:
                if (Round.first == HAND::A) {
                    return 2 + 6;
                }
                else if (Round.first == HAND::B) {
                    return 3 + 6;
                }
                else if (Round.first == HAND::C) {
                    return 1 + 6;
                }
            default:
                return 0;
        }
        return 0;
    }
#endif

int main()
{
    std::ifstream Input {"input.txt"};
    std::vector<int> Results{};
    std::pair<HAND,HAND> Round{};
    char Buffer{};
    int Sum{};
    HAND Hand{};
    uint16_t Counter{};

    while(Input >> Buffer) {

        switch(Buffer) {
            case 'A':
                Hand = HAND::A;
                break;
            case 'B':
                Hand = HAND::B;
                break;
            case 'C':
                Hand = HAND::C;
                break;
            case 'X':
                Hand = HAND::X;
                break;
            case 'Y':
                Hand = HAND::Y;
                break;
            case 'Z':
                Hand = HAND::Z;
                break;
            default:
                break;
        }

        if (Counter == 0) {
            ++Counter;
            Round.first = Hand;
            continue;
        }

        Round.second = Hand;
        --Counter;

        Results.emplace_back(RoundResults(Round));
    }

    for (auto& Result:Results) {
        Sum += Result;
    }

    std::cout << Sum;

    Input.close();
    return 0;
}