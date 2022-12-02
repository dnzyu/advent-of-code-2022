#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

int load_and_calculate(const char* filepath)
{
    // A : Rock B: Paper C: Scissors
    // X : Lose Y: Draw Z: Win
    int total_score = 0;
    std::vector<std::vector<int>> evaluations = { {3,1,2}, {1,2,3}, {2,3,1} };

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        char p1 = line[0] - 65;
        char p2 = line[2] - 88;

        auto eval = evaluations[p1];
        auto point = eval[p2];

        total_score += p2*3 + point;
    }

    return total_score;
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }

    int total_score = load_and_calculate(argv[1]);
    std::cout << total_score << std::endl;
}