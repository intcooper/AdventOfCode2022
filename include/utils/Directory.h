#pragma once

#include "File.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace AdventOfCode::Utils
{

class Directory
{
  public:
    Directory(const std::string& name, Directory* parent);
    std::string GetName() const;
    Directory* GetParent() const;
    void AddFile(std::unique_ptr<File>&& file);
    void AddDirectory(std::unique_ptr<Directory>&& directory);
    std::multimap<std::string, uint32_t> FindDirectoriesOfMaxSize(uint32_t maxSize) const;
    Directory* GetDirectory(const std::string& name) const;
    bool HasChildren() const;
    
    [[nodiscard]] inline const std::vector<std::unique_ptr<Directory>>& GetDirectories() const
    {
        return m_directories;
    }

    [[nodiscard]] inline const std::vector<std::unique_ptr<File>>& GetFiles() const
    {
        return m_files;
    }

  private:
    std::string m_name;
    Directory* m_parent;
    std::vector<std::unique_ptr<Directory>> m_directories;
    std::vector<std::unique_ptr<File>> m_files;

    uint32_t FindDirectoriesOfMaxSizeInternal(uint32_t maxSize, std::multimap<std::string, uint32_t>& directories) const;
};
}
