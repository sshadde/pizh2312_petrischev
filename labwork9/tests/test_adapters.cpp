#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <list>
#include "range_adapters.h"

using namespace ra;

TEST(FilterTest, OddNumbers) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 3, 5};
    std::vector<int> result;

    for (int i : v | filter([](int x) { return x % 2; })) {
        result.push_back(i);
    }

    EXPECT_EQ(result, expected);
}

TEST(TransformTest, Square) {
    std::vector<int> v = {1, 2, 3};
    std::vector<int> expected = {1, 4, 9};
    std::vector<int> result;

    for (int i : v | transform([](int x) { return x * x; })) {
        result.push_back(i);
    }

    EXPECT_EQ(result, expected);
}

TEST(TakeTest, FirstN) {
    std::vector<int> v = {10, 20, 30, 40, 50};
    std::vector<int> expected = {10, 20, 30};
    std::vector<int> result;

    for (int i : v | take(3)) {
        result.push_back(i);
    }

    EXPECT_EQ(result, expected);
}

TEST(DropTest, SkipN) {
    std::vector<int> v = {5, 6, 7, 8, 9};
    std::vector<int> expected = {7, 8, 9};
    std::vector<int> result;

    for (int i : v | drop(2)) {
        result.push_back(i);
    }

    EXPECT_EQ(result, expected);
}

TEST(ReverseTest, ReverseVector) {
    std::vector<char> v = {'a', 'b', 'c', 'd'};
    std::vector<char> expected = {'d', 'c', 'b', 'a'};
    std::vector<char> result;

    for (char c : reverse(v)) {
        result.push_back(c);
    }

    EXPECT_EQ(result, expected);
}

TEST(KeysTest, MapKeys) {
    std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::vector<std::string> expected = {"one", "three", "two"};
    std::vector<std::string> result;

    for (const auto& key : keys(m)) {
        result.push_back(key);
    }

    EXPECT_EQ(result, expected);
}

TEST(ValuesTest, MapValues) {
    std::map<std::string, int> m = {{"a", 10}, {"b", 20}, {"c", 30}};
    std::vector<int> expected = {10, 20, 30};
    std::vector<int> result;

    for (int val : values(m)) {
        result.push_back(val);
    }

    EXPECT_EQ(result, expected);
}

TEST(PipelineTest, CombinedAdapters) {
    std::list<int> lst = {1, 2, 3, 4, 5, 6};
    std::vector<int> expected = {1, 9};
    std::vector<int> result;

    for (int i : lst |
             filter([](int x){ return x % 2; }) |
             transform([](int x){ return x * x; }) |
             take(2)) {
        result.push_back(i);
    }

    EXPECT_EQ(result, expected);
}

