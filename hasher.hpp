#include <chrono>
#include <random>
#include <vector>

namespace hashing {
    using ull = unsigned long long;
    using hash_t = std::pair<ull, ull>;

    namespace modulo {
        const ull MOD = (1ULL << 61) - 1;
        
        ull fit(const ull a) {
            return (a & MOD) + (a >> 61);
        }
        
        ull mod(const ull a) {
            return fit(fit(a) + 1) - 1;
        }
        
        ull add(ull a, const ull b) {
            return (a += b) >= MOD ? (a -= MOD) : a;
        }
        
        ull sub(ull a, const ull b) {
            return (a < b) ? (MOD + a) - b : a - b;
        }
        
        ull mul(const ull a, const ull b) {
            const ull az = a & ~0U, ao = a >> 32, bz = b & ~0U, bo = b >> 32, tm = az * bo + ao * bz;
            return mod(fit(az * bz) + (ao * bo << 3) + (tm >> 29) + (tm << 32 & MOD));
        }
    }
    
    std::mt19937 rd(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<ull> deg[2] = { std::vector<ull>(1, 1), std::vector<ull>(1, 1) };
    ull alph = 257, base[2] = { (alph+(rd()&((1ULL<<47)-0x1)))|0x1, (alph+(rd()&((1ULL<<47)-0x1)))|0x1 };

    template<typename T>
    struct hasher {
        int length;
        std::vector<ull> pre[2] = { std::vector<ull>(1, 0), std::vector<ull>(1, 0) };

        hasher(const T &cntr) {
            length = cntr.size();
            
            for (int id = 0; id < 2; id++) {
                while (deg[id].size() <= length + 1) {
                    deg[id].push_back(modulo::mul(deg[id].back(), base[id]));
                }

                for (auto &el : cntr) {
                    pre[id].push_back(modulo::add(modulo::mul(pre[id].back(), base[id]), el));
                }
            }
        }

        hash_t operator()(int l, int r) {
            return {
                modulo::sub(pre[0][r], modulo::mul(pre[0][l], deg[0][r - l])),
                modulo::sub(pre[1][r], modulo::mul(pre[1][l], deg[1][r - l]))
            };
        }
    };
}