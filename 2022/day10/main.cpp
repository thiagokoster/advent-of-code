#include <cstddef>
#include <iostream>
#include <ostream>
#include <queue>
#include <algorithm>
#include <vector>
#include "../utils/file.h"
#include "../utils/string_helper.h"


class Register
{
    public:
        int value = 1;
};


class Instruction
{
public:
    const char* name;
    int cyclesToComplete;
    bool ready = false;
    int m_operand;
    Register& reg; 

    Instruction(const char* name, int value, int time, Register& reg) : 
        name(name), m_operand(value), cyclesToComplete(time), reg(reg){};
    void execute()
    {
        if(cyclesToComplete == 1)
        {
            ready = true;
            reg.value += m_operand;
        }

        --cyclesToComplete;
    }

};

class CPU
{
public:
    std::queue<Instruction> instructions;
    void tick()
    {
        instructions.front().execute();
        if(instructions.front().ready)
        {
            instructions.pop();
        }
    };
};


void print_sprite(int position, int pixelColumn)
{
    int spriteLen = 3;
    
    char pixel = '#';
    if (abs(pixelColumn - position - 1) > 1)
    {
       pixel = '.'; 
    }
    std::cout << pixel;
}

int main()
{
    std::cout << "Day 10!" << std::endl;
    auto lines = FileHandler::read_file("../day10/input.txt");
    int cycle = 1; 
    CPU cpu;
    Register reg;
    std::vector<int> keyCycles {40, 80, 120, 160, 200, 240};
    for (auto line : lines)
    {
        auto args = StringHandler::split(line, ' ');
        if(args[0] == "noop")
        {
            cpu.instructions.push(Instruction("noop", 0, 1, reg));
        }
        else if(args[0] == "addx")
        {
            int value = std::stoi(args[1]);
            cpu.instructions.push(Instruction("addx", value, 2, reg));

        }
    }
    int part1 = 0;
    while(!cpu.instructions.empty())
    {
        print_sprite(reg.value, cycle % 40); 
        cpu.tick();

        if (std::find(keyCycles.begin(), keyCycles.end(), cycle) != keyCycles.end())
        {
            std::cout << std::endl;
        }
        ++cycle;
    }
    std::cout << std::endl;
}


