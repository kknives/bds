#include <bits/stdc++.h>
using namespace std;
using ll = uint64_t;

int main() {
  int tc, n;
  cin >> tc;
  while (tc--) {
    cin >> n;
    ll *nums = (ll*)calloc(n, n*sizeof(ll));
    for (int i = 0; i < n; i++) cin >> nums[i];
    for (int j = 0; j < n; j++) {
      ll pow_2_sum = 0, sum = 0, max_num = 0;
      for (int i = j; i >= 0; i--) {
        int pow_2 = __builtin_ctzll(nums[i]);
        if ((max_num << pow_2) < nums[i]) {
          sum += max_num;
          max_num = nums[i];
          continue;
        }
        // printf("max: %ld | sum: %ld\n", max_num, sum);
        // pow_2_sum += pow_2;
        sum += nums[i] >> pow_2;
        max_num <<= pow_2;
      }
      printf("%ld ", (sum+max_num) % 1000000007);
    }
    printf("\n");
  }
}
