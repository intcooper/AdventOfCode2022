#pragma once

#include "DailyTask.h"
#include "utils/Grid.hpp"

namespace AdventOfCode
{
using TreeHeight = uint8_t;

class Day8 : public DailyTask
{
  public:
    Day8(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 8 - Treetop Tree House";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    Utils::Grid<TreeHeight> m_map;

    void ParseInputFile();
    bool IsTreeVisible(size_t treeRow, size_t treeCol);
    uint32_t GetTreeScenicScore(size_t treeRow, size_t treeCol);
};
}
