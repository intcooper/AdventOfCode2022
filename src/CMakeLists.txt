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

add_executable (
	AdventOfCode2022 
	"AdventOfCode2022.cpp"
	"Day1.cpp"
	"Day2.cpp"
	"Day3.cpp"
	"Day4.cpp"
	"Day5.cpp"
	"Day6.cpp"
	"Day7.cpp"
	"Directory.cpp"
	"Day8.cpp"
	"Day9.cpp"
	"Day10.cpp"
	"Day11.cpp"
	"Day12.cpp"
	"Day13.cpp"
	"Day14.cpp"
	"Day15.cpp"
)

target_include_directories(AdventOfCode2022 PRIVATE ../include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventOfCode2022 PROPERTY CXX_STANDARD 20)
endif()


install(TARGETS AdventOfCode2022 DESTINATION bin)
install(FILES ../res/day1input.txt DESTINATION bin)
install(FILES ../res/day2input.txt DESTINATION bin)
install(FILES ../res/day3input.txt DESTINATION bin)
install(FILES ../res/day4input.txt DESTINATION bin)
install(FILES ../res/day5input.txt DESTINATION bin)
install(FILES ../res/day6input.txt DESTINATION bin)
install(FILES ../res/day7input.txt DESTINATION bin)
install(FILES ../res/day8input.txt DESTINATION bin)
install(FILES ../res/day9input.txt DESTINATION bin)
install(FILES ../res/day10input.txt DESTINATION bin)
install(FILES ../res/day11input.txt DESTINATION bin)
install(FILES ../res/day12input.txt DESTINATION bin)
install(FILES ../res/day13input.txt DESTINATION bin)
install(FILES ../res/day14input.txt DESTINATION bin)
install(FILES ../res/day15input.txt DESTINATION bin)

enable_testing()

function(do_test name target arg1 arg2 arg3 result)
  add_test(NAME Comp${name} COMMAND ${target} ${arg1} ${arg2} ${arg3})
  set_tests_properties(Comp${name}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(Day1_example   AdventOfCode2022 1 ../../res/day1input_example.txt   "" "  Task1: 24000\n  Task2: 45000")
do_test(Day1           AdventOfCode2022 1 ../../res/day1input.txt           "" "  Task1: 74711\n  Task2: 209481")
do_test(Day2_example   AdventOfCode2022 2 ../../res/day2input_example.txt   "" "  Task1: 15\n  Task2: 12")
do_test(Day2           AdventOfCode2022 2 ../../res/day2input.txt           "" "  Task1: 10718\n  Task2: 14652")
do_test(Day3_example   AdventOfCode2022 3 ../../res/day3input_example.txt   "" "  Task1: 157\n  Task2: 70")
do_test(Day3           AdventOfCode2022 3 ../../res/day3input.txt           "" "  Task1: 8394\n  Task2: 2413")
do_test(Day4_example   AdventOfCode2022 4 ../../res/day4input_example.txt   "" "  Task1: 2\n  Task2: 4")
do_test(Day4           AdventOfCode2022 4 ../../res/day4input.txt           "" "  Task1: 471\n  Task2: 888")
do_test(Day5_example   AdventOfCode2022 5 ../../res/day5input_example.txt   "" "  Task1: CMZ\n  Task2: MCD")
do_test(Day5           AdventOfCode2022 5 ../../res/day5input.txt           "" "  Task1: GRTSWNJHH\n  Task2: QLFQDBBHM")
do_test(Day6_example   AdventOfCode2022 6 ../../res/day6input_example.txt   "" "  Task1: 7\n  Task2: 19")
do_test(Day6           AdventOfCode2022 6 ../../res/day6input.txt           "" "  Task1: 1480\n  Task2: 2746")
do_test(Day7_example   AdventOfCode2022 7 ../../res/day7input_example.txt   "" "  Task1: 95437\n  Task2: 24933642")
do_test(Day7           AdventOfCode2022 7 ../../res/day7input.txt           "" "  Task1: 1845346\n  Task2: 3636703")
do_test(Day8_example   AdventOfCode2022 8 ../../res/day8input_example.txt   "" "  Task1: 21\n  Task2: 8")
do_test(Day8           AdventOfCode2022 8 ../../res/day8input.txt           "" "  Task1: 1662\n  Task2: 537600")
do_test(Day9_example1  AdventOfCode2022 9 ../../res/day9input_example1.txt  "" "  Task1: 13\n  Task2: 1")
do_test(Day9_example2  AdventOfCode2022 9 ../../res/day9input_example2.txt  "" "  Task1: 88\n  Task2: 36")
do_test(Day9           AdventOfCode2022 9 ../../res/day9input.txt           "" "  Task1: 6057\n  Task2: 2514")
do_test(Day10_example  AdventOfCode2022 10 ../../res/day10input_example.txt "" "  Task1: 13140")
do_test(Day10          AdventOfCode2022 10 ../../res/day10input.txt         "" "  Task1: 14060")
do_test(Day11_example  AdventOfCode2022 11 ../../res/day11input_example.txt "" "  Task1: 10605\n  Task2: 2713310158")
do_test(Day11          AdventOfCode2022 11 ../../res/day11input.txt         "" "  Task1: 76728\n  Task2: 21553910156")
do_test(Day12_example  AdventOfCode2022 12 ../../res/day12input_example.txt "" "  Task1: 31\n  Task2: 29")
do_test(Day12          AdventOfCode2022 12 ../../res/day12input.txt         "" "  Task1: 391\n  Task2: 386")
do_test(Day13_example  AdventOfCode2022 13 ../../res/day13input_example.txt "" "  Task1: 13\n  Task2: 140")
do_test(Day13          AdventOfCode2022 13 ../../res/day13input.txt         "" "  Task1: 6623\n  Task2: 23049")
do_test(Day14_example  AdventOfCode2022 14 ../../res/day14input_example.txt "" "  Task1: 24\n  Task2: 93")
do_test(Day14          AdventOfCode2022 14 ../../res/day14input.txt         "" "  Task1: 964\n  Task2: 32041")
do_test(Day15_example  AdventOfCode2022 15 ../../res/day15input_example.txt "10 20" "Task1: 26\n  Task2: 56000011")
do_test(Day15          AdventOfCode2022 15 ../../res/day15input.txt         "2000000 4000000" "Task1: 4424278\n  Task2: 10382630753392")
 