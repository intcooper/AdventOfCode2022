#include "Day9.h"

#include "utils/Helpers.hpp"

namespace AdventOfCode
{
Day9::Day9(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day9::Task1()
{
    Utils::Rope rope{1};

    RunTask(rope);
}

void Day9::Task2()
{
    Utils::Rope rope{9};

    RunTask(rope);
}

void Day9::RunTask(Utils::Rope rope)
{
    const std::map<char, Utils::Point> directions{{'U', Utils::Rope::up},
                                           {'D', Utils::Rope::down},
                                           {'R', Utils::Rope::right},
                                           {'L', Utils::Rope::left}};

    for (std::string line; std::getline(m_inputFile, line);)
    {
        auto parts = Utils::Split(line, ' ');

        rope.MoveHead(directions.at(parts[0][0]), std::stoi(parts[1].data()));
    }

    m_result = std::to_string(rope.GetVisited().size());
}
}