#include <iterator>
#include <ostream>
#include <queue>
#include <iostream>
#include <list>
#include <set>
#include <utility>
#include <vector>
#include <climits>
#include "../utils/file.h"


struct Cell
{
    int id;
    char label;
    int dist;
    int row;
    int col;
    std::list<std::pair<int,int>> neighbours(int gridWidth, int gridHeight) 
    {
        std::list<std::pair<int,int>> n;

        if (row != 0)
        {
            n.push_back(std::pair(row - 1, col));
        }
        if( row < gridHeight - 1)
        {
            n.push_back(std::pair(row + 1,col));
        }

        if (col != 0)
        {
            n.push_back(std::pair(row, col - 1));
        }
        if(col < gridWidth - 1)
        {
            n.push_back(std::pair(row, col + 1));
        }

        return n;
    };

    bool operator< (const Cell& other) const 
    {
       return id < other.id;
    }
};

    void run(std::vector<std::vector<Cell>>& grid, int er, int ec, int sr, int sc)
    {
        std::queue<Cell> q;
        std::set<Cell> visited;
        q.push(grid[sr][sc]);
        visited.insert(grid[sr][sr]);
        while(!q.empty())
        {
            auto current = q.front();
            q.pop();

            for (auto nCord : current.neighbours(grid[0].size(), grid.size()))
            {
                if(visited.contains(grid[nCord.first][nCord.second]))
                {
                    continue;
                }

                if((grid[nCord.first][nCord.second].label - '0') - (grid[current.row][current.col].label - '0') > 1)
                {
                    continue;
                }
                if( nCord.first == er && nCord.second == ec)
                {
                    std::cout << nCord.first << " " << nCord.second << std::endl;
                    std::cout << current.dist + 1 << std::endl;
                    return;
                }

                visited.insert(grid[nCord.first][nCord.second]);
                grid[nCord.first][nCord.second].dist += current.dist + 1;
                q.push(grid[nCord.first][nCord.second]);

            }
        }
        std::cout << "couldn't find" << std::endl;
    }


int main()
{
    std::cout << "Day 12!" << std::endl;
    std::vector<std::vector<Cell>> grid;
    auto lines = FileHandler::read_file("../day12/input.txt");
    int sr, sc, er, ec;
    int id = 0;
    int row = 0;
    for(auto line : lines)
    {
        grid.push_back(std::vector<Cell>());
        for(int column = 0; column < line.length();++column)
        {
            if (line[column] == 'S')
            {
                sr = row;
                sc = column;
                grid[row].push_back(Cell{id, 'a', 0, row, column});
            }
            else if(line[column] == 'E')
            {
                er = row;
                ec = column;
                grid[row].push_back(Cell{id, 'z', 0, row, column});
            }
            else
            {
                grid[row].push_back(Cell{id, line[column], 0, row, column});
            }
            ++id;
        }
        ++row;
    }

    run(grid, er, ec, sr, sc);

    for(int i = 0; i < grid.size(); ++i)
    {
        //for(int j =0; j < grid[0].size(); j++)
        //    std::cout << grid[i][j].dist << '\t';

        //std::cout << std::endl;
    }
    
}
