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
        std::int8_t i1 = 0x1;
        std::int16_t i2 = 0x0102;
        std::int32_t i3 = 0x01020304;
        std::int64_t i4 = 0x0102030405060708;

        print_ips_int(i1);
        print_ips_int(i2);
        print_ips_int(i3);
        print_ips_int(i4);
    }
    BOOST_CHECK(output.is_equal("1\n1.2\n1.2.3.4\n1.2.3.4.5.6.7.8\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_uint)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        std::uint8_t i1 = 0x1;
        std::uint16_t i2 = 0x0102;
        std::uint32_t i3 = 0x01020304;
        std::uint64_t i4 = 0x0102030405060708;

        print_ips_int(i1);
        print_ips_int(i2);
        print_ips_int(i3);
        print_ips_int(i4);
    }
    BOOST_CHECK(output.is_equal("1\n1.2\n1.2.3.4\n1.2.3.4.5.6.7.8\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_container_vector)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        std::vector<int> v = {1,2,3,4,5,6,7,8,9};
        print_ips_container(v);
    }
    BOOST_CHECK(output.is_equal("1.2.3.4.5.6.7.8.9\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_container_list)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        std::list<int> l = {1,2,3,4,5,6,7,8,9};
        print_ips_container(l);
    }
    BOOST_CHECK(output.is_equal("1.2.3.4.5.6.7.8.9\n"));
}

BOOST_AUTO_TEST_CASE(check_print_ips_tuple)
{
    output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
        auto t = std::make_tuple(1,2,3,4);
        print_ips_tuple(t);
    }
    BOOST_CHECK(output.is_equal("1.2.3.4\n"));
}

BOOST_AUTO_TEST_SUITE_END()
