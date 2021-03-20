#include <vector>

namespace cht {
    struct line_t {
        long long k, b;
        line_t(long long __k,long long __b) : k(__k), b(__b) {}
        long long operator()(long long x) { return k * x + b; }
        long double intersect_x(line_t other) { return (long double)(other.b - b) / (k - other.k); }
    };

    std::vector<line_t> hull;

    void add(long long k, long long b) { // what if the slopes are the same?
        line_t line(k, b);
        while (hull.size() > 1 && hull[hull.size() - 2].intersect_x(line) < hull[hull.size() - 1].intersect_x(line)) {
            hull.pop_back();
        }
        hull.push_back(line);
    }

    long long get(long long x) {
        int l = 0, r = hull.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (hull[m - 1](x) < hull[m](x)) { // 'less' for maximum
                l = m;
            } else {
                r = m;
            }
        }
        return hull[l](x);
    }

    // this CHT for maximum, so remember
    // to sort lines by slope in increasing order
}