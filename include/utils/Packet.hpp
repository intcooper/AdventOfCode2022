#pragma once

#include <map>

namespace AdventOfCode::Utils
{

class Packet
{
  public:
    Packet()
        : m_values()
        , m_lists()
        , m_parent(nullptr)
        , m_maxIndex(0)
    {
    }

    explicit Packet(Packet* parent)
        : m_values()
        , m_lists()
        , m_parent(parent)
        , m_maxIndex(0)
    {
    }

    bool operator==(const Packet& other) const
    {
        auto areValuesEqual =
            m_values.size() == other.m_values.size() && std::equal(m_values.begin(), m_values.end(), other.m_values.begin());

        auto areListsEqual =
            m_lists.size() == other.m_lists.size() && std::equal(m_lists.begin(), m_lists.end(), other.m_lists.begin());

        return areValuesEqual && areListsEqual;
    }

    void AppendValue(uint8_t value)
    {
        m_values[m_maxIndex++] = value;
    }

    void AddValue(int index, uint8_t value)
    {
        m_values[index] = value;

        if (index > m_maxIndex)
        {
            m_maxIndex = index;
        }
    }

    void AppendList(const Packet& packet)
    {
        m_lists[m_maxIndex++] = packet;
    }

    void AddList(int index, const Packet& packet)
    {
        m_lists[index] = packet;

        if (index > m_maxIndex)
        {
            m_maxIndex = index;
        }
    }

    Packet* GetParent() const
    {
        return m_parent;
    }

    int GetMaxIndex() const
    {
        return m_maxIndex;
    }

    bool IsValue(int index) const
    {
        return m_values.contains(index);
    }

    char GetValue(int index) const
    {
        return m_values.at(index);
    }

    bool IsList(int index) const
    {
        return m_lists.contains(index);
    }

    const Packet& GetList(int index) const
    {
        return m_lists.at(index);
    }

    void ConvertToList(int index)
    {
        if (IsValue(index))
        {
            Packet newList(this);
            newList.AddValue(0, m_values.at(index));
            AddList(index, newList);
            m_values.erase(index);
        }
    }

  private:
    std::map<int, uint8_t> m_values;
    std::map<int, Packet> m_lists;
    Packet* m_parent;
    int m_maxIndex;
};
}