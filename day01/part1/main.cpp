#include <iostream>
#include <fstream>
#include <string>
#include <limits.h> 

int load_and_sort(const char* filepath)
{
    int max_calories = INT_MIN;
    int calories = 0;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        if (line.empty())
        {
            if (calories > max_calories)
            {
                max_calories = calories;
            }

            calories = 0;    
        }
        else
        {
            calories += std::stoi(line);
        }
        
    }

    return max_calories;
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }

    int max_calories = load_and_sort(argv[1]);
    std::cout << max_calories << std::endl;
}