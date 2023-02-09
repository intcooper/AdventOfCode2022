#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Utils.hpp"

namespace AdventOfCode
{
	class DailyTask
	{
	public:
		DailyTask()
			: m_inputFileName{}
			, m_result{ 0 }
		{
		}

		DailyTask(std::string inputFileName)
			: m_inputFileName{ inputFileName }
			, m_result{ 0 }
			, m_inputFile{inputFileName}
		{
		}

		virtual ~DailyTask() = default;

		void Run()
		{
			std::cout << GetTitle() << '\n';

			std::cout << "  Task1: ";
			Task1();
			std::cout << GetResult() << '\n';

			m_inputFile.clear();
			m_inputFile.seekg(0);

			std::cout << "  Task2: ";
			Task2();
			std::cout << GetResult() << '\n' << std::endl;
		}

	protected:
		std::string m_inputFileName;
		std::string m_result;
		std::ifstream m_inputFile;

		virtual std::string GetTitle() const = 0;
		virtual void Task1() = 0;
		virtual void Task2() = 0;
		
		inline virtual std::string GetResult() const
		{
			return m_result;
		};
	};
}