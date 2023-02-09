#pragma once

#include "DailyTask.h"
#include "Packet.hpp"

#include <optional>
#include <string_view>

namespace AdventOfCode
{
class Day13 : public DailyTask
{
  public:
    Day13(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 13 - Distress Signal";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    Packet TextToPacket(std::string_view text);
    void GetPacket(Packet* root, std::string_view text, int& index);
    std::optional<bool> ComparePackets(const Packet& left, const Packet& right);
};
}
