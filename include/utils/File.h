#pragma once

#include <string>

namespace AdventOfCode::Utils
{

class File
{
  public:
    File(std::string name, uint32_t size)
        : m_name{name}
        , m_size{size}
    {
    }

    inline std::string GetName() const
    {
        return m_name;
    }

    inline uint32_t GetSize() const
    {
        return m_size;
    }

  private:
    std::string m_name;
    uint32_t m_size;
};

}