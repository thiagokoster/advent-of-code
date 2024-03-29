#pragma once
#include <iterator>
#include <set>
#include <string>
#include <vector>

class StringHandler
{
public:
    static std::vector<std::string> split(const std::string& str, char delimiter)
    {
        std::vector<std::string> out;

        std::string buffer = "";
        
        auto iter = std::begin(str);
        while(iter != std::end(str))
        {
            if(*iter != delimiter)
            {
                buffer += *iter;
            }
            else 
            {
                out.push_back(buffer);
                buffer = "";
            }
            ++iter;
        }
        out.push_back(buffer);
        return out; 
    };

    static std::vector<std::string> split(const std::string& str, std::string delimiter)
    {
        std::vector<std::string> out;
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;

        while((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
        {
            token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            out.push_back(token);
        }
        out.push_back(str.substr(pos_start));
        return out;
    }

    static std::set<char> to_set(const std::string& str)
    {
        std::set<char> out;

        for(char c : str)
        {
            out.insert(c);
        }

        return out;
    };

    static bool unique(const std::string& str)
    {
        std::set<char> char_set;

        for(char c : str)
        {
            char_set.insert(c);
        }

        return char_set.size() == str.size();
    }
};
