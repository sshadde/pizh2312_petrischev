#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "range_adapters.h"

int main() {
    using namespace ra;

    std::vector<int> v = {1,2,3,4,5,6};
    std::cout << "Squares of odd numbers: ";
    for (int x : v | filter([](int i){ return i % 2; })
                    | transform([](int i){ return i * i; })) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "First 3 elements: ";
    for (int x : v | take(3)) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "After dropping 2 elements: ";
    for (int x : v | drop(2)) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "Reversed vector: ";
    for (int x : reverse(v)) std::cout << x << " ";
    std::cout << std::endl;

    std::map<std::string, int> m = {{"a",10}, {"b",20}, {"c",30}};
    std::cout << "Map keys: ";
    for (const auto& k : keys(m)) std::cout << k << " ";
    std::cout << std::endl;

    std::cout << "Map values: ";
    for (auto v : values(m)) std::cout << v << " ";
    std::cout << std::endl;

    std::list<int> lst = {1,2,3,4,5,6};
    std::cout << "Pipeline example: ";
    for (int x : lst
        | filter([](int i){ return i % 2; })
        | transform([](int i){ return i * i; })
        | take(2)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

