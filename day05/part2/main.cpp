#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

bool load(const char* filepath, std::vector<std::stack<char>>& crates_, std::vector<std::vector<int>>& operations_)
{
    std::vector<std::vector<char>> crates_temp;
    std::vector<std::vector<int>> operations;

    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        if (line.find("move") != std::string::npos)
        {
            int op1 = std::stoi(line.substr(line.find("e")+2, line.find("f")));
            int op2 = std::stoi(line.substr(line.find("om")+3, line.find("t")));
            int op3 = std::stoi(line.substr(line.find("t")+3));
            
            operations.push_back({op1, op2-1, op3-1});
        }
        else if (line.find("[") != std::string::npos)
        {
            std::vector<char> crate;
            for (std::size_t i = 0; i <= line.length()/4; i++)
            {
                if (line[4*i] == '[')
                {
                    crate.push_back(line[4*i+1]);
                }
                else
                {
                    crate.push_back('-');
                }
            }

            crates_temp.push_back(crate);           
        }
    }

    std::vector<std::stack<char>> crates(crates_temp[0].size());
    
    for (int i = crates_temp.size()-1; i >= 0; i--)
    {
        for (std::size_t j = 0; j < crates_temp[i].size(); j++)
        {
            if (crates_temp[i][j] != '-')
            {
                crates[j].push(crates_temp[i][j]);
            }
        }
    }
 
    crates_ = crates;
    operations_ = operations;

    return true;
}


std::string compute(std::vector<std::stack<char>>& crates, std::vector<std::vector<int>>& operations)
{
    std::string result = "";
    
    for (auto op : operations)
    {   
        std::vector<char> vals;
        for (int i = 0; i < op[0]; i++)
        {
            int val = crates[op[1]].top();
            crates[op[1]].pop();
            vals.push_back(val);
        }

        for (int i = op[0]-1; i > -1; i--)
        {
            crates[op[2]].push(vals[i]);
        }
    }

    for (auto c : crates)
    {
        if (!c.empty())
        {
            result += c.top();
        }
        
    }  

    return result;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    std::vector<std::vector<int>> operations;
    std::vector<std::stack<char>> crates;

    
    load(argv[1], crates, operations);

    auto result = compute(crates, operations);
    std::cout << result << std::endl;
}