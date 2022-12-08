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


int get_visible_trees(std::vector<std::string>& input)
{
    int count = 2*input.size()+2*input[0].length()-4;

    for (size_t i = 1; i < input.size()-1; i++)
    {
        for (size_t j = 1; j < input[i].length()-1; j++)
        {
            bool rl_vis = true;
            bool rr_vis = true;
            bool ll_vis = true;
            bool lr_vis = true;
            size_t r = i;
            size_t c = j;

            while (r-- > 0)
            {
                if (input[i][j] <= input[r][j])
                {
                    rl_vis = false;
                    break;
                }
            }
               
            r = i;
            while (r++ < input.size()-1)
            {
                if (input[i][j] <= input[r][j])
                {
                    rr_vis = false;
                    break;
                }
            }

            while (c-- > 0)
            {
                if (input[i][j] <= input[i][c])
                {
                    ll_vis = false;
                    break;
                }
            }

            c = j;

            while (c++ < input.size()-1)
            {
                if (input[i][j] <= input[i][c])
                {
                    lr_vis = false;
                    break;
                }
            }


            if (rl_vis || rr_vis || ll_vis || lr_vis)
            {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load(argv[1]);
    int result = get_visible_trees(input);
    std::cout << result << std::endl;
}