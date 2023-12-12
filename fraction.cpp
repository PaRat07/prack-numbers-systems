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
//    Reduce();
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

std::string Print(Fraction frac, uint8_t sys) {
    std::string ans;
    frac.SetSystem(sys);
    ans += to_string(frac.num() / frac.den());
    frac -= frac.num() / frac.den();
    if (frac == 0) {
        return ans;
    }

    std::string fract_part;
    std::map<Fraction, int> ind_to_frac;
    while (!ind_to_frac.contains(frac) && frac != 0) {
        ind_to_frac[frac] = fract_part.size();
        frac *= sys;
        uint8_t num = to_int(frac.num() / frac.den());
        if (num < 10) {
            fract_part.push_back('0' + num);
        } else if (num < 10 + 26) {
            fract_part.push_back('A' + (num - 10));
        } else {
            fract_part +='[' + to_string((int)num) + ']';
        }
        frac -= frac.num() / frac.den();
    }

    ans += '.';
    if (frac == 0) {
        ans += fract_part;
    } else {
        int to_print_brace = ind_to_frac[frac];
        for (int i = 0; i < fract_part.size(); ++i) {
            if (i == to_print_brace) {
                ans += '(';
            }
            ans += fract_part[i];
        }
        ans += ')';
    }
    return ans;
}


void AssertIsNumber(std::string s, uint8_t sys) {
    int max_num = 0;
    int cur_in_sq_braces = 0;
    bool now_sq_braces = false, was_something_in_braces = false;
    for (char sym : s) {
        if (sym == '[') {
            now_sq_braces = true;
            was_something_in_braces = false;
        } else if (sym == ']') {
            if (!now_sq_braces) {
                throw std::invalid_argument("] without [");
            } else if (!was_something_in_braces) {
                throw std::invalid_argument("Empty braces");
            }
            max_num = std::max(max_num, cur_in_sq_braces);
        } else if (sym >= 'A' && sym <= 'Z') {
            if (now_sq_braces) {
                throw std::invalid_argument("Letters mustn't be between [ and ]");
            }
            max_num = std::max(max_num, 10 + sym - 'A');
        } else if (sym >= '0' && sym <= '9') {
            if (now_sq_braces) {
                cur_in_sq_braces *= 10;
                cur_in_sq_braces += sym - '0';
                was_something_in_braces = true;
            }
            max_num = std::max(max_num, sym - '0');
            was_something_in_braces = true;
        } else if (sym == '.') {
            if (now_sq_braces) {
                throw std::invalid_argument("Square braces weren't closed before the point");
            }
        } else {
            throw std::invalid_argument("Unexpected character");
        }
    }
    if (max_num >= sys) {
        throw std::invalid_argument("A digit is bigger then base");
    } else if (now_sq_braces) {
        throw std::invalid_argument("[ without ]");
    }
}

void Fraction::Input(const std::string &num_s, uint8_t sys) {
    AssertIsNumber(num_s, sys);
    size_t ind = std::find(num_s.begin(), num_s.end(), '.') - num_s.begin();
    Fraction zel_part(uint132_t(num_s.substr(0, ind), sys),
                      uint132_t(1, sys));
    if (ind == num_s.size()) {
        *this = zel_part;
        return;
    }
    std::string fract_part_s = num_s.substr(ind + 1);
    std::string frac_part_s_without_period = fract_part_s.substr(0, fract_part_s.find_first_of('('));
    Fraction fract_part(uint132_t(frac_part_s_without_period, sys), 1);
    fract_part /= my_bin_pow(sys, frac_part_s_without_period.size());
    if (frac_part_s_without_period.size() != fract_part_s.size()) {
        std::string period_s = fract_part_s.substr(frac_part_s_without_period.size() + 1);
        period_s.pop_back();
        if (!period_s.empty()) {
            Fraction period(period_s);
            period /= my_bin_pow(sys, period_s.size()) - 1;
            period /= my_bin_pow(sys, fract_part_s.size() - 2 - period_s.size());
            *this = zel_part + fract_part + period;
            return;
        }
    }
    *this = zel_part + fract_part;
}

void Fraction::SetSystem(uint8_t sys) {
    num_.SetSystem(sys);
    den_.SetSystem(sys);
}

uint132_t gcd(uint132_t first_number, uint132_t second_number) {
    while (first_number != uint132_t(0, first_number.GetSystem())) {
        uint132_t buf = second_number % first_number;
        second_number = first_number;
        first_number = buf;
    }
    return second_number;
}
