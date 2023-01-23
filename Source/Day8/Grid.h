#pragma once

#include <numeric>
#include <vector>
#include <algorithm>

#include <iterator>

namespace AdventOfCode
{
	/// <summary>
	/// Templated implementation of a dynamic bi-dimensional array.
	/// </summary>
	/// <typeparam name="ValueType">The element type.</typeparam>
	/// <remarks>
	/// The internal structure is a vector of vectors of ValueType. 
	/// Adding an element to the container invalidates all the iterators!
	/// To-do: implement const iterators.
	/// </remarks>
	template<class ValueType>
	class Grid
	{
	public:
		template<class GridType>
		class ColumnIterator;

		template<class GridType>
		class RowIterator;

		using value_type = ValueType;
		using pointer = ValueType*;
		using reference = ValueType&;
		using column_iterator = ColumnIterator<Grid<ValueType>>;
		using row_iterator = RowIterator<Grid<ValueType>>;

		void AppendRow()
		{
			m_map.emplace_back();
		};

		void AppendTree(ValueType height)
		{
			m_map.rbegin()->push_back(height);
		}

		size_t Rows() const
		{
			return m_map.size();
		}

		size_t Cols() const
		{
			return m_map[0].size(); // assuming that all the rows have the same number of columns
		}

		ValueType Get(size_t treeRow, size_t treeCol) const
		{
			if ((treeRow >= m_map.size()) || (treeCol >= m_map[0].size()))
			{
				return -1;
			}

			return m_map[treeRow][treeCol];
		}

	private:
		std::vector<std::vector<ValueType>> m_map;


	public:
		column_iterator column_begin(size_t column)
		{
			return column_iterator(this, column, 0, false);
		}

		column_iterator column_end(size_t column)
		{
			return column_iterator(this, column, std::numeric_limits<size_t>::max(), true);
		}

		std::reverse_iterator<column_iterator> column_rbegin(size_t column)
		{
			return std::reverse_iterator<column_iterator>(column_end(column));
		}

		std::reverse_iterator<column_iterator> column_rend(size_t column)
		{
			return std::make_reverse_iterator<column_iterator>(column_begin(column));
		}

		row_iterator row_begin(size_t row)
		{
			return row_iterator(this, row, 0, false);
		}

		row_iterator row_end(size_t row)
		{
			return row_iterator(this, row, std::numeric_limits<size_t>::max(), true);
		}

		std::reverse_iterator<row_iterator> row_rbegin(size_t row)
		{
			return std::reverse_iterator<row_iterator>(row_end(row));
		}

		std::reverse_iterator<row_iterator> row_rend(size_t row)
		{
			return std::make_reverse_iterator<row_iterator>(row_begin(row));
		}


	private:
		template<class GridType>
		class GridIterator
		{
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = size_t;
			using value_type = typename GridType::value_type;
			using pointer = typename GridType::pointer;
			using reference = typename GridType::reference;

			GridIterator() noexcept
				: m_map{ nullptr }
				, m_row{ std::numeric_limits<size_t>::max() }
				, m_column{ std::numeric_limits<size_t>::max() }
				, m_isEnd{ true }
			{
			}

			GridIterator(GridType* ptr, difference_type column, difference_type row, bool isEnd) noexcept
				: m_map{ ptr }
				, m_row{ row }
				, m_column{ column }
				, m_isEnd{ isEnd }
			{
			}

			reference operator*()
			{
				return m_map->m_map[m_row][m_column];
			}

			pointer operator->()
			{
				return &m_map->m_map[m_row][m_column];
			}

			// Postfix increment
			GridIterator operator++(int)
			{
				GridIterator tmp = *this;
				++(*this);
				return tmp;
			}

			// Postfix decrement
			GridIterator operator--(int)
			{
				GridIterator tmp = *this;
				--(*this);
				return tmp;
			}

			friend bool operator== (const GridIterator& a, const GridIterator& b)
			{
				return (a.m_map == b.m_map) && ((a.m_isEnd && b.m_isEnd) || ((a.m_column == b.m_column) && (a.m_row == b.m_row)));
			};

			friend bool operator!= (const GridIterator& a, const GridIterator& b)
			{
				return !operator==(a, b);
			};

		protected:
			GridType* m_map;
			difference_type m_row;
			difference_type m_column;
			bool m_isEnd;
		};


		public:
		template<class GridType>
		class ColumnIterator : public GridIterator<GridType>
		{
		public:
            ColumnIterator()
            {
            }

			ColumnIterator(GridType* ptr, typename GridIterator<GridType>::difference_type column, typename GridIterator<GridType>::difference_type row, bool isEnd) noexcept
				: GridIterator<GridType>(ptr, column, row, isEnd )
			{
			}

			// Prefix increment
			ColumnIterator& operator++()
			{
				if (!this->m_isEnd)
				{
					if (this->m_row == this->m_map->Rows() - 1)
					{
						this->m_isEnd = true;
					}
					else
					{
						this->m_row++;
					}
				}

				return *this;
			}

			// Prefix decrement
			ColumnIterator& operator--()
			{
				if (!this->m_isEnd)
				{
					if (this->m_row == 0)
					{
						this->m_isEnd = true;
					}
					else
					{
						this->m_row--;
					}
				}
				else
				{
					if (this->m_row >= this->m_map->Rows())
					{
						this->m_row = this->m_map->Rows() - 1;
						this->m_isEnd = false;
					}
				}

				return *this;
			}
		};



		template<class GridType>
		class RowIterator : public GridIterator<GridType>
		{
		public:
            RowIterator()
            {
            }

			RowIterator(GridType* ptr, typename GridIterator<GridType>::difference_type row, typename GridIterator<GridType>::difference_type column, bool isEnd) noexcept
				: GridIterator<GridType>(ptr, column, row, isEnd)
			{
			}

			// Prefix increment
			RowIterator& operator++()
			{
				if (!this->m_isEnd)
				{
					if (this->m_column == this->m_map->Cols() - 1)
					{
						this->m_isEnd = true;
					}
					else
					{
						this->m_column++;
					}
				}

				return *this;
			}

			// Prefix decrement
			RowIterator& operator--()
			{
				if (!this->m_isEnd)
				{
					if (this->m_column == 0)
					{
						this->m_isEnd = true;
					}
					else
					{
						this->m_column--;
					}
				}
				else
				{
					if (this->m_column >= this->m_map->Cols())
					{
						this->m_column = this->m_map->Cols() - 1;
						this->m_isEnd = false;
					}
				}

				return *this;
			}

		};

	};

}