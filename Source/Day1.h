#pragma once

#include "DailyTask.h"

namespace AdventOfCode
{
	class Day1 : public DailyTask
	{
	public:
		Day1(std::string inputFileName);

		inline virtual std::string GetTitle() const override
		{
			return "Day 1 - Calorie Counting";
		}

		virtual void Task1() override;
		virtual void Task2() override;
	};
}