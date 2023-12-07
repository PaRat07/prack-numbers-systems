#include "fraction.h"

Fraction::Fraction(uint132_t num)
        : num_(std::move(num))
        , den_(uint132_t(1, num_.GetSystem()))
{}

Fraction::Fraction(uint132_t num, uint132_t den)
        : num_(num)
        , den_(den)
{
    if (num_.GetSystem() != den_.GetSystem()) {
        den_.SetSystem(num_.GetSystem());
    }
    if (den_ == 0) {
        throw std::logic_error("Denominator can't be equal to zero");
    }
    Reduce();
}

Fraction Fraction::operator-() const {
    return { !is_less_0_, num_, den_ };
}

Fraction &Fraction::operator++() {
    num_ += den_;
    return *this;
}

Fraction Fraction::operator++(int) {
    auto buf = *this;
    num_ += den_;
    return buf;
}

Fraction &Fraction::operator--() {
    num_ -= den_;
    return *this;
}

Fraction Fraction::operator--(int) {
    auto buf = *this;
    num_ -= den_;
    return buf;
}

Fraction::Fraction(bool is_less_0, uint132_t num, uint132_t den)
        : is_less_0_(is_less_0)
        , num_(std::move(num))
        , den_(std::move(den))
{}

void Fraction::Reduce() {
    uint132_t gcd_res = gcd(num_, den_);
    num_ /= gcd_res;
    den_ /= gcd_res;
}

bool operator<(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num() * rhs.den() < rhs.num() * lhs.den();
}

bool operator>(const Fraction &lhs, const Fraction &rhs) {
    return rhs < lhs;
}

bool operator<=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs < rhs);
}

bool operator<(const Fraction &lhs, const uint132_t &rhs) {
    return lhs.num() < rhs * lhs.den();
}

bool operator>=(const Fraction &lhs, const uint132_t &rhs) {
    return !(lhs < rhs);
}

bool operator<(const uint132_t &lhs, const Fraction &rhs) {
    return lhs * rhs.den() < rhs.num();
}

bool operator>(const uint132_t &lhs, const Fraction &rhs) {
    return rhs < lhs;
}

bool operator<=(const uint132_t &lhs, const Fraction &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const uint132_t &lhs, const Fraction &rhs) {
    return !(lhs < rhs);
}

bool operator>(const Fraction &lhs, const uint132_t &rhs) {
    return rhs < lhs;
}

bool operator<=(const Fraction &lhs, const uint132_t &rhs) {
    return !(lhs > rhs);
}

bool operator==(const Fraction &lhs, const Fraction &rhs)  {
    return lhs.num() * rhs.den() == rhs.num() * lhs.den();
}

bool operator!=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs == rhs);
}

bool operator==(const Fraction &lhs, const uint132_t &rhs) {
    return lhs.num() == rhs * lhs.den();
}

bool operator==(const uint132_t &lhs, const Fraction &rhs) {
    return lhs * rhs.den() == rhs.num();
}

bool operator!=(const uint132_t &lhs, const Fraction &rhs)  {
    return !(lhs == rhs);
}

bool operator!=(const Fraction &lhs, const uint132_t &rhs)  {
    return !(lhs == rhs);
}

Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
    return { lhs.num() * rhs.den() + rhs.num() * lhs.den(), lhs.den() * rhs.den() };
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
    return { lhs.num() * rhs.den() - rhs.num() * lhs.den(), lhs.den() * rhs.den() };
}

Fraction operator+(const Fraction &lhs, const uint132_t &rhs) {
    return { lhs.num() + rhs * lhs.den(), lhs.den() };
}

Fraction operator+(const uint132_t &lhs, const Fraction &rhs) {
    return { lhs * rhs.den() + rhs.num(), rhs.den() };
}

Fraction operator-(const Fraction &lhs, const uint132_t &rhs) {
    return { lhs.num() - rhs * lhs.den(), lhs.den() };
}

Fraction operator-(const uint132_t &lhs, const Fraction &rhs) {
    return { lhs * rhs.den() - rhs.num(), rhs.den() };
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
    return { lhs.num() * rhs.num(), lhs.den() * rhs.den() };
}

Fraction operator*(const uint132_t &lhs, const Fraction &rhs) {
    return { lhs * rhs.num(), rhs.den() };
}

Fraction operator*(const Fraction &lhs, const uint132_t &rhs) {
    return { lhs.num() * rhs, lhs.den() };
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
    return { lhs.num() * rhs.den(), lhs.den() * rhs.num() };
}

Fraction operator/(const uint132_t &lhs, const Fraction &rhs) {
    return { lhs * rhs.den(), rhs.num() };
}

Fraction operator/(const Fraction &lhs, const uint132_t &rhs) {
    return { lhs.num(), lhs.den() * rhs };
}

Fraction &Fraction::operator+=(const Fraction &other) {
    *this = *this + other;
    return *this;
}

Fraction &Fraction::operator+=(const uint132_t &other) {
    *this = *this + other;
    return *this;
}

Fraction &Fraction::operator-=(const Fraction &other) {
    *this = *this - other;
    return *this;
}

Fraction &Fraction::operator-=(const uint132_t &other) {
    *this = *this - other;
    return *this;
}

Fraction &Fraction::operator*=(const Fraction &other) {
    *this = *this * other;
    return *this;
}

Fraction &Fraction::operator*=(const uint132_t &other) {
    *this = *this * other;
    return *this;
}

Fraction &Fraction::operator/=(const Fraction &other) {
    *this = *this / other;
    return *this;
}

Fraction &Fraction::operator/=(const uint132_t &other) {
    *this = *this / other;
    return *this;
}

void Print(std::ostream &out, Fraction frac, uint8_t sys) {
    out << to_string(frac.num() / frac.den());
    frac -= frac.num() / frac.den();
    if (frac == 0) {
        return;
    }

    std::string fract_part;
    std::map<Fraction, int> ind_to_frac;
    while (!ind_to_frac.contains(frac) && frac != 0) {
        ind_to_frac[frac] = fract_part.size();
        frac *= sys;
        fract_part += to_string(frac.num() / frac.den());
        frac -= frac.num() / frac.den();
    }

    out << '.';
    if (frac == 0) {
        out << fract_part;
    } else {
        int to_print_brace = ind_to_frac[frac];
        for (int i = 0; i < fract_part.size(); ++i) {
            if (i == to_print_brace) {
                out << '(' << std::flush;
            }
            out << fract_part[i] << std::flush;
        }
        out << ')' << std::flush;
    }
}

void Fraction::Input(std::istream &in, uint8_t sys) {
    std::string num_s;
    in >> num_s;
    size_t ind = std::find(num_s.begin(), num_s.end(), '.') - num_s.begin();
    Fraction zel_part(uint132_t(num_s.substr(0, ind), sys),
                      uint132_t(1, sys));
    if (ind == num_s.size()) {
        *this = zel_part;
        return;
    }
    std::string fract_part_s = num_s.substr(ind + 1);
    ind = 0;
    Fraction fract_part;
    while (ind < fract_part_s.size() && fract_part_s[ind] != '(') {
        if (fract_part_s[ind] == '[') {
            throw std::runtime_error("not works yet");
        } else if (fract_part_s[ind] >= 'A' && fract_part_s[ind] <= 'Z') {
            fract_part *= sys;
            fract_part += fract_part_s[ind] + 10 - 'A';
        } else {
            fract_part *= sys;
            fract_part += fract_part_s[ind] - '0';
        }
        ++ind;
    }
    fract_part /= my_bin_pow(sys, ind);
    if (ind < fract_part_s.size()) {
        std::string period_s = fract_part_s.substr(ind + 1);
        if (!period_s.empty()) {
            period_s.pop_back();
            Fraction period;
            ind = 0;
            while (ind < period_s.size()) {
                if (period_s[ind] == '[') {
                    throw std::runtime_error("not works yet");
                } else if (period_s[ind] >= 'A' && period_s[ind] <= 'Z') {
                    period *= sys;
                    period += period_s[ind] + 10 - 'A';
                } else {
                    period *= uint132_t(sys, sys);
                    period += uint132_t(period_s[ind] - '0', sys);
                }
                ++ind;
            }
            period /= my_bin_pow(sys, period_s.size()) - 1;
            period /= my_bin_pow(sys, fract_part_s.size() - 2 - period_s.size());
            *this = zel_part + fract_part + period;
            return;
        }
    }
    *this = zel_part + fract_part;
}

uint132_t gcd(uint132_t first_number, uint132_t second_number) {
    while (first_number != uint132_t(0, first_number.GetSystem())) {
        uint132_t buf = second_number % first_number;
        second_number = first_number;
        first_number = buf;
    }
    return second_number;
}
