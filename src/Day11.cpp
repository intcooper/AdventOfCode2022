#include "Day11.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <stdint.h>

namespace AdventOfCode
{
Day11::Day11(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day11::Task1()
{
    m_monkeys.clear();
    ParseInputFile();

    RunTask(20, [](auto i) { return i / 3; });
}

void Day11::Task2()
{
    m_monkeys.clear();
    ParseInputFile();

    uint64_t common_multiple{1};
    for (auto& m : m_monkeys)
    {
        common_multiple *= m.GetTestDivisor();
    }

    RunTask(10'000, [common_multiple](auto i) { return i % common_multiple; });
}

void Day11::RunTask(int numOfRounds,
                    std::function<uint64_t(uint64_t)> reduceWorry)
{
    for (int i = 0; i < numOfRounds; ++i)
    {
        for (auto& m : m_monkeys)
        {
            m.InspectItems(reduceWorry);
        }
    }

    std::vector<uint64_t> inspections;

    for (auto& m : m_monkeys)
    {
        inspections.emplace_back(m.GetTotalInspections());
    }

    std::sort(inspections.begin(), inspections.end(), std::greater<int>());
    m_result = std::to_string(inspections[0] * inspections[1]);
}

void Day11::ParseInputFile()
{
    std::vector<uint64_t> items;
    std::function<uint64_t(uint64_t, uint64_t)> operation;
    uint64_t testDivisor;
    std::function<void(uint64_t)> onTestPositive;
    std::function<void(uint64_t)> onTestNegative;

    std::map<char, std::function<uint64_t(uint64_t, uint64_t)>> operators = {
        {'+', [](auto a, auto b) { return a + b; }},
        {'-', [](auto a, auto b) { return a - b; }},
        {'*', [](auto a, auto b) { return a * b; }},
        {'/', [](auto a, auto b) { return a / b; }}};

    for (std::string line; std::getline(m_inputFile, line);)
    {
        auto parts = Utils::Split(line, ':');

        if (parts[0].starts_with("Monkey"))
        {
            continue;
        }

        if (parts[0] == "  Starting items")
        {
            auto subparts = Utils::Split(parts[1], ',');

            std::transform(subparts.begin(), subparts.end(),
                           std::back_inserter(items),
                           [](auto i) { return std::stoi(i.data()); });

            continue;
        }

        if (parts[0] == "  Operation")
        {
            auto subparts = Utils::Split(parts[1], ' ');
            auto oper = operators.at(subparts[4].data()[0]);

            if (subparts[5].find_first_not_of("0123456789") ==
                std::string::npos)
            {
                // is a number
                auto op = std::stoi(subparts[5].data());
                operation = std::bind(oper, std::placeholders::_1, op);
            }
            else
            {
                // assume that the operator is "old" as in "old * old"
                operation = std::bind(oper, std::placeholders::_1,
                                      std::placeholders::_1);
            }

            continue;
        }

        if (parts[0] == "  Test")
        {
            auto subparts = Utils::Split(parts[1], ' ');
            testDivisor = std::stoi(subparts[3].data());

            continue;
        }

        if (parts[0] == "    If true")
        {
            auto subparts = Utils::Split(parts[1], ' ');
            onTestPositive = std::bind(
                [& m_monkeys = m_monkeys](auto worry, auto monkeyId) {
                    m_monkeys[monkeyId].AddItem(worry);
                },
                std::placeholders::_1, std::stoi(subparts[4].data()));

            continue;
        }

        if (parts[0] == "    If false")
        {
            auto subparts = Utils::Split(parts[1], ' ');
            onTestNegative = std::bind(
                [& m_monkeys = m_monkeys](auto worry, auto monkeyId) {
                    m_monkeys[monkeyId].AddItem(worry);
                },
                std::placeholders::_1, std::stoi(subparts[4].data()));

            continue;
        }

        if (parts[0].empty())
        {
            m_monkeys.emplace_back(items, operation, testDivisor,
                                   onTestPositive, onTestNegative);
            items.clear();
            operation = nullptr;
            onTestPositive = nullptr;
            onTestNegative = nullptr;
        }
    }

    m_monkeys.emplace_back(items, operation, testDivisor, onTestPositive,
                           onTestNegative);
}
}
