#pragma once

#include "DailyTask.h"
#include "utils/Packet.hpp"

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
    Utils::Packet TextToPacket(std::string_view text);
    void GetPacket(Utils::Packet* root, std::string_view text, int& index);
    std::optional<bool> ComparePackets(const Utils::Packet& left, const Utils::Packet& right);
};
}
