#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

void ReadSignal(int& Cycle, int& Register, std::vector<int>& Sig_Strength) {
    if (Cycle == 20 || Cycle == 60 || Cycle == 100 || Cycle == 140 || Cycle == 180 || Cycle == 220) {
        Sig_Strength.emplace_back(Cycle * Register);
    }
}

void MapPixels(int& Cycle, int& Register, int &Pixel, std::vector<char>& CRT) {
    if (Pixel >= 40) {
        Pixel = 0;
    }
    if (Pixel == Register || Pixel == Register-1 || Pixel == Register+1) {
        CRT.emplace_back('#');
    } else {
        CRT.emplace_back('.');
    }
    if (Cycle == 40 || Cycle == 80 || Cycle == 120 || Cycle == 160 || Cycle == 200 || Cycle == 240) {
        CRT.emplace_back('\n');
    }
    Pixel++;
}

int main() {
    std::ifstream Input{"input.txt"};
    std::string Buffer{};
    std::vector<int> Sig_Strength{};
    std::vector<char> CRT{};
    int Sum{};
    int Cycle{1};
    int Register{1};
    int Pixel{};

    while (std::getline(Input,Buffer)) {
        ReadSignal(Cycle, Register, Sig_Strength);
        MapPixels(Cycle, Register, Pixel, CRT);
        std::string_view Cmd{Buffer.data(), 4};
        if (Cmd == "noop") {
            ++Cycle;
            continue;
        } else {
            std::string_view Val{Buffer.begin()+5, Buffer.end()};
            int Value{std::atoi(Val.data())};
            ++Cycle;
            ReadSignal(Cycle, Register, Sig_Strength);
            MapPixels(Cycle, Register, Pixel, CRT);
            ++Cycle;
            Register += Value;
        }
    }
    for (auto& SigStr:Sig_Strength) {
        Sum += SigStr;
    }
    for (auto& Pix:CRT) {
        std::cout << Pix;
    }
    std::cout << Sum << std::endl;
    Input.close();
    return 0;
}