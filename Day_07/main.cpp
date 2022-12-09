#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <stack>
#include <map>
#include <cctype>

struct File
{
    size_t m_Size{};
    std::string m_Name{};
};

struct Folder
{
    std::string m_Name{};
    Folder* Parent{};
    std::map<std::string, Folder> m_Dirs{};
    std::vector<File> m_Files{};

    void print() {
        std::cout << "    Folder: " << m_Name << '\n' 
                  << "    Size:   " << get_size() << '\n';
        if (!m_Dirs.empty()) {
            std::cout << "    Directories: \n";
            for (auto& [name,folder]:m_Dirs) {
                std::cout << "\t- " << folder.m_Name << " : " << folder.get_size() << '\n'; 
            }
        }
        if (!m_Files.empty()) {
            std::cout << "    Files: \n";
            for (auto& Data:m_Files) {
                std::cout << "\t- " << Data.m_Name << " : " << Data.m_Size << '\n';
            }
        }
        std::cout << '\n';
    }

    void print_all() {
        this->print();
        for (auto& [key,value]:m_Dirs) {
            value.print_all();
        }
    }

    size_t get_size() {
        size_t Size{};
        for (auto& [name,folder]:m_Dirs) {
            Size += folder.get_size();
        }
        for (auto& Data:m_Files) {
            Size += Data.m_Size;
        }
        return Size;
    }

    void get_size_under(size_t& Size) {
        for (auto& [name,folder]:m_Dirs) {
            if (folder.get_size() <= 100000) {
                if (!folder.m_Dirs.empty()) {
                    Size += folder.get_size();
                }
                Size += folder.get_size();
            }
            else {
                folder.get_size_under(Size);
            }
        }
    }

    void make_space(size_t Required, std::vector<size_t>& Container) {
        for (auto& [key,value]:m_Dirs) {
            if (value.get_size() >= Required) {
                Container.emplace_back(value.get_size());
                value.make_space(Required, Container);
            }
        }
    }

    Folder* get_dir(std::string_view Name) {
        return &m_Dirs.at(Name.data());
    }

    void mkdir(std::string_view Name, Folder* Parent) {
        Folder temp{Name.data(), Parent};
        m_Dirs.emplace(Name.data(), (Name.data(), temp));
    }

    void touch(size_t Size, std::string_view Name) {
        m_Files.emplace_back(Size, Name.data());
    }
};

int main() 
{
    std::ifstream Input{"input.txt"};
    std::string Buffer{};
    std::stack<std::string> CWD{};
    Folder Top{"/"};
    Folder* Current{&Top};
    size_t sum{};
    
    while (std::getline(Input,Buffer)) {
        if (Buffer.starts_with("$ ls")) {
            while(std::getline(Input,Buffer)) {
                if (Buffer.starts_with("dir")) {
                    if (CWD.top() == "/") {
                        Top.mkdir(Buffer.substr(4), Current);
                    }
                    else {
                        Current->get_dir(CWD.top())->mkdir(Buffer.substr(4), Current->get_dir(CWD.top()));
                    }
                }
                else if (isdigit(Buffer[0])) {
                    std::string_view Size{Buffer.begin(), Buffer.begin() + Buffer.find_first_of(' ') - 1};
                    if (CWD.top() == "/") {
                        Top.touch(std::atoi(Size.data()), Buffer.substr(Buffer.find_first_of(' ') + 1));
                    }
                    else {
                        Current->get_dir(CWD.top())->touch(std::atoi(Size.data()), Buffer.substr(Buffer.find_first_of(' ') + 1));
                    }
                }
                else if (Buffer.starts_with("$ cd")) {
                    break;
                }
            }
        }
        
        if (Buffer.starts_with("$ cd ..")) {
            CWD.pop();
            if (Current->m_Name != "/") {
                Current = Current->Parent;
            }
        }
        else if (Buffer.starts_with("$ cd")) {
            if (!CWD.empty()) {
                if (CWD.top() != "/") {
                    Current = Current->get_dir(CWD.top());
                }
            }
            CWD.push(Buffer.substr(5));
        }
    }

    // Top.print_all();
    // Part 1 Solution
    Top.get_size_under(sum);
    std::cout << sum << std::endl;

    // Part 2 Solution
    const size_t Required{(Top.get_size() + 30'000'000) - 70'000'000};
    std::vector<size_t> Folders{};
    Top.make_space(Required, Folders);
    std::sort(Folders.begin(), Folders.end());
    std::cout << Folders.at(0) << '\n';
    
    Input.close();
    return 0;
}