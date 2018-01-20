/**
 * \file   ip_filter.h
 * \author evgenyko
 * \date   2018
 * \brief  ip_filter.h for OTUS C++ homework #4
 *
 * \details Contains templates for IP printing
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
template <class T, typename std::enable_if<std::is_integral<T>::value, T>::type = 0>
void print_ip(const T& ip)
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
 * \brief Prints IP address from string
 * \details IP prints depending from string without modifications
 * \param [in] ip String IP address
 */
void print_ip(const std::string& ip)
{
    std::cout << ip << std::endl;
}

template<class T> struct is_container : public std::false_type {};

template<class T, class Alloc>
struct is_container<std::vector<T, Alloc>> : public std::true_type {};

template<class T, class Alloc>
struct is_container<std::list<T, Alloc>> : public std::true_type {};

/**
 * \brief Prints IP address from container
 * \details Each element of container represents single byte. Container elements must be integral
 * \param [in] ip Container with IP address
 */
template <class T, typename std::enable_if<is_container<T>::value, typename T::value_type>::type = 0>
void print_ip(const T& ip)
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
 * \brief Prints IP address from tuple. Partitial specialization template
 * \param [in] t Tuple with IP address
 */
template<typename Tuple, typename ElType, std::size_t N>
struct TuplePrinter
{

    static void print_ip(const Tuple& t)
    {
        static_assert(std::is_same<ElType, decltype(std::get<N-1>(t))>::value, "Tuple elements of same type requested!");
        TuplePrinter<Tuple, decltype(std::get<N-1>(t)), N-1>::print_ip(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

/**
 * \brief Prints IP address from tuple. Partitial specialization template
 * \param [in] t Tuple with IP address
 */
template<typename Tuple, typename ElType>
struct TuplePrinter<Tuple, ElType, 1>
{
    static void print_ip(const Tuple& t)
    {
        static_assert(std::is_same<ElType, decltype(std::get<0>(t))>::value, "Tuple elements of same type requested!");
        std::cout << std::get<0>(t);
    }
};

/**
 * \brief Prints IP address from tuple
 * \details Each element of tuple represents single byte. All tuple elements must have the same type
 *
 * \param [in] t Tuple with IP address
 */
template<typename... Args>
void print_ip(const std::tuple<Args...>& t)
{
    //static_assert(all_same<Args...>, "fuck");

    TuplePrinter<decltype(t), decltype(std::get<sizeof...(Args)-1>(t)), sizeof...(Args)>::print_ip(t);
    std::cout << std::endl;
}
