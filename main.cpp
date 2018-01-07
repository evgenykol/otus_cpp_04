/**
 * \file   main.cpp
 * \author evgenyko
 * \date   2018
 * \brief  main.cpp for OTUS C++ homework #4
 *
 */
#include <cstdlib>
#include <iostream>

#include "version.h"
#include "ip_filter.h"

/**
 * \brief Main function
 * \param [in] argc Input arguments count
 * \param [in] argv Input arguments value
 * \returns Return code
 */

int main(int argc, char const *argv[])
{
    if ((argc > 1) &&
       (!strncmp(argv[1], "-v", 2) || !strncmp(argv[1], "--version", 9)))
    {
        std::cout << "version " << version() << std::endl;
        return 0;
    }

    try
    {
        std::int8_t i1 = 0x1;
        std::int16_t i2 = 0x0102;
        std::int32_t i3 = 0x01020304;
        std::int64_t i4 = 0x0102030405060708;

        print_ips_int(i1);
        print_ips_int(i2);
        print_ips_int(i3);
        print_ips_int(i4);

        std::vector<int> v = {1,2,3,4,5,6,7,8,9};
        print_ips_container(v);

        std::list<int> l = {1,2,3,4,5,6,7,8,9};
        print_ips_container(l);

        auto t = std::make_tuple(1,2,3,4);
        print_ips_tuple(t);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
