#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <regex>
#include "../utils/file.h"
#include "../utils/string_helper.h"


typedef std::list<std::string>::iterator list_it;
typedef std::stack<std::string> stack_type;

struct Command
{
    int amount;
    int from;
    int to;
};

std::vector<stack_type> get_stacks(list_it& it, const list_it& end)
{
    std::vector<std::string> lines;

    while(*it != "" && it != end)
    {
        lines.push_back(*it);
        std::cout << *it << std::endl;
        ++it;
    }
    
    // find number of stacks (9 for my input)
    auto sizes = StringHandler::split(lines[lines.size() -1] ,' ');
    int maxSize = std::stoi(sizes[sizes.size() -2]);
    std::vector<stack_type> stacks(maxSize);
    
    // fill each stack
    std::regex e ("\\[(\\w)\\]");
    for(int i = lines.size() - 2; i >= 0; i--)
    {
        std::smatch m; 
      
        for(auto it = std::sregex_iterator(lines[i].begin(), lines[i].end(), e); it != std::sregex_iterator();++it)
        {
            stacks[it->position()/4].push(it->str(1));
        }
    }
    return stacks;
}

void execute(std::vector<stack_type>& stacks, const Command* command)
{
    if (command == nullptr)
    {
        return;
    }

    for(int i = 0; i < command->amount ; i++)
    {
        std::string s = stacks[command->from - 1].top();
        stacks[command->from -1].pop();
        stacks[command->to - 1].push(s);
    }
}


void execute_2(std::vector<stack_type>& stacks, const Command* command)
{
    if (command == nullptr)
    {
        return;
    }
    stack_type buffer;

    for(int i = 0; i < command->amount ; i++)
    {
        buffer.push(stacks[command->from - 1].top());
        stacks[command->from -1].pop();
    }
    
    while(buffer.size() > 0)
    {
        stacks[command->to - 1].push(buffer.top());
        buffer.pop();
    }
}

std::unique_ptr<Command> parse_command(list_it& it, const list_it& end)
{
    std::regex rgx ("move\\W(\\d+)\\Wfrom\\W(\\d+)\\Wto\\W(\\d+)");
    std::smatch matches;
    if(std::regex_search(*it, matches, rgx))
    {
        int amount = std::stoi(matches[1]);
        int from = std::stoi(matches[2]);
        int to = std::stoi(matches[3]);

        return std::unique_ptr<Command> (new Command { amount, from, to });
    }

    return std::unique_ptr<Command>(nullptr);
 
}

int main()
{
    std::list<std::string>lines = FileHandler::read_file("../day5/input.txt");
    list_it it = lines.begin();

    auto stacks = get_stacks(it, lines.end());
    
    while (it != lines.end()) 
    {
        auto command = parse_command(it, lines.end());
        execute_2(stacks, command.get());
        ++it;
    }

    std::cout << "Part 2: "; 
    for(auto stack : stacks)
    {
        std::cout << stack.top();
    }
    std::cout << std::endl;


}
