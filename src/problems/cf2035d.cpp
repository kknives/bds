#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
using i64 = int64_t;

int main() {
  int tc, n;
  cin >> tc;
  const u64 mod = 1000000007;
  while (tc--) {
    cin >> n;
    vector<i64> prev_max;
    vector<i64> prev_pow;
    i64 csum = 0;
    for (int i = 0; i < n; i++) {
      int num;
      cin >> num;
      i64 pows = __builtin_ctzll(u64(num)), a = num >> pows;
      while (not prev_max.empty()) {
        if (pows >= 30 or prev_max.back() <= num) {
          pows += prev_pow.back();
          csum += prev_max.back();
          prev_max.pop_back();
          prev_pow.pop_back();
        }
        else break;
      }
      if (pows != 0) {
        prev_max.push_back(a);
        prev_pow.push_back(pows);
      } else csum += num;
      i64 sum = csum;
      for (i64 j = prev_max.size()-1; j >= 0; j--) {
        sum += (prev_max[j] << prev_pow[j]) % mod;
      }
      printf("%" PRIi64" ", sum %mod);
    }
    putchar('\n');
  }
}
