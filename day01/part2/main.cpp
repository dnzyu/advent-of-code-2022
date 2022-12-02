#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <limits.h> 

int load_and_sort(const char* filepath)
{
    std::vector<int> max_calories = {INT_MIN, INT_MIN, INT_MIN};
    int calories = 0;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        if (line.empty())
        {
            if (calories > max_calories[2])
            {
                max_calories[2] = calories;
            }
            else if (calories > max_calories[1])
            {
                max_calories[1] = calories;
            }
            else if (calories > max_calories[0])
            {
                max_calories[0] = calories;
            }

            calories = 0;    
        }
        else
        {
            calories += std::stoi(line);
        }
        
    }

    int max_three_calories = std::accumulate(max_calories.begin(), max_calories.end(),0);
    return max_three_calories;
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }

    int max_three_calories = load_and_sort(argv[1]);
    std::cout << max_three_calories << std::endl;
}