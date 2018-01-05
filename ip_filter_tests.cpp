#include "ip_filter.h"

#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(split_suite)

BOOST_AUTO_TEST_CASE(check_split)
{
    // ("",  '.') -> [""]
    // ("11", '.') -> ["11"]
    // ("..", '.') -> ["", "", ""]
    // ("11.", '.') -> ["11", ""]
    // (".11", '.') -> ["", "11"]
    // ("11.22", '.') -> ["11", "22"]
    //std::vector<std::string> split(const std::string &str, char d)

    std::vector<std::string> v1 = split("",  '.');
    BOOST_CHECK(v1.size() == 1);
    BOOST_CHECK(v1.at(0) == "");

    std::vector<std::string> v2 = split("11",  '.');
    BOOST_CHECK(v2.size() == 1);
    BOOST_CHECK(v2.at(0) == "11");

    std::vector<std::string> v3 = split("..", '.');
    BOOST_CHECK(v3.size() == 3);
    BOOST_CHECK(v3.at(0) == "");
    BOOST_CHECK(v3.at(1) == "");
    BOOST_CHECK(v3.at(2) == "");

    std::vector<std::string> v4 = split("11.", '.');
    BOOST_CHECK(v4.size() == 2);
    BOOST_CHECK(v4.at(0) == "11");
    BOOST_CHECK(v4.at(1) == "");

    std::vector<std::string> v5 = split(".11", '.');
    BOOST_CHECK(v5.size() == 2);
    BOOST_CHECK(v5.at(0) == "");
    BOOST_CHECK(v5.at(1) == "11");

    std::vector<std::string> v6 = split("11.22", '.');
    BOOST_CHECK(v6.size() == 2);
    BOOST_CHECK(v6.at(0) == "11");
    BOOST_CHECK(v6.at(1) == "22");
}

BOOST_AUTO_TEST_CASE(check_ip_to_int)
{
//std::uint32_t ip_to_int(std::vector<std::string> &ip_str)

    std::vector<std::string> v1 = {"0", "0", "0", "0"};
    BOOST_CHECK(ip_to_int(v1) == 0x0);

    std::vector<std::string> v2 = {"255", "255", "255", "255"};
    BOOST_CHECK(ip_to_int(v2) == 0xffffffff);

    std::vector<std::string> v3 = {"1", "2", "3", "4"};
    BOOST_CHECK(ip_to_int(v3) == 0x01020304);

    std::vector<std::string> v4 = {"222", "173", "235", "246"};
    BOOST_CHECK(ip_to_int(v4) == 0xdeadebf6);

}

BOOST_AUTO_TEST_CASE(check_ip_to_str)
{
    //std::string ip_to_str(std::uint32_t ip_int)
    BOOST_CHECK(ip_to_str(0x0) == "0.0.0.0");
    BOOST_CHECK(ip_to_str(0xFFFFFFFF) == "255.255.255.255");
    BOOST_CHECK(ip_to_str(0x01020304) == "1.2.3.4");
    BOOST_CHECK(ip_to_str(0xdeadebf6) == "222.173.235.246");
}

BOOST_AUTO_TEST_CASE(check_filter_one)
{
    std::vector<std::uint32_t> v1 =
    {
        0x0,
        0x1,
        0x01000000,
        0x02000000,
        0x01abcdef
    };

    auto r = filter(v1, 1);

    BOOST_CHECK(r.size() == 2);
    BOOST_CHECK(r.at(0) == 0x01000000);
    BOOST_CHECK(r.at(1) == 0x01abcdef);
}

BOOST_AUTO_TEST_CASE(check_filter_two)
{
    std::vector<std::uint32_t> v1 =
    {
        0x0,
        0x1,
        0x01000000,
        0x02000000,
        0x01abcdef
    };

    auto r = filter(v1, 1, 0);

    BOOST_CHECK(r.size() == 1);
    BOOST_CHECK(r.at(0) == 0x01000000);
}

BOOST_AUTO_TEST_CASE(check_filter_any)
{
    std::vector<std::uint32_t> v1 =
    {
        0x0,
        0x1,
        0x01000000,
        0x02000000,
        0x01abcdef
    };

    auto r = filter_any(v1, 1);

    BOOST_CHECK(r.size() == 3);
    BOOST_CHECK(r.at(0) == 0x1);
    BOOST_CHECK(r.at(1) == 0x01000000);
    BOOST_CHECK(r.at(2) == 0x01abcdef);
}

BOOST_AUTO_TEST_SUITE_END()
