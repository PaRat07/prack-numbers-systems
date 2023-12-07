#pragma once
#include "big_int.h"

#include "bits/stdc++.h"

uint132_t gcd(uint132_t first_number, uint132_t second_number);

class Fraction {
 public:
    Fraction() = default;
    Fraction(uint132_t num, uint132_t den);
    explicit Fraction(uint132_t num);
    Fraction(const Fraction& other) = default;
    ~Fraction() = default;

    uint132_t num() const { return num_; }
    uint132_t den() const { return den_; }

    /* your code here */
    Fraction operator+()const {
        return *this;
    }
    Fraction operator-()const;

    Fraction &operator++();
    Fraction operator++(int);
    Fraction &operator--();
    Fraction operator--(int);

    Fraction &operator+=(const Fraction &other);
    Fraction &operator+=(const uint132_t &other);
    Fraction &operator-=(const Fraction &other);
    Fraction &operator-=(const uint132_t &other);
    Fraction &operator*=(const Fraction &other);
    Fraction &operator*=(const uint132_t &other);
    Fraction &operator/=(const Fraction &other);
    Fraction &operator/=(const uint132_t &other);

    void Input(std::istream &in, uint8_t sys);
 private:
    bool is_less_0_ = false;
    uint132_t num_ = 0, den_ = 1;

    Fraction(bool is_less_0, uint132_t num, uint132_t den);
    void Reduce();
};

void Print(std::ostream &out, Fraction frac, uint8_t sys);
