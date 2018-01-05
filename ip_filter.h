#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <array>

std::vector<std::string> split(const std::string &str, char d);
std::uint32_t ip_to_int(const std::vector<std::string> ip_str);
std::string ip_to_str(const std::uint32_t ip_int);

template <typename T, typename... Args>
std::vector<std::uint32_t> filter(std::vector<std::uint32_t> v, T firstArg, Args... args)
{
    std::array<T, sizeof... (args)+1> byteVal {firstArg, args...};

    auto f = [&byteVal](std::uint32_t ip)
    {
        for(size_t i = 0; i < byteVal.size(); ++i)
        {
            if(((ip >> 8*(3-i)) & 0xFF) != byteVal[i])
            {
                return false;
            }
        }
        return true;
    };

    std::vector<std::uint32_t> out;
    copy_if(v.begin(), v.end(), std::back_inserter(out), f);
    return out;
}

template <typename T>
std::vector<std::uint32_t> filter_any(std::vector<std::uint32_t> v, T byteVal)
{
    auto f = [byteVal](std::uint32_t ip)
    {
        for(size_t i = 0; i < 4; ++i)
        {
            if(((ip >> 8*(3-i)) & 0xFF) == byteVal)
            {
                return true;
            }
        }
        return false;
    };

    std::vector<std::uint32_t> out;
    copy_if(v.begin(), v.end(), std::back_inserter(out), f);
    return out;
}

