#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;

#include "utils/Point.hpp"

namespace AdventOfCode::Tests
{

struct PointsTestsSuiteFixture
{
    PointsTestsSuiteFixture()
    {
        BOOST_TEST_MESSAGE("setup fixture");
    }

    ~PointsTestsSuiteFixture()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
    }
};

BOOST_AUTO_TEST_SUITE(PointTestSuite, *utf::fixture<PointsTestsSuiteFixture>())

BOOST_AUTO_TEST_CASE(default_constructor)
{
    AdventOfCode::Utils::Point p;
    BOOST_REQUIRE_EQUAL(p.x, 0);
    BOOST_REQUIRE_EQUAL(p.y, 0);
}

BOOST_AUTO_TEST_CASE(constructor_from_coordinates)
{
    AdventOfCode::Utils::Point p{1, 2};
    BOOST_REQUIRE_EQUAL(p.x, 1);
    BOOST_REQUIRE_EQUAL(p.y, 2);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
    AdventOfCode::Utils::Point p1{1, 2};
    AdventOfCode::Utils::Point p2(p1);
    BOOST_REQUIRE_EQUAL(p2.x, 1);
    BOOST_REQUIRE_EQUAL(p2.y, 2);
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
    AdventOfCode::Utils::Point p2({1, 2});
    BOOST_REQUIRE_EQUAL(p2.x, 1);
    BOOST_REQUIRE_EQUAL(p2.y, 2);
}

BOOST_AUTO_TEST_CASE(equal_to_operator)
{
    AdventOfCode::Utils::Point p1{1, 2};
    AdventOfCode::Utils::Point p2{1, 2};
    BOOST_REQUIRE(p1 == p2);
}

BOOST_AUTO_TEST_CASE(not_equal_to_operator)
{
    AdventOfCode::Utils::Point p1{1, 2};
    AdventOfCode::Utils::Point p2{1, 2};
    BOOST_REQUIRE_EQUAL(p1 != p2, false);
}

BOOST_AUTO_TEST_CASE(subtraction_operator)
{
    AdventOfCode::Utils::Point p1{5, 4};
    AdventOfCode::Utils::Point p2{2, 1};
    BOOST_REQUIRE_EQUAL(p1 - p2, AdventOfCode::Utils::Point(3, 3));
}

BOOST_AUTO_TEST_CASE(subtract_int_operator)
{
    AdventOfCode::Utils::Point p1{5, 4};
    BOOST_REQUIRE_EQUAL(p1 - 2, AdventOfCode::Utils::Point(3, 2));
}

BOOST_AUTO_TEST_CASE(addition_operator)
{
    AdventOfCode::Utils::Point p1{5, 4};
    AdventOfCode::Utils::Point p2{2, 1};
    BOOST_REQUIRE_EQUAL(p1 + p2, AdventOfCode::Utils::Point(7, 5));
}

BOOST_AUTO_TEST_CASE(multiply_by_int_operator)
{
    AdventOfCode::Utils::Point p1{5, 4};
    BOOST_REQUIRE_EQUAL(p1 * 2, AdventOfCode::Utils::Point(10, 8));
}

BOOST_AUTO_TEST_CASE(addition_assignment_operator)
{
    AdventOfCode::Utils::Point p1{5, 4};
    AdventOfCode::Utils::Point p2{2, 1};
    p1 += p2;
    BOOST_REQUIRE_EQUAL(p1, AdventOfCode::Utils::Point(7, 5));
}

BOOST_AUTO_TEST_CASE(division_assignment_operator)
{
    AdventOfCode::Utils::Point p1{6, 4};
    AdventOfCode::Utils::Point p2{2, 2};
    p1 /= p2;
    BOOST_REQUIRE_EQUAL(p1, AdventOfCode::Utils::Point(3, 2));
}

BOOST_AUTO_TEST_CASE(division_assignment_operator_by_zero_does_not_fail)
{
    AdventOfCode::Utils::Point p1{6, 4};
    AdventOfCode::Utils::Point p2{0, 2};
    p1 /= p2;
    BOOST_REQUIRE_EQUAL(p1, AdventOfCode::Utils::Point(6, 2));
}

BOOST_AUTO_TEST_CASE(less_than_operator)
{
    AdventOfCode::Utils::Point p1{6, 4};
    AdventOfCode::Utils::Point p2{0, 2};
    BOOST_REQUIRE(p2 < p1);
}

BOOST_AUTO_TEST_CASE(greater_than_operator)
{
    AdventOfCode::Utils::Point p1{6, 4};
    AdventOfCode::Utils::Point p2{0, 2};
    BOOST_REQUIRE(p1 > p2);
}

BOOST_AUTO_TEST_CASE(distance_between_points_is_manhattan_distance)
{
    AdventOfCode::Utils::Point p1{1, 1};
    AdventOfCode::Utils::Point p2{2, 2};
    BOOST_REQUIRE_EQUAL(p1.Distance(p2), 2);
}


BOOST_AUTO_TEST_SUITE_END()

}