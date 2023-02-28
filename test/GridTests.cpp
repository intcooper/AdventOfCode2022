#include <algorithm>
#include <iterator>
#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>
namespace utf = boost::unit_test;

#include "utils/Grid.hpp"

namespace AdventOfCode2022Tests
{
constexpr uint32_t GridRows{10};
constexpr uint32_t GridColumns{10};
AdventOfCode::Utils::Grid<uint8_t> grid;

struct GridTestsSuiteFixture
{
    GridTestsSuiteFixture()
    {
        BOOST_TEST_MESSAGE("setup fixture");

        for (int j = 0; j < GridRows; ++j)
        {
            grid.AppendRow();

            for (int i = 0; i < GridColumns; ++i)
            {
                grid.AppendValue(i + (10 * j));
            }
        }
    }

    ~GridTestsSuiteFixture()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
    }
};

BOOST_AUTO_TEST_SUITE(GridRowIteratorSuite, *utf::fixture<GridTestsSuiteFixture>())

BOOST_AUTO_TEST_CASE(row_begin_points_to_first_element)
{
    BOOST_REQUIRE_EQUAL(*grid.row_begin(0), 0);
}

BOOST_AUTO_TEST_CASE(row_end_points_to_past_the_last_row_element)
{
    BOOST_REQUIRE_EQUAL(*--grid.row_end(0), 9);
}

BOOST_AUTO_TEST_CASE(row_rbegin_points_to_the_last_row_element)
{
    BOOST_REQUIRE_EQUAL(*grid.row_rbegin(0), 9);
    BOOST_REQUIRE_EQUAL(*grid2.begin()->rbegin(), 9);
}

BOOST_AUTO_TEST_CASE(row_rend_points_to_before_the_first_row_element)
{
    BOOST_REQUIRE_EQUAL(*--grid.row_rend(0), 0);
    BOOST_REQUIRE_EQUAL(*--grid2.begin()->rend(), 0);
}

BOOST_AUTO_TEST_CASE(distance_between_begin_and_end_is_row_size)
{
    BOOST_REQUIRE_EQUAL(std::distance(grid.row_begin(0), grid.row_end(0)), grid.Cols());
}

BOOST_AUTO_TEST_CASE(distance_between_rbegin_and_rend_is_row_size)
{
    BOOST_REQUIRE_EQUAL(std::distance(grid.row_rbegin(0), grid.row_rend(0)), grid.Cols());
}

BOOST_AUTO_TEST_CASE(reverse_iter_next_is_previous_element)
{
    BOOST_REQUIRE_EQUAL(*std::next(grid.row_rbegin(0)), 8);
    BOOST_REQUIRE_EQUAL(*std::next(grid.row_rbegin(0), 5), 4);
    BOOST_REQUIRE(std::next(grid.row_rbegin(0), 10) == grid.row_rend(0));
}

BOOST_AUTO_TEST_CASE(iter_find_if)
{
    auto it = std::find_if(grid.row_begin(0), grid.row_end(0), [](auto i){ return i == 5; });
    BOOST_REQUIRE_EQUAL(*it, 5);
    BOOST_REQUIRE_EQUAL(std::distance(grid.row_begin(0), it), 5);
}

BOOST_AUTO_TEST_CASE(reverse_iter_find_if)
{
    auto it = std::find_if(grid.row_rbegin(0), grid.row_rend(0), [](auto i){ return i == 5; });
    BOOST_REQUIRE_EQUAL(*it, 5);
    BOOST_REQUIRE_EQUAL(std::distance(grid.row_rbegin(0), it), 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GridColumnIteratorSuite, *utf::fixture<GridTestsSuiteFixture>())

BOOST_AUTO_TEST_CASE(column_begin_points_to_first_element)
{
    BOOST_REQUIRE_EQUAL(*grid.column_begin(0), 0);
}

BOOST_AUTO_TEST_CASE(column_end_points_to_past_the_last_column_element)
{
    BOOST_REQUIRE_EQUAL(*--grid.column_end(0), 90);
}

BOOST_AUTO_TEST_CASE(column_rbegin_points_to_the_last_column_element)
{
    BOOST_REQUIRE_EQUAL(*grid.column_rbegin(0), 90);
}

BOOST_AUTO_TEST_CASE(column_rend_points_to_before_the_first_column_element)
{
    BOOST_REQUIRE_EQUAL(*--grid.column_rend(0), 0);
}

BOOST_AUTO_TEST_CASE(distance_between_begin_and_end_is_column_size)
{
    BOOST_REQUIRE_EQUAL(std::distance(grid.column_begin(0), grid.column_end(0)), grid.Rows());
}

BOOST_AUTO_TEST_CASE(distance_between_rbegin_and_rend_is_column_size)
{
    BOOST_REQUIRE_EQUAL(std::distance(grid.column_rbegin(0), grid.column_rend(0)), grid.Rows());
}

BOOST_AUTO_TEST_CASE(reverse_iter_next_is_previous_element)
{
    BOOST_REQUIRE_EQUAL(*std::next(grid.column_rbegin(0)), 80);
    BOOST_REQUIRE_EQUAL(*std::next(grid.column_rbegin(0), 5), 40);
    BOOST_REQUIRE(std::next(grid.column_rbegin(0), grid.Rows()) == grid.column_rend(0));
}


BOOST_AUTO_TEST_CASE(iter_find_if)
{
    auto it = std::find_if(grid.column_begin(0), grid.column_end(0), [](auto i){ return i == 50; });
    BOOST_REQUIRE_EQUAL(*it, 50);
    BOOST_REQUIRE_EQUAL(std::distance(grid.column_begin(0), it), 5);
}

BOOST_AUTO_TEST_CASE(reverse_iter_find_if)
{
    auto it = std::find_if(grid.column_rbegin(0), grid.column_rend(0), [](auto i){ return i == 50; });
    BOOST_REQUIRE_EQUAL(*it, 50);
    BOOST_REQUIRE_EQUAL(std::distance(grid.column_rbegin(0), it), 4);
}

BOOST_AUTO_TEST_SUITE_END()
}