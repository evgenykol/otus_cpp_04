#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::uint32_t ip_to_int(const std::vector<std::string> ip_str)
{
    std::uint32_t ip_int = 0;
    for(auto i = 0; i < 4; ++i)
    {
        ip_int += (std::stoi(ip_str.at(i)) & 0xFF) << 8*(3-i);
    }
    return ip_int;
}

std::string ip_to_str(const std::uint32_t ip_int)
{
    std::string ip_str = std::to_string((ip_int & 0xFF000000) >> 24);
    ip_str += "." + std::to_string((ip_int & 0xFF0000) >> 16);
    ip_str += "." + std::to_string((ip_int & 0xFF00) >> 8);
    ip_str += "." + std::to_string((ip_int & 0xFF));
    return ip_str;
}


