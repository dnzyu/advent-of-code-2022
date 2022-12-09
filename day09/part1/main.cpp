#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

std::vector<std::pair<char, int>> load(const char* filepath)
{
    std::vector<std::pair<char, int>> input;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        std::pair<char,int> p = {line[0], std::stoi(line.substr(2))};
        input.push_back(p);
    }

    return input;
}


int get_tail_visited(std::vector<std::pair<char, int>>& input)
{
    int n = 700;
    
    std::pair<int,int> head_pos = {n/2,n/2};
    std::pair<int,int> tail_pos = {n/2,n/2};
    
    std::vector<std::vector<int>> visited(n, std::vector<int>(n,0));
    visited[tail_pos.first][tail_pos.second]++;

    for (auto v : input)
    {
        if (v.first == 'R')
        {
            for (int i = 0; i < v.second; i++)
            {
                head_pos.second++;

                if (abs(head_pos.second - tail_pos.second) > 1)
                {
                    if (head_pos.first != tail_pos.first)
                    {
                        tail_pos.first = head_pos.first;
                    }
                    tail_pos.second++;
                    visited[tail_pos.first][tail_pos.second]++;
                }
            }
            
        }
        else if (v.first == 'L')
        {
            for (int i = 0; i < v.second; i++)
            {
                head_pos.second--;

                if (abs(head_pos.second - tail_pos.second) > 1)
                {
                    if (head_pos.first != tail_pos.first)
                    {
                        tail_pos.first = head_pos.first;
                    }
                    tail_pos.second--;
                    visited[tail_pos.first][tail_pos.second]++;
                }
            }
            
        }
        else if (v.first == 'U')
        {
            for (int i = 0; i < v.second; i++)
            {
                head_pos.first--;

                if (abs(head_pos.first - tail_pos.first) > 1)
                {
                    if (head_pos.second != tail_pos.second)
                    {
                        tail_pos.second = head_pos.second;
                    }
                    tail_pos.first--;
                    visited[tail_pos.first][tail_pos.second]++;
                }
            }
        }
        else if (v.first == 'D')
        {
            for (int i = 0; i < v.second; i++)
            {
                head_pos.first++;

                if (abs(head_pos.first - tail_pos.first) > 1)
                {
                    if (head_pos.second != tail_pos.second)
                    {
                        tail_pos.second = head_pos.second;
                    }
                    tail_pos.first++;
                    visited[tail_pos.first][tail_pos.second]++;
                }
            }
        }
    }
    

    int total = 0;

    for (auto row : visited)
    {
        for (auto col: row)
        {
            if (col > 0) 
            {
                total++;
            }
        }
    }

    return total;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load(argv[1]);
    int result = get_tail_visited(input);
    std::cout << result << std::endl;
}