#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include "../utils/file.h"
#include "../utils/string_helper.h"

#include "action.h"
#include "rock.h"
#include "paper.h"
#include "scissors.h"


std::unique_ptr<Action> translate_action(const char letter)
{
    if (letter == 'A' || letter == 'X')
    {
        return std::unique_ptr<Action> { new RockAction() };
    }

    if (letter == 'B' || letter == 'Y')
    {
        return std::unique_ptr<Action> { new PaperAction() };
    }

    if (letter == 'C' || letter == 'Z')
    {
        return std::unique_ptr<Action> { new ScissorsAction() };
    }

    throw std::invalid_argument("Invalid letter");
}


Result translate_result(const char letter)
{
    if ( letter == 'X')
    {
        return Result::Lost;
    }

    if (letter == 'Y')
    {
        return Result::Draw;
    }

    if (letter == 'Z')
    {
        return Result::Win; 
    }

    throw std::invalid_argument("Invalid letter");
}

int getPoints(ActionType me, Result result)
{
    return (int)result + (int) me;
}

int process_line(const char* line)
{
    std::vector<std::string> actionsStr = StringHandler::split(std::string(line), ' ');
    auto opponent = translate_action(actionsStr[0][0]);
    auto me = translate_action(actionsStr[1][0]);
    
    auto result = me->fight(opponent.get());
    return getPoints(me->get_type(), result);
}

int process_line_2(const char* line)
{
    std::vector<std::string> actionsStr = StringHandler::split(std::string(line), ' ');
    auto opponent = translate_action(actionsStr[0][0]);
    auto result = translate_result(actionsStr[1][0]);
    
    auto me = opponent->based_on_result(result);
    
    return getPoints(me, result);
}

int main() {

    auto lines = FileHandler::read_file("../day2/input.txt");
    int points = 0;
    int points2 = 0;
    for (auto line : lines)
    {
        points += process_line(line.c_str());
        points2 += process_line_2(line.c_str());
    }

    std::cout << "Total: " << points << std::endl;
    std::cout << "Total 2: " << points2 << std::endl;
}

