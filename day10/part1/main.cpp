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


int calculate(std::vector<std::pair<int, int>>& input)
{
    int sum = 0;
    int x = 1;
    int index = 0;
    int cycle_count = 0;

    while (++cycle_count)
    {
        if (index >= input.size())
        {
            break;
        }

        if (cycle_count < 260 && (cycle_count == 20 || (cycle_count-20)%40 == 0))
        {
            sum += cycle_count*x;
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

    return sum;
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