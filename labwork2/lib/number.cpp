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

uint2022_t operator+(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t r;
    uint64_t carry = 0;

    for (int i = 0; i < uint2022_t::SIZE; ++i) {
        uint64_t t = (uint64_t)a.data[i] + b.data[i] + carry;
        r.data[i] = uint32_t(t);
        carry = t >> 32;
    }

    return r;
}

uint2022_t operator-(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t r;
    int64_t borrow = 0;

    for (int i = 0; i < uint2022_t::SIZE; ++i) {
        int64_t t = (int64_t)a.data[i] - b.data[i] - borrow;

        if (t < 0) {
            t += (1LL << 32);
            borrow = 1;
        } else {
            borrow = 0;
        }
        r.data[i] = uint32_t(t);
    }

    return r;
}

uint2022_t operator*(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t r;
    for (int i = 0; i < uint2022_t::SIZE; ++i) {
        uint64_t carry = 0;

        for (int j = 0; j + i < uint2022_t::SIZE; ++j) {
            uint64_t t = (uint64_t)a.data[i] * b.data[j] + r.data[i + j] + carry;
            r.data[i + j] = uint32_t(t);
            carry = t >> 32;
        }
    }

    return r;
}

uint2022_t operator/(const uint2022_t& a, const uint2022_t& b) {
    uint2022_t zero;
    uint2022_t one = from_uint(1);
    uint2022_t dividend = a;
    uint2022_t divisor = b;
    uint2022_t q;

    if (divisor == zero) return q;

    while (!(dividend < divisor)) {
        dividend = dividend - divisor;
        q = q + one;
    }

    return q;
}

bool operator==(const uint2022_t& a, const uint2022_t& b) {
    for (int i = 0; i < uint2022_t::SIZE; ++i)
        if (a.data[i] != b.data[i]) return false;

    return true;
}

bool operator!=(const uint2022_t& a, const uint2022_t& b) {
    return !(a == b);
}

bool operator<(const uint2022_t& a, const uint2022_t& b) {
    for (int i = uint2022_t::SIZE - 1; i >= 0; --i) {
        if (a.data[i] < b.data[i]) return true;
        if (a.data[i] > b.data[i]) return false;
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    uint2022_t temp = value;
    uint2022_t zero;
    std::string s;

    while (temp != zero) {
        uint64_t rem = 0;
        for (int i = uint2022_t::SIZE - 1; i >= 0; --i) {
            uint64_t cur = (rem << 32) | temp.data[i];
            temp.data[i] = uint32_t(cur / 10);
            rem = cur % 10;
        }
        s.push_back(char('0' + rem));
    }

    if (s.empty()) s = "0";
    std::reverse(s.begin(), s.end());
    stream << s;

    return stream;
}
