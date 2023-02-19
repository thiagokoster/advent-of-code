#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/file.h"

int main(){
    std::cout << "Hello World" << std::endl;
    auto lines = FileHandler::read_file("../input.txt");
    
    int currentCalories = 0;
    std::vector<int> elvesCalories;

    for (auto line : lines) 
    {
        if(line == "")
        {
            elvesCalories.push_back(currentCalories);
            currentCalories = 0;
        }
        else
        {
            currentCalories += std::stoi(line);
        }
    }
    std::sort(elvesCalories.begin(), elvesCalories.end(), std::greater<int>());
    std::cout << "Top 1: " << elvesCalories[0] << std::endl;
    std::cout << "Top 3: " << elvesCalories[0] + elvesCalories[1] + elvesCalories[2] << std::endl;
}

