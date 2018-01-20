/**
 * \file   main.cpp
 * \author evgenyko
 * \date   2018
 * \brief  main.cpp for OTUS C++ homework #4
 *
 */
#include <cstdlib>
#include <cstring>
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
        print_ip(char(-1));
        print_ip(short(0));
        print_ip(int(2130706433));
        print_ip(long(8875824491850138409));

        print_ip("74.114.88.139");

        print_ip(std::vector<int>{80, 87, 192, 10});
        print_ip(std::list<int>{81, 19, 82, 9});

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
