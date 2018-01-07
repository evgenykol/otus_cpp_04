/**
 * \file   ip_filter.h
 * \author evgenyko
 * \date   2018
 * \brief  ip_filter.h for OTUS C++ homework #4
 *
 * \details * Contains templates for IP printing
 */


#pragma once
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>

/**
 * \brief Prints IP address from intgral typed variable
 * \details IP prints depending on variable's size (e.g. short->"X.X", int->"X.X.X.X")
 * \param [in] ip Integral typed IP address
 */
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

/**
 * \brief Prints IP address from container
 * \details Each element of container represents single byte. Container elements must be integral
 * \param [in] ip Container with IP address
 */
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


/**
 * \brief Prints IP address from tupe. Partitial specialization template
 * \param [in] t Tuple with IP address
 */
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

/**
 * \brief Prints IP address from tupe. Partitial specialization template
 * \param [in] t Tuple with IP address
 */
template<typename Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print_ips_tuple(const Tuple& t)
    {
        //static_assert(std::is_integral<std::get<0>(t)>::value, "Integral type of tuple element required!");
        std::cout << std::to_string(std::get<0>(t));
    }
};

/**
 * \brief Prints IP address from tupe
 * \details Each element of tuple represents single byte. All tuple elements must have the same type
 *
 * \param [in] t Tuple with IP address
 */
template<typename... Args>
void print_ips_tuple(const std::tuple<Args...>& t)
{
    TuplePrinter<decltype(t), sizeof...(Args)>::print_ips_tuple(t);
    std::cout << std::endl;
}

