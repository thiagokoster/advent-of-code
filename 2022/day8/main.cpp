#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include "../utils/file.h"
#include "../utils/string_helper.h"

bool look_west(int row, int column, std::vector<std::vector<int>>& grid, int& score)
{
    for (int j = column - 1; j >= 0; --j)
    {
        score += 1;
        if (grid[row][j] >= grid[row][column])
        {
            return false;
        }
    }

    return true;
}

bool look_east(int row, int column, std::vector<std::vector<int>>& grid, int& score)
{
    for (int j = column + 1; j < grid.size(); ++j)
    {
        score += 1;
        if (grid[row][j] >= grid[row][column])
        {
            return false;
        }
    }
    return true;
}

bool look_north(int row, int column, std::vector<std::vector<int>>& grid, int& score)
{
    for (int i = row - 1; i >= 0 ; --i)
    {
        score += 1;
        if (grid[i][column] >= grid[row][column])
        {
            return false;
        }
    }
    return true;
}

bool look_south(int row, int column, std::vector<std::vector<int>>& grid, int& score)
{
    for (int i = row + 1; i < grid.size() ; ++i)
    {
        score += 1;
        if (grid[i][column] >= grid[row][column])
        {
            return false;
        }
    }
    return true;
}
bool is_visible(int row, int column, std::vector<std::vector<int>>& grid, int& score)
{
    if ( row == 0 || row == grid.size() - 1)
        return true;

    if (column == 0 || column == grid.size() - 1)
        return true;

    int westScore = 0;
    bool west = look_west(row, column, grid, westScore);

    int eastScore = 0;
    bool east = look_east(row, column, grid, eastScore);

    int northScore = 0;
    bool north = look_north(row, column, grid, northScore);

    int southScore = 0;
    bool south = look_south(row, column, grid, southScore);

    score = westScore * eastScore * northScore * southScore;
    return west || east || north || south;
}

int main()
{
    std::cout << "Day 8!" << std::endl;
    auto lines = FileHandler::read_file("../day8/input.txt");
    int gridSize = lines.size();
    std::vector<std::vector<int>> grid;
    
    int i = 0;
    auto iterator = lines.begin();
    while(iterator != lines.end())
    {
        grid.push_back(std::vector<int>());
        for(int j = 0; j < iterator->size(); ++j)
        {
            int tree = (*iterator)[j] - '0';
            grid[i].push_back(tree);
        }

        ++i;
        ++iterator;
    }

    //Part 1
    int maxScore = 0;
    int visibleTrees = 0;
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid.size(); j++)
        {
            int score = 0;
            bool isVisible = is_visible(i, j, grid, score);
            if (isVisible)
                visibleTrees += 1;
            maxScore = std::max(score, maxScore);
        }
    }

    std::cout << "Part 1: " << visibleTrees << std::endl;
    std::cout << "Part 2: " << maxScore << std::endl;
}



