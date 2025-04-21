#include "number.h"
#include <cstring>
#include <algorithm>

uint2022_t from_uint(uint32_t i) {
    uint2022_t r;
    r.data[0] = i;

    return r;
}

uint2022_t from_string(const char* buff) {
    uint2022_t r;
    for (int pos = 0; buff[pos]; ++pos) {
        uint64_t carry = 0;

        for (int i = 0; i < uint2022_t::SIZE; ++i) {
            uint64_t t = (uint64_t)r.data[i] * 10 + carry;
            r.data[i] = uint32_t(t);
            carry = t >> 32;
        }

        uint32_t d = buff[pos] - '0';
        carry = d;

        for (int i = 0; i < uint2022_t::SIZE && carry; ++i) {
            uint64_t t = (uint64_t)r.data[i] + carry;
            r.data[i] = uint32_t(t);
            carry = t >> 32;
        }
    }

    return r;
}
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    return false;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    stream << "Implement me";

    return stream;
}
