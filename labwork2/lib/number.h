#pragma once
#include <cinttypes>
#include <iostream>

struct uint2022_t {
    static const int SIZE = 64;        // 64×32 = 2048 бит
    uint32_t data[SIZE];               // младшее слово — data[0]

    // конструктор по умолчанию
    uint2022_t() {
        for (int i = 0; i < SIZE; ++i)
            data[i] = 0;
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);
uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);
bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);
bool operator<(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
