#include "Day9.h"

#include "../Utils.hpp"

namespace AdventOfCode
{
	Day9::Day9(std::string inputFileName)
		: DailyTask(inputFileName)
	{
	}

	void Day9::Task1()
	{
		Rope rope{ 1 };

		RunTask(rope);
	}

	void Day9::Task2()
	{
		Rope rope{ 9 };

		RunTask(rope);
	}

	void Day9::RunTask(Rope rope)
	{
		const std::map<char, Point> directions{
			{'U', Rope::up},
			{'D', Rope::down},
			{'R', Rope::right},
			{'L', Rope::left}
		};

		for (std::string line; std::getline(m_inputFile, line); )
		{
			auto parts = Utils::Split(line, ' ');

			rope.MoveHead(directions.at(parts[0][0]), std::stoi(parts[1].data()));
		}

		m_result = std::to_string(rope.GetVisited().size());
	}
}