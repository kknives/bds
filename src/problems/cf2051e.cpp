// Main thing is to realize that the optimal price will be one of the a_i or b_i
// This is because both are the transition points for the "buy" and "review"
// actions. Any other value other that a_i or b_i won't affect buy or review.
// This means a search on a_i and b_i. This can be done using sweep line.
// (a_i, 1) and (b_i, 2) is used to identify the type of event.
// As these are transition points, nothing happens at these values. Only after
// these values are crossed are the actions to be implemented. And for events
// with the same value, they must be implemented together.
//
// After that, working out on paper tells that the (a_i , 1) event increases the
// number of neg revies by 1, And (b_i, 2) event causes -1,-1. One reduction in
// trees bought and neg reviews.
//
// Additional memory allocation reduction by making the events vector in outer
// scope and reserving and clearing instead of destructing it for every TC.
//
// Also, the integer types give a lot of pain when printing. Just use PRIu64
// if using uint64_t. Also, realize that i and j cannot be int, because the
// events array can be 4*10^5 which is greater than int32_t.
#include <bits/stdc++.h>
#ifdef DEBUG
constexpr bool debug = true;
#else
constexpr bool debug = false;
#endif

using namespace std;
using u32 = uint32_t;
using u64 = uint64_t;

int main() {
  int tc;
  cin >> tc;
  vector<pair<u64, int>> events;
  while (tc--) {
    int n, k;
    cin >> n >> k;
    events.reserve(2*n);
    for (int i = 0; i < n; i++) {
      int t;
      cin >> t;
      events.emplace_back(t, 1);
    }
    for (int i = 0; i < n; i++) {
      int t;
      cin >> t;
      events.emplace_back(t, 2);
    }

    sort(events.begin(), events.end());
    u64 max_money = 0, trees = n, rev = 0;
    u64 chg_trees = 0, chg_rev = 0;
    u32 i = 0;
    while (i < events.size()) {
      auto [v, _] = events[i];
      trees += chg_trees;
      rev += chg_rev;
      if (rev <= k) max_money = max(max_money, v*trees);

      chg_trees = 0, chg_rev = 0;
      u32 j;
      for (j = i; events[j].first == v and j < events.size(); j++) {
        auto [_, type] = events[j];
        if (type == 1) {
          chg_trees += 0;
          chg_rev += 1;
        }
        if (type == 2) {
          chg_trees -= 1;
          chg_rev -= 1;
        }
      }
      i = j;
    }
    printf("%jd\n", max_money);
    events.clear();
  }
}
