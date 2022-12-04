#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> load(const char* filepath)
{
    std::vector<std::vector<int>> input;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        std::string part1 = line.substr(0,line.find(','));
        std::string part2 = line.substr(line.find(',')+1);

        int part1_val1 = std::stoi(part1.substr(0,part1.find('-')));
        int part1_val2 = std::stoi(part1.substr(part1.find('-')+1));
        int part2_val1 = std::stoi(part2.substr(0,part2.find('-')));
        int part2_val2 = std::stoi(part2.substr(part2.find('-')+1));

        input.push_back({part1_val1,part1_val2,part2_val1,part2_val2});
    }

    return input;
}

int calculate(std::vector<std::vector<int>>& input)
{
    int overlapping_pairs = 0;

    for (auto& v : input)
    {
        if (v[1] < v[2] || v[0] > v[3]) continue;
        
        overlapping_pairs++;
    }

    return overlapping_pairs;
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