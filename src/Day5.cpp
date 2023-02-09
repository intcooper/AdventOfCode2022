#include "Day5.h"

namespace AdventOfCode
{
Day5::Day5(std::string inputFileName)
    : DailyTask(inputFileName)
    , m_stacks{}
{
}

void Day5::Task1()
{
    LoadHeader();

    for (std::string line; std::getline(m_inputFile, line);)
    {
        static constexpr size_t countPos = 5;
        size_t fromPos = line.find("from");
        size_t toPos = line.find("to");

        uint8_t count = std::stoi(line.substr(countPos, fromPos - countPos));
        uint8_t from = std::stoi(line.substr(fromPos + 5, toPos - fromPos));
        uint8_t to = std::stoi(line.substr(toPos + 3, line.length() - toPos));

        for (size_t i = 0; i < count; i++)
        {
            auto crate = m_stacks[static_cast<size_t>(from) - 1].front();
            m_stacks[static_cast<size_t>(from) - 1].pop_front();
            m_stacks[static_cast<size_t>(to) - 1].push_front(crate);
        }
    }
}

void Day5::Task2()
{
    LoadHeader();

    for (std::string line; std::getline(m_inputFile, line);)
    {
        static constexpr size_t countPos = 5;
        size_t fromPos = line.find("from");
        size_t toPos = line.find("to");

        uint8_t count = std::stoi(line.substr(countPos, fromPos - countPos));
        uint8_t from = std::stoi(line.substr(fromPos + 5, toPos - fromPos));
        uint8_t to = std::stoi(line.substr(toPos + 3, line.length() - toPos));

        auto& stack_to = m_stacks[static_cast<size_t>(to) - 1];
        auto& stack_from = m_stacks[static_cast<size_t>(from) - 1];
        stack_to.insert(stack_to.begin(), stack_from.begin(),
                        std::next(stack_from.begin(), count));

        for (size_t i = 0; i < count; i++)
        {
            stack_from.pop_front();
        }
    }
}

void Day5::LoadHeader()
{
    m_stacks.clear();

    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (m_stacks.empty())
        {
            size_t nofstacks = (line.length() + 1) / 4;
            m_stacks.resize(nofstacks);
        }

        if (line.empty())
        {
            break;
        }

        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == '[')
            {
                m_stacks[i / 4].push_back(line[i + 1]);
            }
        }
    }
}

std::string Day5::GetResult() const
{
    std::string result;

    for (size_t i = 0; i < m_stacks.size(); i++)
    {
        result += m_stacks[i].front();
    }

    return result;
}
}