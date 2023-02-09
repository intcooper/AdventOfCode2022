#include "Day2.h"

namespace AdventOfCode
{
Day2::Day2(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day2::Task1()
{
    uint32_t result{0};

    for (std::string line; std::getline(m_inputFile, line);)
    {
        uint8_t opponentPlay(static_cast<uint8_t>(line[0] - 'A') + 1u);
        uint8_t playerPlay(static_cast<uint8_t>(line[2] - 'X') + 1u);
        uint8_t outcome{0};

        if (opponentPlay == playerPlay)
        {
            outcome = 3;
        }
        else
        {
            if (WinCombinations[static_cast<size_t>(opponentPlay) - 1] ==
                playerPlay)
            {
                outcome = 6;
            }
        }

        result += outcome + playerPlay;
    }

    m_result = std::to_string(result);
}

void Day2::Task2()
{
    uint32_t result{0};

    for (std::string line; std::getline(m_inputFile, line);)
    {
        uint8_t opponentPlay(static_cast<uint8_t>(line[0] - 'A') + 1u);
        uint8_t playerPlay{0};
        uint8_t outcome = (static_cast<uint8_t>(line[2] - 'X') * 3u);

        if (outcome == 3)
        {
            playerPlay = opponentPlay;
        }
        else
        {
            if (outcome == 0)
            {
                playerPlay =
                    LossCombinations[static_cast<size_t>(opponentPlay) - 1];
            }
            else
            {
                playerPlay =
                    WinCombinations[static_cast<size_t>(opponentPlay) - 1];
            }
        }

        result += outcome + playerPlay;
    }

    m_result = std::to_string(result);
}
}