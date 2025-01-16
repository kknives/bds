#include <bits/stdc++.h>
using namespace std;
using ll = uint64_t;

int main() {
  int tc, n;
  cin >> tc;
  const ll mod = 1000000007;
  while (tc--) {
    cin >> n;
    ll *nums = (ll*)calloc(n, n*sizeof(ll));
    // ll *bare_sum = (ll*)calloc(n, n*sizeof(ll));
    cin >> nums[0];
    // bare_sum[0] = nums[0] >> __builtin_clzll(nums[0]);
    for (int i = 1; i < n; i++) {
      cin >> nums[i];
      // bare_sum[i] = bare_sum[i-1] + (nums[i] >> __builtin_ctzll(nums[i]));
    }
    ll max_pow_2 = 0;
    for (int j = 0; j < n; j++) {
      max_pow_2 += __builtin_clzll(nums[j]);
      ll pow_2_sum = 0, sum = 0, max_num = 0;
      for (int i = j; i >= 0; i--) {
        int pow_2 = __builtin_ctzll(nums[i]);
        pow_2_sum += pow_2;
        if ((max_num << pow_2) < nums[i]) {
          sum += max_num % mod;
          max_num = nums[i];
          continue;
        }
        // printf("max: %ld | sum: %ld\n", max_num, sum);
        sum += (nums[i] >> pow_2) % mod;
        max_num = (max_num << pow_2) % mod;
        // if (pow_2_sum >= 32) {
        //   max_num <<= (max_pow_2 - pow_2_sum);
        //   sum += bare_sum[i+1];
        //   printf("SAVING: %" PRIu64 " | %" PRIu64 "\n", max_num, bare_sum[i+1]);
        //   break;
        // }
      }
      sum += max_num % mod;
      printf("%" PRIu64 " ", sum % mod);
    }
    printf("\n");
    free(nums);
    // free(bare_sum);
  }
}
