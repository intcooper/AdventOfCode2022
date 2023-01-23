#pragma once

#include "DailyTask.h"

#include <string>
#include <array>
#include <functional>

namespace AdventOfCode
{
	class Day10 : public DailyTask
	{
	public:
		Day10(std::string inputFileName);

		inline virtual std::string GetTitle() const override
		{
			return "Day 10 - Cathode-Ray Tube";
		}

		virtual void Task1() override;
		virtual void Task2() override;

	private:
		static constexpr uint8_t ScreenRows{ 6 };
		static constexpr uint8_t ScreenCols{ 40 };

		std::array<std::array<char, ScreenCols>, ScreenRows> m_screen;
		uint32_t m_cycle;
		int32_t m_regX;

		void RunTask(std::function<void()>);

		inline constexpr int32_t CheckSignal() const
		{
			if ((m_cycle >= 20) && ((m_cycle - 20) % 40 == 0))
			{
				return m_cycle * m_regX;
			}

			return 0;
		}

		inline constexpr void SetCurrentPixel(bool state)
		{
			const auto screenRow = (m_cycle - 1) / ScreenCols;
			const auto screenCol = (m_cycle - 1) % ScreenCols;
			m_screen[screenRow][screenCol] = state ? '#' : '.';
		}

		void SetCurrentPixel()
		{
			const auto currentPixel = (m_cycle - 1) % ScreenCols;

			if (std::abs(static_cast<int>(currentPixel - m_regX)) <= 1)
			{
				SetCurrentPixel(true);
			}
			else
			{
				SetCurrentPixel(false);
			}
		}
	};
}
