#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

struct dir
{
    std::string name;
    int filesize = 0;
    std::vector<std::pair<std::string, int>> files;
    std::vector<dir> directories;
};

int size_of_dir(dir& d)
{
    int size = 0;

    for (auto&  f : d.files)
    {
        std::cout << f.first << ": " << f.second << std::endl;
        size += f.second;
    }

    std::cout << d.name << " Prev Size: " << d.filesize << " | Total Size: " << size << std::endl;
    return size;
}

int sum_size_of_dir(int& sum, dir& d, int lim)
{

    if (!d.directories.empty())
    {
        for (auto& di : d.directories)
        {
            d.filesize += sum_size_of_dir(sum, di, lim);
               
        }
    }
    
    d.filesize = size_of_dir(d);
    std::cout << d.name << " Prev Size: " << d.filesize << std::endl;
    sum += (sum + d.filesize < lim) ? d.filesize : 0;
    return sum;
}

bool load_commands(const char* filepath)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> commands;
    std::pair<std::string, std::vector<std::string>> command;
    std::vector<std::string> output;


    auto file = std::ifstream{filepath};
    auto line = std::string{};

    while (getline(file,line))
    {
        if (line[0] == '$')
        {   
            if (!output.empty() || command.first.substr(0,2) == "cd")
            {
                command.second = output;
                commands.push_back(command);
                output.clear();
            }
            std::string str = line.substr(2);
            command = std::make_pair(str,output);
        }
        else
        {   
            output.push_back(line);
        }
    }

    for (auto command : commands)
    {
        std::cout << "command name: " << command.first << std::endl;

        for (auto output : command.second)
        {
            std::cout << output << std::endl;
        }
    }
    return true;
}

void run_sample_dir()
{
    dir sample_dir;
    dir sample_dir2;
    dir sample_dir3;
    dir sample_dir4;

    sample_dir.name = "d1";
    sample_dir2.name = "d2";
    sample_dir3.name = "d3";
    sample_dir4.name = "d4";

    sample_dir.files.push_back({"test1.txt", 1});
    sample_dir.files.push_back({"test2.txt", 2});
    sample_dir.files.push_back({"test3.txt", 3});

    sample_dir2.files.push_back({"test4.txt", 4});
    sample_dir2.files.push_back({"test5.txt", 5});
    sample_dir2.files.push_back({"test6.txt", 6});

    sample_dir3.files.push_back({"test7.txt", 7});
    sample_dir3.files.push_back({"test8.txt", 8});
    sample_dir3.files.push_back({"test9.txt", 9});



    sample_dir4.files.push_back({"test10.txt", 0});
    sample_dir4.files.push_back({"test11.txt", 11});
    sample_dir4.files.push_back({"test12.txt", 0});

    sample_dir2.directories.push_back(sample_dir4);


    sample_dir.directories.push_back(sample_dir2);
    sample_dir.directories.push_back(sample_dir3);


    int sum = 0;
    sum_size_of_dir(sum, sample_dir, 20);
    std::cout << "Sum of all under lim: " << sum << std::endl;
}

int calculate()
{
    int pos = -1;
    return pos;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "invalid argument count" << std::endl;
        exit(1);
    }
    
    auto input = load_commands(argv[1]);

    run_sample_dir();

    int result = calculate();
    std::cout << result << std::endl;
}