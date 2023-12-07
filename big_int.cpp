#include "big_int.h"


uint132_t::uint132_t(uint64_t val, uint8_t sys)
        : data_(10, 0)
        , system_(sys)
{
    int32_t ind = 0;
    while (val) {
        if (ind >= data_.size()) {
            data_.resize(ind + 1, 0);
        }
        data_[ind++] = val % system_;
        val /= system_;
    }
}

void uint132_t::SetSystem(uint8_t new_sys) {
    uint132_t new_num(0, new_sys);
    for (int i = data_.size() - 1; i >= 0; --i) {
        new_num *= uint132_t(system_, new_sys);
        new_num += uint132_t(data_[i], new_sys);
    }
    *this = std::move(new_num);
}

uint132_t uint132_t::operator+(const uint132_t &other) const {
    uint132_t ans = *this;
    ans += other;
    return ans;
}

uint132_t uint132_t::operator-(const uint132_t &other) const {
    uint132_t ans = *this;
    ans -= other;
    return ans;
}

uint132_t uint132_t::operator*(uint132_t other) const {
    other *= *this;
    return other;
}

uint132_t uint132_t::operator/(const uint132_t &other) const {
    uint132_t ans = *this;
    ans /= other;
    return ans;
}

uint132_t uint132_t::operator%(const uint132_t &other) const {
    uint132_t ans = *this;
    ans %= other;
    return ans;
}

uint132_t uint132_t::operator>>(size_t shift) const {
    uint132_t ans = *this;
    ans >>= shift;
    return ans;
}

uint132_t uint132_t::operator<<(size_t shift) const {
    uint132_t ans = *this;
    ans <<= shift;
    return ans;
}

uint132_t &uint132_t::operator+=(const uint132_t &other) {
    int32_t ind = 0, carry = 0;
    while (ind < other.data_.size() || ind < data_.size()) {
        if (data_.size() <= ind) data_.push_back(0);
        int32_t val = (other.data_.size() > ind ? other.data_[ind] : 0) + (data_.size() > ind ? data_[ind] : 0) + carry;
        carry = val / system_;
        data_[ind] = val % system_;
        ++ind;
    }
    if (carry > 0) {
        if (data_.size() <= ind) data_.push_back(0);
        data_[ind] = carry;
    }
    return *this;
}

uint132_t &uint132_t::operator-=(uint132_t other) {
    if (data_.size() < other.data_.size()) {
        data_.resize(other.data_.size(), 0);
    } else if (data_.size() > other.data_.size()) {
        other.data_.resize(data_.size(), 0);
    }

    int carry = 0;
    for (int i = 0; i < data_.size(); ++i) {
        data_[i] += system_ - other.data_[i] - carry;
        carry = 1 - data_[i] / system_;
        data_[i] %= system_;
    }

    return *this;
}

uint132_t &uint132_t::operator*=(uint132_t other) {
    if (GetSystem() != other.GetSystem()) {
        SetSystem(other.GetSystem());
    }
    *this = KarazubaMul(*this, other);
    Reduce();
    return *this;
}

uint132_t &uint132_t::operator/=(const uint132_t &other) {
    uint132_t l = 0, r = std::max(*this, other) + 1;
    while (r > l + uint132_t(1, 10)) {
        uint132_t mid = StupidDiv(l + r, 2);
        uint132_t val = mid * other;
        if (mid * other <= *this) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return *this = l;
}

uint132_t &uint132_t::operator<<=(size_t shift) {
    data_.resize(data_.size() + shift);
    std::copy(data_.begin(), data_.end() - shift, data_.begin() + shift);
    std::fill(data_.begin(), data_.begin() + shift, 0);
    return *this;
}

uint132_t &uint132_t::operator>>=(size_t shift) {
    std::copy(data_.begin() + shift, data_.end(), data_.begin());
    std::fill(data_.end() - shift, data_.end(), 0);
    return *this;
}

uint132_t &uint132_t::operator%=(const uint132_t &mod) {
    return *this = *this - (*this / mod) * mod;
}

uint132_t uint132_t::StupidMul(uint132_t a, uint132_t b) {
    uint132_t ans(0, a.GetSystem());
    ans.data_.resize(a.data_.size() + b.data_.size() + 1);
    for (int i = 0; i < a.data_.size(); ++i) {
        int carry = 0;
        for (int j = 0; j < b.data_.size() || carry > 0; ++j) {
            int val = (b.data_.size() > j ? b.data_[j] : 0) * a.data_[i] + carry + ans.data_[j + i];
            ans.data_[j + i] = val % ans.GetSystem();
            carry = val / ans.GetSystem();
        }
    }
    ans.Reduce();
    return ans;
}

uint132_t uint132_t::KarazubaMul(uint132_t l, uint132_t r) {
    if (l.data_.size() <= 8 && r.data_.size() <= 8) {
        return StupidMul(l, r);
    }

    int size = std::max(l.data_.size(), r.data_.size());
    if (size & 1) ++size;
    l.data_.resize(size, 0);
    r.data_.resize(size, 0);

    int shift = l.data_.size() / 2;
    uint132_t a(l.data_.rbegin(), l.data_.rbegin() + shift, l.GetSystem());
    uint132_t b(l.data_.rbegin() + shift, l.data_.rend(), l.GetSystem());

    uint132_t c(r.data_.rbegin(), r.data_.rbegin() + shift, r.GetSystem());
    uint132_t d(r.data_.rbegin() + shift, r.data_.rend(), r.GetSystem());

    uint132_t ac = KarazubaMul(a, c);
    uint132_t bd = KarazubaMul(b, d);

    return (ac << shift * 2) + ((KarazubaMul(a + b, c + d) - ac - bd) << shift) + bd;
}

bool operator<(const uint132_t &lhs, const uint132_t &rhs) {
    for (int i = std::max(lhs.data_.size(), rhs.data_.size()) - 1; i >= 0; --i) {
        if (rhs.data_.size() <= i && lhs.data_[i] > 0) {
            return false;
        } else if (lhs.data_.size() <= i && rhs.data_[i] > 0) {
            return true;
        } else if (rhs.data_.size() > i && lhs.data_.size() > i && lhs.data_[i] > rhs.data_[i]) {
            return false;
        } else if (lhs.data_.size() > i && rhs.data_.size() > i && lhs.data_[i] < rhs.data_[i]) {
            return true;
        }
    }
    return false;
}

bool operator>(const uint132_t &lhs, const uint132_t &rhs) {
    return rhs < lhs;
}

bool operator<=(const uint132_t &lhs, const uint132_t &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const uint132_t &lhs, const uint132_t &rhs) {
    return !(lhs < rhs);
}

bool operator==(const uint132_t &lhs, const uint132_t &rhs) {
    return lhs >= rhs && lhs <= rhs;
}

bool operator!=(const uint132_t &lhs, const uint132_t &rhs) {
    return !(lhs == rhs);
}

uint132_t my_bin_pow(uint132_t num, uint132_t pow) {
    if (pow == 0) return uint132_t(1, num.GetSystem());
    if (pow % uint132_t(2, pow.GetSystem()) == 0) {
        return my_bin_pow(num * num, pow / 2);
    } else {
        return num * my_bin_pow(num, pow - 1);
    }
}

std::string to_string(const uint132_t &num) {
    int ind = num.data_.size() - 1;
    while(ind >= 0 && num.data_[ind] == 0) --ind;
    std::string ans;
    while (ind >= 0) {
        ans.push_back('0' + num.data_[ind]);
        --ind;
    }
    return (ans.empty() ? "0" : ans);
}

uint132_t uint132_t::StupidDiv(uint132_t a, uint8_t b) {
    int carry = 0;
    for (int i = a.data_.size() - 1; i >= 0; --i) {
        int val = carry * a.GetSystem() + a.data_[i];
        a.data_[i] = val / b;
        carry = val % b;
    }
    return a;
}

uint132_t::uint132_t(std::string s, uint8_t sys)
    : data_(std::max(s.size(), 10ull), 0)
    , system_(sys)
{
    for (int i = 0; i < s.size(); ++i) {
        data_[i] = s[s.size() - i - 1] - '0';
    }
}

void uint132_t::Reduce() {
    while (data_.size() > 10 && data_.back() == 0) data_.pop_back();
}
