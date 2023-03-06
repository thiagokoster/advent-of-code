#include <iostream>

#include "../utils/file.h"
#include "../utils/string_helper.h"


int process(const std::string& line, unsigned marker_size)
{
    for(int i = 0; i < line.length() - marker_size - 1; ++i)
    {
        std::string buffer = line.substr(i, marker_size);
        if (StringHandler::unique(buffer))
        {
            return i + marker_size;
        }
    }
    return 0;
}

int main()
{
    std::cout << "Day 6!" << std::endl;
    std::string line = FileHandler::read_file("../day6/input.txt").front();

    std::cout << process(line, 4) << std::endl;
    std::cout << process(line, 14) << std::endl;
}
