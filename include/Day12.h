#pragma once

#include "DailyTask.h"
#include "Point.hpp"

#include <stdint.h>
#include <string>
#include <vector>

namespace AdventOfCode
{
	class Day12 : public DailyTask
	{
	public:
		Day12(std::string inputFileName);

		inline virtual std::string GetTitle() const override
		{
			return "Day 12 - Hill Climbing Algorithm";
		}

		virtual void Task1() override;
		virtual void Task2() override;

	private:
        std::vector<std::string> m_map;
        Point m_startPos;
        Point m_endPos;
        std::vector<Point> m_candidateStartPos;

        std::vector<Point> Explore(const Point& start, const Point& end);
        void ParseInputFile();
	};
}
