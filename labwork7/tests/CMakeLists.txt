find_package(GTest REQUIRED)

add_executable(ID3ParserTests
    ID3ParserTests.cpp
)

target_include_directories(ID3ParserTests PUBLIC
    ${PROJECT_SOURCE_DIR}/lib
)

target_link_libraries(ID3ParserTests PRIVATE
    id3parser
    GTest::gtest
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(ID3ParserTests)

