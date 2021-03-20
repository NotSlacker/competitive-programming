#include <iostream>

template<typename T> 
T pow(T a, int n) {
    T r(1);
    if (n < 0) {
        a = 1 / a;
        n = -n;
    }
    while (n > 0) {
        if (n & 1) {
            r *= a;
        }
        a *= a;
        n /= 2;
    }
    return r;
}

template<int MOD = 1'000'000'007>
struct modulo {
    int val;

    modulo(long long tmp = 0) : val(tmp % MOD) {
        if (val < 0) {
            val += MOD;
        }
    }
    
    modulo(const modulo &other) : val(other.val)
    { }

    modulo &operator=(const modulo &other) {
        val = other.val;
        return *this;
    }

    modulo &operator+=(const modulo other) {
        val += other.val;
        if (val >= MOD) {
            val -= MOD;
        }
        return *this;
    }

    modulo &operator-=(const modulo &other) {
        val -= other.val;
        if (val < 0) {
            val += MOD;
        }
        return *this;
    }

    modulo &operator*=(const modulo other) {
        val = (val * 1LL * other.val) % MOD;
        return *this;
    }

    modulo &operator/=(const modulo other) {
        val = (val * 1LL * pow(other, MOD - 2).val) % MOD;
        return *this;
    }

    friend modulo operator+(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return modulo(lhs) += rhs;
    }

    friend modulo operator-(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return modulo(lhs) -= rhs;
    }
    
    friend modulo operator*(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return modulo(lhs) *= rhs;
    }

    friend modulo operator/(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return modulo(lhs) /= rhs;
    }
    
    friend bool operator<(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return lhs.val < rhs.val;
    }
    
    friend bool operator>(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return lhs.val > rhs.val;
    }
    
    friend bool operator==(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return lhs.val == rhs.val;
    }
    
    friend bool operator!=(const modulo<MOD> &lhs, const modulo<MOD> &rhs) {
        return lhs.val != rhs.val;
    }

    friend std::ostream& operator<<(std::ostream &out, const modulo<MOD> &other) {
        return out << other.val;
    }

    friend std::istream& operator>>(std::istream &inp, modulo<MOD> &other) {
        long long tmp;
        inp >> tmp;
        tmp %= MOD;
        other.val = tmp < 0 ? tmp + MOD : tmp;
        return inp;
    }
};