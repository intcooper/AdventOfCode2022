#pragma once

#include <deque>
#include <functional>
#include <string>
#include <vector>

namespace AdventOfCode
{
class Monkey
{
  public:
    Monkey() = default;

    Monkey(std::vector<uint64_t> items,
           std::function<uint64_t(uint64_t, uint64_t)> operation,
           uint64_t testDivisor, std::function<void(uint64_t)> onTestPositive,
           std::function<void(uint64_t)> onTestNegative)
        : m_items(items.begin(), items.end())
        , m_operation{operation}
        , m_testDivisor{testDivisor}
        , m_onTestPositive{onTestPositive}
        , m_onTestNegative{onTestNegative}
        , m_numOfInspections{0}
    {
    }

    void InspectItems(std::function<uint64_t(uint64_t)> reduceWorry)
    {
        while (!m_items.empty())
        {
            ++m_numOfInspections;

            auto worry = m_items.front();
            worry = m_operation(worry, worry);
            worry = reduceWorry(worry);

            if (worry % m_testDivisor == 0)
            {
                m_onTestPositive(worry);
            }
            else
            {
                m_onTestNegative(worry);
            }

            m_items.pop_front();
        }
    }

    void AddItem(int worry)
    {
        m_items.push_back(worry);
    }

    inline int GetTotalInspections() const
    {
        return m_numOfInspections;
    }

    inline uint64_t GetTestDivisor() const
    {
        return m_testDivisor;
    }

  private:
    std::deque<uint64_t> m_items;
    std::function<uint64_t(uint64_t, uint64_t)> m_operation;
    uint64_t m_testDivisor;
    std::function<void(uint64_t)> m_onTestPositive;
    std::function<void(uint64_t)> m_onTestNegative;
    uint32_t m_numOfInspections;
};
}