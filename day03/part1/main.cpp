#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

const std::string priorty = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int load_and_compare(const char* filepath)
{

    int total_priority = 0;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        std::string part1 = line.substr(0, line.length()/2);
        std::string part2 = line.substr(line.length()/2, line.length()/2);
        
        std::unordered_map<char, int> items_at_part1;

        for (int i = 0 ; i < part1.length(); i++)
        {
            items_at_part1[part1[i]]++;
        } 

        for (int i = 0 ; i < part2.length(); i++)
        {
            if (items_at_part1.find(part2[i]) != items_at_part1.end())
            {
                int p = priorty.find(part2[i]);
                total_priority += p+1; 
                break;
            }   
        }
    }

    return total_priority;
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }

    int total_priority = load_and_compare(argv[1]);
    std::cout << total_priority << std::endl;
}