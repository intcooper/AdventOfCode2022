#include "Day3.h"

#include <algorithm>
#include <vector>

namespace AdventOfCode
{
Day3::Day3(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day3::Task1()
{
    std::vector<char> duplicates;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        size_t middle = line.length() / 2;

        for (size_t i = 0; i < middle; i++)
        {
            if (std::find(line.begin() + middle, line.end(), line[i]) !=
                line.end())
            {
                duplicates.push_back(line[i]);
                break;
            }
        }
    }

    m_result = std::to_string(GetPriority(duplicates));
}

void Day3::Task2()
{
    std::vector<char> badges;
    std::vector<std::string> rucksacks;

    int lineIndex = 1;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (lineIndex % 3 == 0)
        {
            rucksacks.push_back(line);

            // find the badge
            for (size_t i = 0; i < rucksacks[0].length(); i++)
            {
                if (std::find(rucksacks[1].begin(), rucksacks[1].end(),
                              rucksacks[0][i]) != rucksacks[1].end())
                {
                    if (std::find(rucksacks[2].begin(), rucksacks[2].end(),
                                  rucksacks[0][i]) != rucksacks[2].end())
                    {
                        badges.push_back(rucksacks[0][i]);
                        break;
                    }
                }
            }

            rucksacks.clear();
        }
        else
        {
            rucksacks.push_back(line);
        }

        ++lineIndex;
    }

    m_result = std::to_string(GetPriority(badges));
}
}