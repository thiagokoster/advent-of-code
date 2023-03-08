#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include "../utils/file.h"


struct Position
{
public:
    int x = 0;
    int y = 0;
    std::string str() const
    {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    };
};

class Node
{
public:
    Node* tail = nullptr;
    std::set<std::string> visited;
    std::string str()
    {
        return position.str();
    };
protected:
    Position position;
    void pullTail()
    {
        if (tail == nullptr)
        {
            return;
        }
        
        auto difX = position.x - tail ->position.x;
        auto aDifX = abs(difX);

        auto difY = position.y - tail->position.y;
        auto aDifY = abs(difY);

        if (aDifX > 1 && aDifY == 0)
            tail->position.x += difX/abs(difX);
        if (aDifY > 1 && aDifX == 0)
            tail->position.y += difY/abs(difY);

        if(aDifX >= 2 && aDifY >=1 || aDifY >= 2 && aDifX >=1)
        {
            tail->position.x += difX/abs(difX);
            tail->position.y += difY/abs(difY);
        }
       
        tail->visited.insert(tail->position.str());
        tail->pullTail();
    };

};

class Head : public Node
{
public:
    void move(std::string command)
    {
        char direction = command[0]; 
        unsigned int times = std::stoi(command.substr(2, command.length()));
        
        for(int i = 0; i < times; ++i)
        {
            if(direction == 'U')
            {
                // Move up
                position.y += 1;
            }
            else if(direction == 'D')
            {
                // Move down
                position.y -= 1;
            }
            else if(direction == 'L')
            {
                // Move left
                position.x -=1;
            }
            else if(direction == 'R')
            {
                // Move right
                position.x += 1;
            }
            pullTail();
        }

    }
};


int main() 
{
    auto lines = FileHandler::read_file("../day9/input.txt");
    Head head;
    Node* tail1 = new Node;
    Node* tail2 = new Node;
    Node* tail3 = new Node;
    Node* tail4 = new Node;
    Node* tail5 = new Node;
    Node* tail6 = new Node;
    Node* tail7 = new Node;
    Node* tail8 = new Node;
    Node* tail9 = new Node;

    head.tail = tail1;
    tail1->tail = tail2;
    tail2->tail = tail3;
    tail3->tail = tail4;
    tail4->tail = tail5;
    tail5->tail = tail6;
    tail6->tail = tail7;
    tail7->tail = tail8;
    tail8->tail = tail9;

    for (auto line : lines)
    {
        head.move(line);   
    }

    std::cout << "Part 1: " << tail1->visited.size() << std::endl;
    std::cout << "Part 2: " << tail9->visited.size() << std::endl;
}
