#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string priorty = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int find_badge_item(std::string str1, std::string str2, std::string str3)
{
    std::vector<char> similarity;
    int badge = -1;

    for (int i = 0; i < str2.length(); i++)
    {
        if (str1.find(str2[i]) != std::string::npos)
        {
            similarity.push_back(str2[i]);
        }
    }

    for (auto s : similarity)
    {
        if (str3.find(s) != std::string::npos)
        {
            badge = priorty.find(s) + 1;
            break;
        }
    }

    return badge;
}

int load_and_compare(const char* filepath)
{

    int total_priority = 0;
    int count = 0;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    std::string rucksack1 = "";
    std::string rucksack2 = "";
    std::string rucksack3 = "";
    
    while (getline(file,line))
    {
        if (count++<3)
        {
            if (count == 1)
            {
                rucksack1 = line;
            }
            else if (count == 2)
            {
                rucksack2 = line;
            }
            else
            {
                rucksack3 = line;

                total_priority += find_badge_item(rucksack1, rucksack2, rucksack3);

                count = 0;
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