#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream Input{"input.txt"};
    std::string Buffer{};
    std::vector<int> Container{};
    int Calorie{};
    int Sum{};
    while(Input) 
    {
        std::getline(Input, Buffer);
        if (Buffer.empty()) {
            if (Sum > 10000) {
                Container.emplace_back(Sum);
            }
            Sum = 0;
        }
        else {
            Sum += stoi(Buffer);
        }
    }

    int HighestValue{};
    int SecondHighestValue{};
    int ThirdHighestValue{};

    for (auto& Calories:Container) {
        if (Calories > HighestValue) {
            HighestValue = Calories;
        }
    }

    for (auto& Calories:Container) {
        if (Calories > SecondHighestValue) {
            if (Calories != HighestValue) {
                SecondHighestValue = Calories;
            }
        }
    }

    for (auto& Calories:Container) {
        if (Calories > ThirdHighestValue) {
            if (Calories != HighestValue && Calories != SecondHighestValue) {
                ThirdHighestValue = Calories;
            }
        }
    }

    std::cout << '\n' << HighestValue << '\n';
    std::cout << '\n' << HighestValue + SecondHighestValue + ThirdHighestValue;

    Input.close();
    return 0;
}