#pragma once

#include "DailyTask.h"
#include "Directory.h"

#include <string>

namespace AdventOfCode
{
class Day7 : public DailyTask
{
  public:
    Day7(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 7 - No Space Left On Device";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    Directory m_fsRoot;

    std::string PrintFs(Directory* root) const;
    void ParseInputFile();
};
}
