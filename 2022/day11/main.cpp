#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../utils/file.h"
#include "../utils/string_helper.h"

class Operation
{
    public:
       Operation(const std::string& oper, const std::string& constant) :
           oper(oper), constant(constant) {};
       int execute(int item)
       {
           int op;
           
           if (constant == "old")
               op = item;
           else
            op = std::stoi(constant);

           if (oper == "*")
               return item * op;
           else if (oper == "+")
               return item + op;
           else if (oper == "-")
               return item - op;
           else if (oper == "/")
               return item/op;

            throw std::invalid_argument("Invalid oper");
       };
       std::string str() const
       {
            std::stringstream s;
            s << "new = old " << oper << " " << constant;
            return s.str();
       };
    private:
       std::string oper;
       const std::string constant;
};

class Monkey
{
    public:
        int id;
        int inspectedItems = 0;
        std::deque<unsigned long long> items;
        Operation* operation;
        int divisibleBy = 1;
        int ifTrue = -1;
        int ifFalse = -1;
        Monkey(int id) : id(id) {};
        ~Monkey()
        {
            if(operation != nullptr)
            {
                delete operation;
            }
        };
        void str() const
        {
            std::cout << "Monkey " << id << std::endl;
            
            std::cout << items_str() << std::endl;
            if(operation != nullptr)
            {
                std::cout << operation->str() << std::endl;
            }
            std::cout << test_str() << std::endl;
            std::cout << std::endl;
        };

        void executeRound(const std::vector<Monkey*>& monkeys)
        {
            while(!items.empty())
            {
                // inspect item
                inspectedItems++;
                unsigned long long item = items.front();

                std::cout << "Inspecting: " << item << std::endl;
                item = operation->execute(item);
                std::cout << "New item value: " << item << std::endl;

                // Monkey gets bored
                item = std::floor((float)item / 3);
                std::cout << "Monkey gets bored: " << item << std::endl;

                if (item % divisibleBy == 0)
                {
                    std::cout << "Divisible by: " << divisibleBy << std::endl;
                    std::cout << "Throwing to monkey " << ifTrue <<std::endl;
                    monkeys[ifTrue]->items.push_back(item);
                }
                else
                {
                    std::cout << "Not divisible by: " << divisibleBy << std::endl;
                    std::cout << "Throwing to monkey " << ifFalse << std::endl;
                    monkeys[ifFalse]->items.push_back(item);
                }
                
                items.pop_front();
            }
        }
    private:
        std::string items_str() const
        {
            std::stringstream s;

            s << "  Starting items: ";
            for(int i = 0; i < items.size(); ++i)
            {
                s << items[i];
                if(i < items.size() -1)
                    s << ", ";
            }

            return s.str();
        };

        std::string test_str() const
        {
            std::stringstream s;
            s << "  Test: divisible by " << divisibleBy << std::endl;
            s << "    If true: trow to monkey " << ifTrue << std::endl;
            s << "    If false: trow to monkey " << ifFalse;
            return s.str();
        }
        
};




std::vector<Monkey*> interpreter()
{
    std::vector<Monkey*> monkeys;
    auto lines = FileHandler::read_file("../day11/debug.txt");
    auto it = lines.begin();
    
    int id = 0;
    while(it != lines.end())
    {
        if(it->starts_with("Monkey "))
        {
            Monkey* m = new Monkey(id);
            ++it;
            // get starting items
            auto items = StringHandler::split(it->substr(18,it->length()), ", ");
            for(auto item : items)
                m->items.push_back(std::stoi(item));
            ++it;
            // get operation
            auto args = StringHandler::split(it->substr(23, it->length()), ' ');
            m->operation = new Operation(args[0], args[1]);
            ++it;
            // get test
            m->divisibleBy = std::stoi(it->substr(21,it->length()));
            ++it;
            // get condition
            m->ifTrue = std::stoi(it->substr(29, it->length()));
            ++it;
            m->ifFalse = std::stoi(it->substr(30, it->length()));
            
            ++id;
            monkeys.push_back(m);
        }
        ++it;
    }

    return monkeys;
}

int main()
{
    std::cout << "Day 11" << std::endl;
    auto monkeys = interpreter(); 

    for(int i = 1; i <= 20; ++i)
    {
        for(auto monkey : monkeys)
            monkey->executeRound(monkeys);
    }
    

    // calculate monkey business
    std::sort(monkeys.begin(), monkeys.end(),
            [](const Monkey* lhs, const Monkey* rhs)
            {
                return lhs->inspectedItems > rhs->inspectedItems;   
            });
    for(auto m : monkeys)
        std::cout << m->inspectedItems << std::endl;
    std::cout << "Part 1: " << monkeys[0]->inspectedItems * monkeys[1]->inspectedItems << std::endl;
    // Deleting
    for (auto p : monkeys)
        delete p;

    monkeys.clear();
}
