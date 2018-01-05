#pragma once
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>

template <typename T>
void print_ips_int(const T& ip)
{
    static_assert(std::is_integral<T>::value, "Integral type required!");
    auto bytes_cnt = sizeof(T);

    for(size_t i = bytes_cnt; i > 0; --i)
    {
        std::uint8_t byte = ((ip >> (8*(i-1))) & 0xFF);
        if(i != bytes_cnt)
        {
            std::cout << ".";
        }
        std::cout << std::to_string(byte);
    }
    std::cout << std::endl;
}

template <typename T>
void print_ips_container(const T& ip)
{
    static_assert(std::is_integral<typename T::value_type>::value, "Integral type required!");
    bool not_first = false;

    for(auto ipp : ip)
    {
        if(not_first)
        {
            std::cout << ".";
        }
        std::cout << std::to_string(ipp);
        not_first = true;
    }
    std::cout << std::endl;
}


//void print_ips_tuple()
//{
//}

//template <typename T>
//void print_ips_tuple(T t)
//{
//    static_assert(std::is_integral<T>::value, "Integral type required!");
//    std::cout << t;

//}

//template <typename T, typename... Args>
//void print_ips_tuple(T t, Args... args)
//{
//    static_assert(std::is_integral<T>::value, "Integral type required!");
//    std::cout << t << ".";
//    print_ips_tuple(args...);

//}


template<typename Tuple, std::size_t N>
struct TuplePrinter
{
    static void print_ips_tuple(const Tuple& t)
    {
        //static_assert(std::is_integral<typename std::get<N-1>(t)::value_type>::value, "Integral type of tuple element required!");
        TuplePrinter<Tuple, N-1>::print_ips_tuple(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print_ips_tuple(const Tuple& t)
    {
        //static_assert(std::is_integral<std::get<0>(t)>::value, "Integral type of tuple element required!");
        std::cout << std::to_string(std::get<0>(t));
    }
};

template<typename... Args>
void print_ips_tuple(const std::tuple<Args...>& t)
{
    TuplePrinter<decltype(t), sizeof...(Args)>::print_ips_tuple(t);
    std::cout << std::endl;
}


template <typename... Args>
void iterate(Args... args)
{
    std::cout << sizeof...(args) << std::endl;
    int a[sizeof...(args)] = {(std::cout << args << ".", 0)...};

    std::cout << std::endl;
}




