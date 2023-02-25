// AdventOfCode2022.cpp : Defines the entry point for the application.
//

#include "AdventOfCode2022.h"

#include <optional>

auto GetCommandLineParams(int argc, char* argv[])
{
    return (argc > 1) 
    ? [&argc, &argv]()
      {
          const std::vector<std::string> params(argv, argv+argc);
          return std::optional{std::make_tuple(params[0], std::stoi(params[1]), params[2], params.size() > 3 ? params[3] : "")};
      }()
    : std::nullopt;
}

int main(int argc, char* argv[])
{
    const auto params = GetCommandLineParams(argc, argv);

    if (params == std::nullopt)
    {
        return 1;
    }

    const auto[ignore, day, inputFile, args] = params.value();

    std::unique_ptr<AdventOfCode::DailyTask> task;

    switch (day)
    {
    case 1:
        task = std::make_unique<AdventOfCode::Day1>(inputFile);
        break;
    case 2:
        task = std::make_unique<AdventOfCode::Day2>(inputFile);
        break;
    case 3:
        task = std::make_unique<AdventOfCode::Day3>(inputFile);
        break;
    case 4:
        task = std::make_unique<AdventOfCode::Day4>(inputFile);
        break;
    case 5:
        task = std::make_unique<AdventOfCode::Day5>(inputFile);
        break;
    case 6:
        task = std::make_unique<AdventOfCode::Day6>(inputFile);
        break;
    case 7:
        task = std::make_unique<AdventOfCode::Day7>(inputFile);
        break;
    case 8:
        task = std::make_unique<AdventOfCode::Day8>(inputFile);
        break;
    case 9:
        task = std::make_unique<AdventOfCode::Day9>(inputFile);
        break;
    case 10:
        task = std::make_unique<AdventOfCode::Day10>(inputFile);
        break;
    case 11:
        task = std::make_unique<AdventOfCode::Day11>(inputFile);
        break;
    case 12:
        task = std::make_unique<AdventOfCode::Day12>(inputFile);
        break;
    case 13:
        task = std::make_unique<AdventOfCode::Day13>(inputFile);
        break;
    case 14:
        task = std::make_unique<AdventOfCode::Day14>(inputFile);
        break;
    case 15:
        task = std::make_unique<AdventOfCode::Day15>(inputFile, args);
        break;
    }

    task->Run();

    return 0;
}
