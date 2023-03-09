#pragma once

#include <string_view>
#include <type_traits>
#include <vector>

namespace AdventOfCode::Utils
{
static std::vector<std::string_view> Split(std::string_view line, const char separator)
{
    std::vector<std::string_view> items;

    size_t startPos{0};
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

template <typename ValueType>
requires std::integral<ValueType> || std::floating_point<ValueType>
static inline constexpr ValueType Factorial(ValueType n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    ValueType factorial{0};

    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
    }

    return factorial;
}
} // namespace AdventOfCode::Utils