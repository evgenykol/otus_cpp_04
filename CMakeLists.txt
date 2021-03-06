cmake_minimum_required(VERSION 3.2)

project(ip_print VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(ip_print main.cpp)

add_library(ip_filter_lib ip_filter.h ip_filter.cpp)

add_executable(ip_filter_tests ip_filter_tests.cpp)

set_target_properties(ip_print ip_filter_lib ip_filter_tests
        PROPERTIES
                CXX_STANDARD 14
                CXX_STANDARD_REQUIRED ON
                CMAKE_CXX_EXTENSIONS OFF
                COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(ip_filter_tests
        PROPERTIES
                COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
                INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_print
        ip_filter_lib
)

target_link_libraries(ip_filter_tests
        ${Boost_LIBRARIES}
        ip_filter_lib
)

install(TARGETS ip_print RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT edkolotilov@gmail.com)

include (CPack)

enable_testing()

add_test(check_print_ips_int ip_filter_tests)
add_test(check_print_ips_uint ip_filter_tests)
add_test(check_print_ips_string ip_filter_tests)
add_test(check_print_ips_container_vector ip_filter_tests)
add_test(check_print_ips_container_list ip_filter_tests)
add_test(check_print_ips_tuple ip_filter_tests)
