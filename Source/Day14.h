#pragma once

#include "DailyTask.h"

namespace AdventOfCode
{
	class Day14 : public DailyTask
	{
	public:
		Day14(std::string inputFileName);

		inline virtual std::string GetTitle() const override
		{
			return "Day 14 - Regolith Reservoir";
		}

		virtual void Task1() override;
		virtual void Task2() override;

	private:
	};
}
