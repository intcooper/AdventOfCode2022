#pragma once

#include <vector>
#include <string_view>

namespace AdventOfCode::Utils
{
	static std::vector<std::string_view> Split(std::string_view line, const char separator)
	{
		std::vector<std::string_view> items;

		size_t startPos{ 0 };
		size_t pos = line.find(separator, startPos);

		while (pos != std::string_view::npos)
		{
			items.emplace_back(line.substr(startPos, pos - startPos));
			startPos = ++pos;
			pos = line.find(separator, startPos);
		}

		items.emplace_back(line.substr(startPos));

		return items;
	}
}