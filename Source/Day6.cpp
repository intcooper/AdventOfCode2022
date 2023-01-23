#include "Day6.h"

#include <unordered_set>
#include <deque>

namespace AdventOfCode
{
	Day6::Day6(std::string inputFileName)
		: DailyTask(inputFileName)
	{
	}

	void Day6::Task1()
	{
		m_result = std::to_string(GetMarkerStart(4));
	}

	void Day6::Task2()
	{
		m_result = std::to_string(GetMarkerStart(14));
	}

	size_t Day6::GetMarkerStart(uint8_t markerSize)
	{
		std::unordered_set<char> marker;
		std::deque<char> buffer;
		size_t index{ 0 };

		for (char c; m_inputFile.get(c); )
		{
			++index;

			buffer.push_back(c);
			auto result = marker.insert(c);

			if (buffer.size() == markerSize)
			{
				marker.insert(buffer.begin(), buffer.end());

				if (marker.size() == markerSize)
				{
					break;
				}

				marker.clear();
			}

			if (index >= markerSize)
			{
				buffer.pop_front();
			}
		}

		return index;
	}
}