#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <utility>
#include <set>

#include "../utils/file.h"
#include "../utils/string.h"

static std::map<char, int> priority;

void populate_priority()
{
    int i = 1;
    while(i <= 52)
    {
        if(i <= 26)
        {
            priority.insert(std::pair<char,int>(char(96 + i), i));
        }
        else
        {
            priority.insert(std::pair<char,int>(char(38 + i), i));
        }

        i++;
    }
}

int process_line(const std::string& line)
{
    std::set<char> compartment1;
    std::set<char> compartment2;

    for (int i = 0; i < line.length(); i++)
    {
        if( i < line.length() / 2 )
        {
            compartment1.insert(line[i]);
        }
        else
        {
            compartment2.insert(line[i]);
        }

    }

    std::string intersection;
    std::set_intersection(compartment1.begin(), compartment1.end(), 
            compartment2.begin(), compartment2.end(), 
            std::back_inserter(intersection));

    if(intersection.length() > 0)
    {
        return priority[intersection[0]];
    }

    return 0;
}
 
int process_line_2(const std::string& elf1, const std::string& elf2, const std::string& elf3)
{
    std::set<char> elf1Items = StringHandler::to_set(elf1);
    std::set<char> elf2Items = StringHandler::to_set(elf2);
    std::set<char> elf3Items = StringHandler::to_set(elf3);

    std::set<char> temp;
    std::set<char> badge;

    std::set_intersection(elf1Items.begin(), elf1Items.end(),
            elf2Items.begin(), elf2Items.end(),
            std::inserter(temp, temp.begin()));

    std::set_intersection(elf3Items.begin(), elf3Items.end(),
            temp.begin(), temp.end(),
            std::inserter(badge, badge.begin()));
    
    return priority[*badge.begin()];
}

int main()
{
    populate_priority();
    auto lines = FileHandler::read_file("../day3/input.txt");
    int points = 0;
    int points2 = 0;
    std::set<char> elf1Items;
    for(auto line : lines)
    {
        points += process_line(line);
    }

    auto iter = lines.begin();
    while(iter != lines.end())
    {
        auto elf1 = *iter++;
        auto elf2 = *iter++;
        auto elf3 = *iter++;

        points2 += process_line_2(elf1, elf2, elf3);
    }

    std::cout << "Points 1: " << points << std::endl;
    std::cout << "Points 2: " << points2 << std::endl;
}
