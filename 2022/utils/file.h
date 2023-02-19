#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>


class FileHandler {
public:
    static std::list<std::string> read_file(const char* file_path)
    {
        std::list<std::string> lines;
        
        std::string line; 
        std::ifstream file (file_path);
        if(!file.is_open())
        {
            std::cout << "Unable to open file:" << file_path << std::endl;
            return lines;
        }
        

        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();
        return lines;

    };
};

