#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>


class uint132_t {
 public:
    uint132_t(uint64_t val = 0, uint8_t sys = 10);
    uint132_t(std::string s, uint8_t sys = 10);

    uint8_t GetSystem() const {
        return system_;
    }

    void SetSystem(uint8_t new_sys);

    uint132_t operator+(const uint132_t &other) const;

    uint132_t operator-(const uint132_t &other) const;

    uint132_t operator*(uint132_t other) const;

    uint132_t operator/(const uint132_t &other) const;

    uint132_t operator%(const uint132_t &other) const;

    uint132_t operator>>(size_t shift) const;

    uint132_t operator<<(size_t shift) const;

    uint132_t &operator+=(const uint132_t &other);

    uint132_t &operator-=(uint132_t other);

    uint132_t &operator*=(uint132_t other);

    uint132_t &operator/=(uint132_t other);

    uint132_t &operator<<=(size_t shift);

    uint132_t &operator>>=(size_t shift);

    uint132_t &operator%=(const uint132_t &mod);

    friend bool operator<(const uint132_t &lhs, const uint132_t &rhs);
    friend std::string to_string(const uint132_t &num);
    friend uint64_t to_int(uint132_t num);
 private:
    template<typename It>
    uint132_t(It beg, It end, uint8_t sys)
        : data_(std::make_reverse_iterator(end), std::make_reverse_iterator(beg))
        , system_(sys)
    {
    }

    void Reduce();

    static uint132_t StupidMul(uint132_t a, uint132_t b);
    static uint132_t KarazubaMul(uint132_t l, uint132_t r);
    static uint132_t StupidDiv(uint132_t a, uint8_t b);

    std::vector<uint8_t> data_;
    uint8_t system_;
};


bool operator<(const uint132_t &lhs, const uint132_t &rhs);

bool operator>(const uint132_t &lhs, const uint132_t &rhs);

bool operator<=(const uint132_t &lhs, const uint132_t &rhs);

bool operator>=(const uint132_t &lhs, const uint132_t &rhs);

bool operator==(const uint132_t &lhs, const uint132_t &rhs);

bool operator!=(const uint132_t &lhs, const uint132_t &rhs);

uint132_t my_bin_pow(uint132_t num, uint132_t pow);

std::string to_string(const uint132_t &num);
