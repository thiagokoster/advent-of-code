#include <iostream>
#include <queue>
#include <vector>
#include "../utils/file.h"
#include "../utils/string_helper.h"


class Monkey
{
    public:
        std::queue<int> items;
        
};




std::vector<Monkey> interpreter()
{
    std::vector<Monkey> monkeys;
    auto lines = FileHandler::read_file("../day11/debug.txt");
    auto it = lines.begin();

    while(it != lines.end())
    {
        if(it->starts_with("Monkey "))
        {
            Monkey m;
            ++it;
            // get starting items
            auto items = StringHandler::split(it->substr(18,it->length()), ", ");
            for(auto item : items)
                m.items.push(std::stoi(item));

            // get operation
            //
            // get test
            //
            // get condition
        }
        ++it;
    }

    return monkeys;
}

int main()
{
    std::cout << "Day 11" << std::endl;
    interpreter(); 
}
