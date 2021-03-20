#include <bits/stdc++.h>

#include "modulo.hpp"
#include "hasher.hpp"
#include "cht.hpp"

int main() {
    // Test for "modulo"
    // Codeforces problem: https://codeforces.com/problemset/problem/1342/E

    {
        const int MOD = 998244353;
        modulo<MOD> c[200200] = { 1 };

        int n, k;
        std::cin >> n >> k;

        int s = n - k;
        modulo<MOD> x(1), y(1);

        if (s <= 0) {
            std::cout << 0 << std::endl;
        } else {
            for (int i = n; i >= n - s + 1; i--) {
                x *= i;
            }

            for (int i = 1; i <= s; i++) {
                y *= i;
            }

            for (int i = 1; i <= s; i++) {
                c[i] = c[i - 1] * (s - i + 1) / i;
            }

            modulo<MOD> ans(0);
            for (int i = 0; i <= s; i++) {
                ans = i & 1 ? ans - c[i] * pow(modulo<MOD>(s - i), n) : ans + c[i] * pow(modulo<MOD>(s - i), n);
            }

            std::cout << (1 + (k > 0)) * x * ans / y << std::endl;
        }
    }

    // Test for "hasher"
    // Codeforces problem: https://codeforces.com/contest/114/problem/D

    {
        std::string str, beg, end;
        std::cin >> str >> beg >> end;
    
        int m = str.size(), p = beg.size(), s = end.size();
        hashing::hasher<std::string> main(str), pref(beg), suff(end);
    
        int ans = 0;
        for (int i = std::max(p, s); i <= m; i++) {
            std::vector<hashing::hash_t> pool;
            
            for (int j = 0; j < str.size() - i + 1; j++) {
                if (main(j, j + p) == pref(0, p) && main(j + i - s, j + i) == suff(0, s)) {
                    pool.push_back(main(j, j + i));
                }
            }

            std::sort(pool.begin(), pool.end());

            ans += std::unique(pool.begin(), pool.end()) - pool.begin();
        }
    
        std::cout << ans;
    }

    // Test for "cht"
    // Codeforces problem: https://codeforces.com/contest/660/problem/F
    
    // s[l] + ... + (r - l + 1) * s[r] -> max
    // (l * s[l] + ... + r * s[r]) - (l - 1) * (s[l] + ... s[r]) -> max
    // weight[r] - weight[l - 1] - (l - 1) * (prefix[r] - prefix[l - 1]) -> max
    // for each r:
    //     f[l](x) = -weight[l - 1] - (l - 1) * (x - prefix[l - 1]) =
    //             = (1 - l) * (x - prefix[l - 1]) - weight[l - 1] =
    //             = (1 - l) * x + (l - 1) * prefix[l - 1] - weight[l - 1]
    // at x = prefix[r] -> max for each l

    {
        int n;
        std::cin >> n;
    
        long long ans = 0;
        std::vector<long long> a(n + 1), prefix(n + 1), weight(n + 1);
    
        for (int i = 1; i < n + 1; i++) {
            std::cin >> a[i];
            
            prefix[i] = prefix[i - 1] + a[i];
            weight[i] = weight[i - 1] + i * a[i];
    
            cht::add(1 - i, prefix[i - 1] * (i - 1) - weight[i - 1]);
            ans = std::max(ans, cht::get(prefix[i]) + weight[i]);
        }
    
        std::cout << ans << std::endl;
    }
}