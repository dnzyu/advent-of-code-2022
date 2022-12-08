#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> load(const char* filepath)
{
    std::vector<std::string> input;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        input.push_back(line);
    }

    return input;
}


int get_highest_score(std::vector<std::string>& input)
{
    int max_score = 0;

    for (size_t i = 1; i < input.size()-1; i++)
    {
        for (size_t j = 1; j < input[i].length()-1; j++)
        {
            int score = 0;

            int rl_score = 0;
            int rr_score = 0;
            int ll_score = 0;
            int lr_score = 0;

            size_t r = i;
            size_t c = j;

            while (r-- > 0)
            {
                rl_score++;

                if (input[i][j] <= input[r][j])
                {                    
                    break;
                }
            }
               
            r = i;
            while (r++ < input.size()-1)
            {
                rr_score++;

                if (input[i][j] <= input[r][j])
                {
                    break;
                }
            }

            while (c-- > 0)
            {
                ll_score++;

                if (input[i][j] <= input[i][c])
                {
                    break;
                }
            }

            c = j;

            while (c++ < input.size()-1)
            {
                lr_score++;

                if (input[i][j] <= input[i][c])
                {
                    break;
                }
            }
            
            score = rl_score*rr_score*ll_score*lr_score;

            max_score = (score > max_score) ? score : max_score;
        }
    }
    return max_score;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load(argv[1]);
    int result = get_highest_score(input);
    std::cout << result << std::endl;
}