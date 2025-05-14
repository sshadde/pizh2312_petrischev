find_package(GTest REQUIRED)

add_executable(test_adapters test_adapters.cpp)
target_link_libraries(test_adapters PRIVATE GTest::gtest_main range_adapters)

include(GoogleTest)
gtest_discover_tests(test_adapters)

