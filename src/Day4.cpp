#include "Day4.h"

#include <algorithm>
#include <numeric>

namespace AdventOfCode
{
struct ElfAssignment
{
    uint32_t start;
    uint32_t end;

    ElfAssignment(std::string_view parts)
    {
        auto assignmentparts = Utils::Split(parts, '-');
        start = std::stoi(assignmentparts[0].data());
        end = std::stoi(assignmentparts[1].data());
    }

    inline bool Includes(const ElfAssignment &other) const
    {
        if ((this->start <= other.start) && (this->end >= other.end))
        {
            return true;
        }

        return false;
    }

    inline bool Overlaps(const ElfAssignment &other) const
    {
        if (this->Includes(other))
        {
            return true;
        }

        if ((this->start <= other.start) && (this->end >= other.start))
        {
            return true;
        }

        return false;
    }
};

Day4::Day4(const std::string &inputFileName)
    : DailyTask(inputFileName)
{
}

void Day4::Task1()
{
    std::ifstream inputfile{m_inputFileName};

    uint32_t numOfFullyContained{0};

    for (std::string line; std::getline(inputfile, line);)
    {
        auto pairParts = Utils::Split(line, ',');
        auto elf1 = ElfAssignment{pairParts[0]};
        auto elf2 = ElfAssignment{pairParts[1]};

        if (elf1.Includes(elf2) || elf2.Includes(elf1))
        {
            ++numOfFullyContained;
        }
    }

    m_result = std::to_string(numOfFullyContained);
}

void Day4::Task2()
{
    std::ifstream inputfile{m_inputFileName};

    uint32_t numOfFullyContained{0};

    for (std::string line; std::getline(inputfile, line);)
    {
        auto pairParts = Utils::Split(line, ',');
        auto elf1 = ElfAssignment{pairParts[0]};
        auto elf2 = ElfAssignment{pairParts[1]};

        if (elf1.Overlaps(elf2) || elf2.Overlaps(elf1))
        {
            ++numOfFullyContained;
        }
    }

    m_result = std::to_string(numOfFullyContained);
}
}