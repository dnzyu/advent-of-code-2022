#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<int, int>> load(const char* filepath)
{
    std::vector<std::pair<int, int>> input;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        std::pair<int,int> p;
        if (line.substr(0, line.find(" ")) == "noop")
        {
            p = std::make_pair(1,0);
        }
        else
        {
            int val = std::stoi(line.substr(line.find(" ")+1));
            p = std::make_pair(2, val);
        }

        input.push_back(p);
    }

    return input;
}


void calculate(std::vector<std::pair<int, int>>& input)
{
    int x = 1;
    int index = 0;
    int cycle_count = 0;
    int row = 0;

    while (++cycle_count)
    {
        if (index >= input.size())
        {
            break;
        }

        if (cycle_count%40 == 0)
        {
            row++;
        }

        if (x >= cycle_count-2-(40*row) && x <= cycle_count-(40*row))
        {
            std::cout << "#";
        }
        else
        {
            std::cout << ".";
        }

        if (cycle_count%40 == 0)
        {
            std::cout << std::endl;
        }

        if (input[index].first == 1)
        {
            x += input[index].second;
            index++;
        }
        else
        {
            input[index].first--;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load(argv[1]);
    calculate(input);
}