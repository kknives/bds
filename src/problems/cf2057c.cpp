#include <bits/stdc++.h>
#ifdef DEBUG
constexpr bool debug = true;
#else
constexpr bool debug = false;
#endif
using namespace std;
using u64 = uint64_t;
using i64 = int64_t;
using u32 = uint32_t;

int main() {
  int tc;
  cin >> tc;
  while (tc--) {
    u32 l,r; cin >> l >> r;
    int k = 31 - __builtin_clz(l^r);
    u32 x = l | ((1<<k) - 1);
    u32 y = x + 1;
    u32 z = (x == l ? r : l);
    if constexpr (debug) {
      u32 max = (1 << k+1) -1;
      max <<= 1;
      printf("%u %u | ", max, (x^y)+(y^z)+(x^z));
    }
    printf("%u %u %u\n", x, y, z);
  }
}
