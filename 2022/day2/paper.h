#pragma once
#include "action.h"
#include "rock.h"
#include "scissors.h"

class PaperAction : public Action
{
public:
    PaperAction() { type = ActionType::Paper; };
    Result fight(const Action* action) const override
    {
        if(this->type == action->get_type())
        {
            return Result::Draw;
        }
        if (action->get_type() == ActionType::Rock) 
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
           return ActionType::Rock;
       }

       return ActionType::Scissors;
    };
};  
