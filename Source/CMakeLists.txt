# CMakeList.txt : CMake project for AdventOfCode2022, include source and define
# project specific logic here.
#

add_library(adventofcode2022_compiler_flags INTERFACE)
target_compile_options(adventofcode2022_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
  "$<${msvc_cxx}:-W3>"
)

target_compile_options(adventofcode2022_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# Add source to this project's executable.
add_executable (
	AdventOfCode2022 
	"AdventOfCode2022.cpp"
	"AdventOfCode2022.h"
	"Utils.hpp"
	"Day1.h"
	"Day1.cpp"
	"Day2.h"
	"Day2.cpp"
	"Day3.h"
	"Day3.cpp"
	"Day4.h"
	"Day4.cpp"
	"Day5.h"
	"Day5.cpp"
	"Day6.h"
	"Day6.cpp"
	"Day7/Day7.h"
	"Day7/Day7.cpp"
	"Day7/Directory.h"
	"Day7/File.h"
	"Day7/Directory.cpp"
	"Day8/Day8.h"
	"Day8/Day8.cpp"
	"Day8/Grid.h"
	"Day9/Day9.h"
	"Day9/Day9.cpp"
	"Day10.h"
	"Day10.cpp"
	"Day11/Monkey.h"
	"Day11/Day11.h"
	"Day11/Day11.cpp"
	"Day12.h"
	"Day12.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventOfCode2022 PROPERTY CXX_STANDARD 20)
endif()


install(TARGETS AdventOfCode2022 DESTINATION bin)
install(FILES ../InputFiles/day1input.txt DESTINATION bin)
install(FILES ../InputFiles/day2input.txt DESTINATION bin)
install(FILES ../InputFiles/day3input.txt DESTINATION bin)
install(FILES ../InputFiles/day4input.txt DESTINATION bin)
install(FILES ../InputFiles/day5input.txt DESTINATION bin)
install(FILES ../InputFiles/day6input.txt DESTINATION bin)
install(FILES ../InputFiles/day7input.txt DESTINATION bin)
install(FILES ../InputFiles/day8input.txt DESTINATION bin)
install(FILES ../InputFiles/day9input.txt DESTINATION bin)
install(FILES ../InputFiles/day10input.txt DESTINATION bin)
install(FILES ../InputFiles/day11input.txt DESTINATION bin)
install(FILES ../InputFiles/day12input.txt DESTINATION bin)

enable_testing()

function(do_test target arg1 arg2 result)
  add_test(NAME Comp${arg1} COMMAND ${target} ${arg1} ${arg2})
  set_tests_properties(Comp${arg1}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(AdventOfCode2022 1 ../../InputFiles/day1input.txt "  Task1: 74711\n  Task2: 209481")
do_test(AdventOfCode2022 2 ../../InputFiles/day2input.txt "  Task1: 10718\n  Task2: 14652")
do_test(AdventOfCode2022 3 ../../InputFiles/day3input.txt "  Task1: 8394\n  Task2: 2413")
do_test(AdventOfCode2022 4 ../../InputFiles/day4input.txt "  Task1: 471\n  Task2: 888")
do_test(AdventOfCode2022 5 ../../InputFiles/day5input.txt "  Task1: GRTSWNJHH\n  Task2: QLFQDBBHM")
do_test(AdventOfCode2022 6 ../../InputFiles/day6input.txt "  Task1: 1480\n  Task2: 2746")
do_test(AdventOfCode2022 7 ../../InputFiles/day7input.txt "  Task1: 1845346\n  Task2: 3636703")
do_test(AdventOfCode2022 8 ../../InputFiles/day8input.txt "  Task1: 1662\n  Task2: 537600")
do_test(AdventOfCode2022 9 ../../InputFiles/day9input.txt "  Task1: 6057\n  Task2: 2514")
do_test(AdventOfCode2022 10 ../../InputFiles/day10input.txt "  Task1: 14060")
do_test(AdventOfCode2022 11 ../../InputFiles/day11input.txt "  Task1: 76728\n  Task2: 21553910156")
do_test(AdventOfCode2022 12 ../../InputFiles/day12input.txt "  Task1: 391\n  Task2: 386")


