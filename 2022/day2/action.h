#pragma once
#include <memory>

enum ActionType
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};

enum Result
{
    Lost = 0,
    Draw = 3,
    Win = 6
};

class Action 
{
public:
    virtual Result fight(const Action* action) const = 0;
    ActionType get_type() const { return type; };
    virtual ActionType based_on_result(Result result) = 0;
    virtual ~Action() = default;
    
protected:
    ActionType type;
};
