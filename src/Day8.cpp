#include "Day8.h"

#include <map>

namespace AdventOfCode
{

Day8::Day8(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day8::Task1()
{
    if (m_map.Rows() == 0)
    {
        ParseInputFile();
    }

    uint32_t nofVisibleTrees{0};

    for (size_t row = 0; row < m_map.Rows(); row++)
    {
        for (size_t col = 0; col < m_map.Cols(); col++)
        {
            if (IsTreeVisible(row, col))
            {
                nofVisibleTrees++;
            }
        }
    }

    m_result = std::to_string(nofVisibleTrees);
}

void Day8::Task2()
{
    if (m_map.Rows() == 0)
    {
        ParseInputFile();
    }

    uint32_t highestScenicScore{0};

    for (size_t row = 1; row < m_map.Rows() - 1; row++)
    {
        for (size_t col = 1; col < m_map.Cols() - 1; col++)
        {
            if (auto scenicScore = GetTreeScenicScore(row, col); scenicScore > highestScenicScore)
            {
                highestScenicScore = scenicScore;
            }
        }
    }

    m_result = std::to_string(highestScenicScore);
}

void Day8::ParseInputFile()
{
    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (!line.empty())
        {
            m_map.AppendRow();
        }

        for (size_t i = 0; i < line.length(); i++)
        {
            m_map.AppendValue(static_cast<TreeHeight>(line[i] - '0'));
        }
    }
}

bool Day8::IsTreeVisible(size_t treeRow, size_t treeCol)
{
    if ((treeRow == 0) || (treeRow == m_map.Rows() - 1) || (treeCol == 0) || (treeCol == m_map.Cols() - 1))
    {
        return true;
    }

    auto treeHeight = m_map.Get(treeRow, treeCol);

    auto pred = [treeHeight](auto h) { return h >= treeHeight; };

    // West
    auto west_first = m_map.row_begin(treeRow);
    auto west_last = std::next(m_map.row_begin(treeRow), treeCol);

    // East
    auto east_first = std::next(m_map.row_begin(treeRow), static_cast<size_t>(treeCol + 1));
    auto east_last = m_map.row_end(treeRow);

    // South
    auto south_first = std::next(m_map.column_begin(treeCol), static_cast<size_t>(treeRow + 1));
    auto south_last = m_map.column_end(treeCol);

    // North
    auto north_first = m_map.column_begin(treeCol);
    auto north_last = std::next(m_map.column_begin(treeCol), treeRow);

    return !std::any_of(west_first, west_last, pred) || !std::any_of(east_first, east_last, pred) ||
           !std::any_of(north_first, north_last, pred) || !std::any_of(south_first, south_last, pred);
}

uint32_t Day8::GetTreeScenicScore(size_t treeRow, size_t treeCol)
{
    auto treeHeight = m_map.Get(treeRow, treeCol);

    const auto pred = [treeHeight](auto t) { return t >= treeHeight; };

    const auto score = [pred](auto first, auto last, auto end) -> uint32_t {
        auto t = std::find_if(first, last, pred);
        if (t == end)
        {
            --t;
        }

        int32_t distance = static_cast<int32_t>(std::distance(first, t));
        return static_cast<uint32_t>(std::abs(distance)) + 1;
    };

    // West
    const auto west_first = std::next(m_map.row_rbegin(treeRow), m_map.Cols() - treeCol);
    const auto west_last = m_map.row_rend(treeRow);

    // East
    const auto east_first = std::next(m_map.row_begin(treeRow), treeCol + 1);
    const auto east_last = m_map.row_end(treeRow);

    // North
    const auto north_first = std::next(m_map.column_rbegin(treeCol), m_map.Rows() - treeRow);
    const auto north_last = m_map.column_rend(treeCol);

    // South
    const auto south_first = std::next(m_map.column_begin(treeCol), treeRow + 1);
    const auto south_last = m_map.column_end(treeCol);

    const auto west_score = score(west_first, west_last, m_map.row_rend(treeRow));
    const auto east_score = score(east_first, east_last, m_map.row_end(treeRow));
    const auto north_score = score(north_first, north_last, m_map.column_rend(treeCol));
    const auto south_score = score(south_first, south_last, m_map.column_end(treeCol));

    return west_score * east_score * north_score * south_score;
}
}