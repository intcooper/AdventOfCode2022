# CMakeList.txt : CMake project for AdventOfCode2022, include source and define
# project specific logic here.
#

add_library(adventofcode2022tests_compiler_flags INTERFACE)
target_compile_options(adventofcode2022tests_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
  "$<${msvc_cxx}:-W3>"
)

target_compile_options(adventofcode2022tests_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_executable (
	AdventOfCode2022Tests 
	"GridTests.cpp"
)

find_package(Boost COMPONENTS test REQUIRED)

target_include_directories(AdventOfCode2022Tests PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(AdventOfCode2022Tests PRIVATE ../include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventOfCode2022Tests PROPERTY CXX_STANDARD 20)
endif()


