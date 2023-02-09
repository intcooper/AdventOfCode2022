#include "Day13.h"

#include <algorithm>
#include <optional>
#include <string>


namespace AdventOfCode
{
    Day13::Day13(std::string inputFileName)
    : DailyTask(inputFileName)
	{
	}

    void Day13::Task1()
    {
        int sumOfCorrect = 0;
        int pairNo = 0;
        std::string strLeft;
        std::string strRight;

        for (std::string line; std::getline(m_inputFile, line);)
        {
            if (line.empty())
            {
                ++pairNo;

                auto res = ComparePackets(TextToPacket(strLeft), TextToPacket(strRight));

                if (res == true)
                {
                    sumOfCorrect += pairNo;
                }

                strLeft.clear();
                strRight.clear();
            }

            if (strLeft.empty())
            {
                strLeft = line;
                continue;
            }
            
            if (strRight.empty())
            {
                strRight = line;
                continue;
            }
        }

        m_result = std::to_string(sumOfCorrect);
    }

    void Day13::Task2()
    {
        int sumOfCorrect = 0;
        int pairNo = 0;
        std::string strLeft;
        std::string strRight;
        std::vector<Packet> packets;

        for (std::string line; std::getline(m_inputFile, line);)
        {
            if (line.empty())
            {
                continue;
            }

            packets.emplace_back(TextToPacket(line));
        }

        const auto divider1 = TextToPacket("[[2]]");
        const auto divider2 = TextToPacket("[[6]]");
        packets.emplace_back(divider1);
        packets.emplace_back(divider2);
        
        std::ranges::sort(packets, [this](auto a, auto b){ return ComparePackets(a, b) == true;});
        auto iter1 = std::ranges::find(packets, divider1);
        auto iter2 = std::ranges::find(packets, divider2);

        auto index1 = std::distance(packets.begin(), iter1) + 1;
        auto index2 = std::distance(packets.begin(), iter2) + 1;
        m_result = std::to_string(index1 * index2);
    }

    void Day13::GetPacket(Packet* root, std::string_view text, int& charIndex)
    {
        std::string value;

        while (charIndex < text.size())
        {
            const auto currentChar = text[charIndex];
            if (currentChar == '[')
            {
                Packet newRoot(root);
                GetPacket(&newRoot, text, ++charIndex);
                
                root->AppendList(newRoot);

                if (charIndex >= text.size() - 1)
                {
                    return;
                }

                ++charIndex;
                continue;
            }

            if (currentChar == ',')
            {
                if (!value.empty())
                {
                    root->AppendValue(std::stoi(value));
                    value.clear();
                }
            }

            if (currentChar == ']')
            {
                if (!value.empty())
                {
                    root->AppendValue(std::stoi(value));
                    value.clear();
                }

                return;
            }

            if ((currentChar >= '0') && (currentChar <= '9'))
            {
                value.push_back(currentChar);
            }

            ++charIndex;
        }
    }

    std::optional<bool> Day13::ComparePackets(const Packet& left, const Packet& right)
    {
        const auto maxIndex = std::max(left.GetMaxIndex(), right.GetMaxIndex());

        int index = 0;
        while (index <= maxIndex)
        {
            if (left.IsValue(index))
            {
                if (right.IsValue(index))
                {
                    if (left.GetValue(index) < right.GetValue(index))
                    {
                        return true;
                    }

                    if (right.GetValue(index) < left.GetValue(index))
                    {
                        return false;
                    }
                }
                else 
                {
                    if (!right.IsList(index))
                    {
                        return false; // no more items in the right list
                    }

                    Packet newLeft(left);
                    newLeft.ConvertToList(index);
                    auto res = ComparePackets(newLeft.GetList(index), right.GetList(index));

                    if (res.has_value())
                    {
                        return res.value();
                    }
                }
            }
            else 
            {
                if (!left.IsList(index))
                {
                    if (right.IsList(index) || right.IsValue(index))
                    {
                        return true; // no more items in the left list
                    }

                    return std::nullopt; 
                }

                Packet newRight(right);

                if (right.IsValue(index))
                {
                    newRight.ConvertToList(index);
                }

                if (newRight.IsList(index))
                {
                    auto res = ComparePackets(left.GetList(index), newRight.GetList(index));

                    if (res.has_value())
                    {
                        return res.value();
                    }
                }
                else 
                {
                    return false; // no more items in the right list
                }
            }

            ++index;
        }

        if (left.GetParent() == nullptr)
        {
            return true;
        }

        return std::nullopt;
    }

    Packet Day13::TextToPacket(std::string_view text)
    {
        int charIndex = 0;
        Packet packet;
        GetPacket(&packet, text, charIndex);

        return packet;
    }
}