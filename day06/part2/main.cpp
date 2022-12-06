#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

std::string load(const char* filepath)
{
    std::string input;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    if (getline(file,line))
    {
        input = line;
    }

    return input;
}

bool is_all_unique(std::string& str)
{
    bool result = true;
    std::unordered_map<char,int> map;

    for (size_t i = 0; i < str.length(); i++)
    {
        if (map.find(str[i]) == map.end())
        {
            map[str[i]] = 1;
        }
        else
        {
            result = false;
            break;
        }
    }

    return result;
}

int calculate(std::string& input)
{
    int pos = -1;
    std::string marker = input.substr(0,13);

    for (size_t i = 13; i < input.length(); i++)
    {
        marker += input[i];
        if (is_all_unique(marker))
        {
            pos = i+1;
            std::cout << "marker: " << marker << std::endl;
            break;
        }

        marker = marker.substr(1,13);
    }
    return pos;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load(argv[1]);
    int result = calculate(input);
    std::cout << result << std::endl;
}