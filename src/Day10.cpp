#include "Day10.h"

namespace AdventOfCode
{
Day10::Day10(std::string inputFileName)
    : DailyTask(inputFileName)
    , m_screen{}
    , m_cycle{0}
    , m_regX{1}
{
}

void Day10::Task1()
{
    int32_t signalStrenght{0};

    RunTask([this, &signalStrenght]() { signalStrenght += CheckSignal(); });

    m_result = std::to_string(signalStrenght);
}

void Day10::Task2()
{
    RunTask([&]() { SetCurrentPixel(); });

    m_result.clear();
    m_result += '\n';

    for (size_t x = 0; x < ScreenRows; x++)
    {
        for (size_t y = 0; y < ScreenCols; y++)
        {
            m_result += m_screen[x][y];
        }
        m_result += '\n';
    }
}

void Day10::RunTask(std::function<void()> task)
{
    m_cycle = 0;
    m_regX = 1;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        auto parts = Utils::Split(line, ' ');

        const auto &command = parts[0];

        if (command == "addx")
        {
            const auto arg = std::stoi(parts[1].data());

            m_cycle++;
            task();
            m_cycle++;
            task();

            m_regX += arg;
        }

        if (command == "noop")
        {
            m_cycle++;
            task();
        }
    }
}
}