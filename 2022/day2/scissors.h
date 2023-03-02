#pragma once
#include "action.h"

class ScissorsAction : public Action
{
public:
    ScissorsAction() { type = ActionType::Scissors; };
    Result fight(const Action* action) const override
    {
        if(this->type == action->get_type())
        {
            return Result::Draw;
        }
        if (action->get_type() == ActionType::Paper) 
        {
            return Result::Win;
        }
        return Result::Lost;
    };
    
    ActionType based_on_result(Result result) override
    {
       if(result == Result::Draw)
       {
            return get_type();
       }

       if (result == Result::Lost)
       {
           return ActionType::Paper;
       }

       return ActionType::Rock;
    };
};
