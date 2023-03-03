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

    static std::set<char> to_set(const std::string& str)
    {
        std::set<char> out;

        for(char c : str)
        {
            out.insert(c);
        }

        return out;
    };
};
