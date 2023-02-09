#include "Directory.h"

namespace AdventOfCode
{
Directory::Directory(const std::string &name, Directory *parent)
    : m_name{name}
    , m_parent{parent}
{
}

std::string Directory::GetName() const
{
    return m_name;
}

Directory *Directory::GetParent() const
{
    return m_parent;
}

void Directory::AddFile(std::unique_ptr<File> &&file)
{
    m_files.push_back(std::move(file));
}

void Directory::AddDirectory(std::unique_ptr<Directory> &&directory)
{
    m_directories.push_back(std::move(directory));
}

std::multimap<std::string, uint32_t>
Directory::FindDirectoriesOfMaxSize(uint32_t maxSize) const
{
    std::multimap<std::string, uint32_t> directories;

    FindDirectoriesOfMaxSizeInternal(maxSize, directories);

    return directories;
}

uint32_t Directory::FindDirectoriesOfMaxSizeInternal(
    uint32_t maxSize, std::multimap<std::string, uint32_t> &directories) const
{
    uint32_t totalSize{0};

    for (const auto &d : m_directories)
    {
        auto size = d->FindDirectoriesOfMaxSizeInternal(maxSize, directories);
        totalSize += size;
    }

    for (const auto &f : m_files)
    {
        auto size = f->GetSize();
        totalSize += size;
    }

    if (totalSize <= maxSize)
    {
        directories.emplace(m_name, totalSize);
    }

    return totalSize;
}

Directory *Directory::GetDirectory(const std::string &name) const
{
    for (auto &d : m_directories)
    {
        if (d->GetName() == name)
        {
            return d.get();
        }
    }

    return nullptr;
}

bool Directory::HasChildren() const
{
    return !m_directories.empty();
}
}
