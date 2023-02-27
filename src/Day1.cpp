#include "Day1.h"

#include <algorithm>
#include <numeric>
#include <ranges>

namespace AdventOfCode
{
Day1::Day1(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day1::Task1()
{
    uint32_t elfcalories{0};
    uint32_t maxCalories{0};

    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (!line.empty())
        {
            elfcalories += std::stoi(line);
        }
        else
        {
            if (elfcalories > maxCalories)
            {
                maxCalories = elfcalories;
            }

            elfcalories = 0;
        }
    }

    m_result = std::to_string(maxCalories);
}

void Day1::Task2()
{
    uint32_t elfcalories{0};
    std::vector<uint32_t> elvesCalories;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (!line.empty())
        {
            elfcalories += std::stoi(line);
        }
        else
        {
            elvesCalories.push_back(elfcalories);

            elfcalories = 0;
        }
    }

    elvesCalories.push_back(elfcalories);

    std::ranges::partial_sort(elvesCalories, elvesCalories.begin() + 3,
                              std::greater<uint32_t>());
    m_result = std::to_string(
        std::accumulate(elvesCalories.begin(), elvesCalories.begin() + 3, 0));
}
}