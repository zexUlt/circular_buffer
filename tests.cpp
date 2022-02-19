#include "CircularBuffer.hpp"
#define BOOST_TEST_MODULE Testing
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE( constructors_test )
{
    CircularBuffer<3, int> rb;
    BOOST_CHECK_EQUAL(rb.empty(), true);
    BOOST_CHECK_EQUAL(rb.full(), false);
    BOOST_CHECK_EQUAL(rb.size(), 0);

    CircularBuffer<3, int> rb1{1, 2, 3};
    BOOST_CHECK_EQUAL(rb1.empty(), false);
    BOOST_CHECK_EQUAL(rb1.full(), true);
    BOOST_CHECK_EQUAL(rb1.size(), 3);
    BOOST_CHECK_EQUAL(rb1.front(), 1);
    BOOST_CHECK_EQUAL(rb1.back(), 3);

    rb = rb;
    BOOST_CHECK_EQUAL(rb.empty(), true);
    BOOST_CHECK_EQUAL(rb.full(), false);
    BOOST_CHECK_EQUAL(rb.size(), 0);

    CircularBuffer<3, int> rb2(rb1);
    BOOST_CHECK_EQUAL(rb2.empty(), false);
    BOOST_CHECK_EQUAL(rb2.full(), true);
    BOOST_CHECK_EQUAL(rb2.size(), 3);
    BOOST_CHECK_EQUAL(rb2.front(), 1);
    BOOST_CHECK_EQUAL(rb2.back(), 3);

    rb = rb1;
    BOOST_CHECK_EQUAL(rb.empty(), false);
    BOOST_CHECK_EQUAL(rb.full(), true);
    BOOST_CHECK_EQUAL(rb.size(), 3);
    BOOST_CHECK_EQUAL(rb.front(), 1);
    BOOST_CHECK_EQUAL(rb.back(), 3);
}

BOOST_AUTO_TEST_CASE( iterators_test )
{
    CircularBuffer<3, int> rb{1, 2, 3};
    BOOST_REQUIRE_EQUAL(*rb.begin(), 1);
    auto it = rb.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    ++it;
    BOOST_CHECK_EQUAL(*it, 2);
    ++it;
    BOOST_CHECK_EQUAL(*it, 3);
    ++it;
    if(it != rb.end()){
        BOOST_FAIL("it != rb1.end().");
    }

    it = rb.begin();
    BOOST_CHECK_EQUAL(*(it++), 1);
    BOOST_CHECK_EQUAL(*it, 2);

    auto it1 = rb.begin();
    auto it2 = rb.begin();
    if(it1 != it2){
        BOOST_FAIL("it1 != it2, where it1 == it2 == rb.begin().");
    }

}

BOOST_AUTO_TEST_CASE( container_modification_test )
{
    CircularBuffer<3, int> rb;

    rb.push_back(1); // 1
    BOOST_REQUIRE_EQUAL(rb.back(), 1);
    BOOST_REQUIRE_EQUAL(rb.front(), 1);
    BOOST_CHECK_EQUAL(rb.size(), 1);
    BOOST_CHECK_EQUAL(rb.empty(), false);
    BOOST_CHECK_EQUAL(rb.full(), false);

    rb.push_back(2); // 1 2
    BOOST_REQUIRE_EQUAL(rb.back(), 2);
    BOOST_REQUIRE_EQUAL(rb.front(), 1);
    BOOST_CHECK_EQUAL(rb.size(), 2);
    BOOST_CHECK_EQUAL(rb.empty(), false);
    BOOST_CHECK_EQUAL(rb.full(), false);

    rb.push_front(3); // 3 1 2
    BOOST_REQUIRE_EQUAL(rb.front(), 3);
    BOOST_CHECK_EQUAL(rb.size(), 3);
    BOOST_CHECK_EQUAL(rb.empty(), false);
    BOOST_CHECK_EQUAL(rb.full(), true);

    rb.push_back(4); // 1 2 4
    auto it = rb.begin();
    BOOST_REQUIRE_EQUAL(*it, 1);
    ++it;
    BOOST_REQUIRE_EQUAL(*it, 2);
    ++it;
    BOOST_REQUIRE_EQUAL(*it, 4);

    BOOST_REQUIRE_EQUAL(rb.pop_front(), 1);
    BOOST_REQUIRE_EQUAL(rb.front(), 2);
    BOOST_CHECK_EQUAL(rb.size(), 2);
    BOOST_CHECK_EQUAL(rb.full(), false);

    rb.clear();
    BOOST_CHECK_EQUAL(rb.size(), 0);
    BOOST_CHECK_EQUAL(rb.empty(), true);
    BOOST_CHECK_EQUAL(rb.full(), false);
}

BOOST_AUTO_TEST_CASE( element_access_test )
{
    CircularBuffer<3, int> rb{1, 2, 3};

    BOOST_REQUIRE_EQUAL(rb.front(), rb[0]);
    BOOST_REQUIRE_EQUAL(rb.back(), rb[2]);
    BOOST_REQUIRE_EQUAL(rb[1], 2);
}