#include "Day7.h"

#include <deque>
#include <numeric>
#include <sstream>
#include <unordered_set>

namespace AdventOfCode
{
Day7::Day7(std::string inputFileName)
    : DailyTask(inputFileName)
    , m_fsRoot{"/", nullptr}
{
}

void Day7::Task1()
{
    ParseInputFile();

    // std::cout << PrintFs(&m_fsRoot);

    auto dirs = m_fsRoot.FindDirectoriesOfMaxSize(100'000);
    auto sizeOfDirs =
        std::accumulate(dirs.begin(), dirs.end(), 0,
                        [](auto a, auto b) { return a += b.second; });

    m_result = std::to_string(sizeOfDirs);
}

void Day7::Task2()
{
    if (!m_fsRoot.HasChildren())
    {
        ParseInputFile();
    }

    auto dirs = m_fsRoot.FindDirectoriesOfMaxSize(INT_MAX);

    auto sizeOfRoot = dirs.find("/")->second;

    auto freeSpace = 70'000'000 - sizeOfRoot;
    auto toBeFreed = 30'000'000 - freeSpace;

    uint32_t sizeOfDir = UINT32_MAX;

    for (const auto& dir : dirs)
    {
        if (dir.second >= toBeFreed)
        {
            if (dir.second < sizeOfDir)
            {
                sizeOfDir = dir.second;
            }
        }
    }

    m_result = std::to_string(sizeOfDir);
}

void Day7::ParseInputFile()
{
    Directory* currentDir = nullptr;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        auto parts = Utils::Split(line, ' ');

        if (parts[0] == "$")
        {
            if (parts[1] == "cd")
            {
                if (parts[2] == "/")
                {
                    currentDir = &m_fsRoot;
                }
                else
                {
                    if (parts[2] == "..")
                    {
                        if (currentDir != nullptr)
                        {
                            currentDir = currentDir->GetParent();
                        }
                    }
                    else
                    {
                        if (currentDir != nullptr)
                        {
                            currentDir =
                                currentDir->GetDirectory(parts[2].data());
                        }
                    }
                }
            }
        }
        else
        {
            if (parts[0] == "dir")
            {
                currentDir->AddDirectory(
                    std::make_unique<Directory>(parts[1].data(), currentDir));
            }
            else
            {
                currentDir->AddFile(std::make_unique<File>(
                    parts[1].data(),
                    static_cast<uint32_t>(std::stoi(parts[0].data()))));
            }
        }
    }
}

std::string Day7::PrintFs(Directory* root) const
{
    std::stringstream str;

    uint8_t levels{1};
    Directory* tmp = root;

    while (tmp->GetParent() != nullptr)
    {
        ++levels;
        tmp = tmp->GetParent();
    }

    str << std::string(levels - 1, '\t') << root->GetName() << "\n";

    for (auto& f : root->m_files)
    {
        str << std::string(levels, '\t') << f->GetName() << "\t" << f->GetSize()
            << "\n";
    }

    for (auto& d : root->m_directories)
    {
        str << PrintFs(d.get());
    }

    return str.str();
}
}