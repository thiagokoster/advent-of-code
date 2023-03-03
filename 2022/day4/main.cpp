#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/file.h"
#include "../utils/string_helper.h"

class Assignment
{
public:
    int start;
    int end;
    Assignment(const std::string& assignmentStr)
    {
        auto idStrs = StringHandler::split(assignmentStr,'-');
        start = std::stoi(idStrs[0]);
        end = std::stoi(idStrs[1]);
    };
    bool fully_contains(const Assignment& assignment) const
    {
        return start <= assignment.start && end >= assignment.end;
    }

    bool overlaps(const Assignment& assignment) const 
    {
        return end >= assignment.start && start <= assignment.end;
    }

};

std::vector<Assignment> parse_assignments(const std::string& line)
{
    std::vector<Assignment> assignments;

    auto assignmentsStr = StringHandler::split(line, ',');
    assignments.push_back(Assignment(assignmentsStr[0]));
    assignments.push_back(Assignment(assignmentsStr[1]));

    return assignments;
}

bool process_line(const char* line)
{
    auto assignments = parse_assignments(line);
    return (assignments[0].fully_contains(assignments[1]) || 
            assignments[1].fully_contains(assignments[0]));
}

bool process_line_2(const char* line)
{
    auto assignments = parse_assignments(line);
    return (assignments[0].overlaps(assignments[1]));
}

int main()
{
    auto lines = FileHandler::read_file("../day4/input.txt");
    int answer = 0, answer2 = 0;
    for (auto line : lines) {
        if (process_line(line.c_str()))
        {
            answer += 1;
        }

        if (process_line_2(line.c_str()))
        {
            answer2 += 1;
        }
    }
    std::cout << "Part 1: " << answer << std::endl;
    std::cout << "Part 2: " << answer2 << std::endl; }
