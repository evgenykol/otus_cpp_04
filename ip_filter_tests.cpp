/**
 * \file   ip_filter_tests.cpp
 * \author evgenyko
 * \date   2018
 * \brief  ip_filter_tests.cpp for OTUS C++ homework #4
 *
 * \details * Contains tests for IP printing functions
 */

#include "ip_filter.h"

#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_SUITE(ip_print_suite)

struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer )
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

private:
    std::streambuf * old;
};

BOOST_AUTO_TEST_CASE(check_print_ips_int)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );

        print_ip(char(-1));
        print_ip(short(0));
        print_ip(int(2130706433));
        print_ip(long(8875824491850138409));
    }
    BOOST_CHECK(output.is_equal("255\n0.0\n127.0.0.1\n123.45.67.89.101.112.131.41\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_uint)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );

        print_ip(std::uint8_t(-1));
        print_ip(std::uint16_t(0));
        print_ip(std::uint32_t(2130706433));
        print_ip(std::uint64_t(8875824491850138409));
    }
    BOOST_CHECK(output.is_equal("255\n0.0\n127.0.0.1\n123.45.67.89.101.112.131.41\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_string)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );

        print_ip("74.114.88.139");
    }
    BOOST_CHECK(output.is_equal("74.114.88.139\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_container_vector)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        print_ip(std::vector<int>{80, 87, 192, 10});
    }
    BOOST_CHECK(output.is_equal("80.87.192.10\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_container_list)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        print_ip(std::list<int>{81, 19, 82, 9});
    }
    BOOST_CHECK(output.is_equal("81.19.82.9\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_tuple)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );

        print_ip(std::make_tuple(77,88,55,77));
        print_ip(std::make_tuple("192","30","253","112"));
    }
    BOOST_CHECK(output.is_equal("77.88.55.77\n192.30.253.112\n"));
}

BOOST_AUTO_TEST_SUITE_END()
