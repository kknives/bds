#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// int index_lbound(vector<int> const& index, vector<int> const & val, int n, int obj) {
//   int low = 0, highjjjjjjjjjjjj
// }
int main() {
  int n, k, q;
  cin >> n >> k >> q;
  vector<vector<int>> regions(k, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      cin >> regions[j][i];
    }
  }

  for (int i = 0; i < k; i++) {
    for (int j = 1; j < n; j++) regions[i][j] |= regions[i][j-1];
  }

  vector<vector<int>> index(k, vector<int>(n, 0));
  for (int j = 0; j < n; j++) {
    index[0][j] = j;
  }
  for (int i = 1; i < k; i++)
    copy(index[0].begin(), index[0].end(), index[i].begin());

  for (int i = 0; i < k; i++) {
    sort(index[i].begin(), index[i].end(), [&regions, i](int a, int b) {
           return regions[i][a] <= regions[i][b];
       });
  }

  while (q--) {
    int bef = 0, aft = n;
    int conds; cin >> conds;
    while (conds--) {
      int reg, val; char c;
      cin >> reg >> c >> val;
      if (bef >= aft) continue;
      reg -=1;
      int low, up;

      if (c == '>') {
        auto ref = lower_bound(index[reg].begin(), index[reg].end(), val, [&regions, reg](int a, int b) {
                                 return a <= regions[reg][b];
                               });
          low = 0;
          up = distance(index[reg].begin(), ref);
        
      }      
      else {
        auto ref = upper_bound(index[reg].begin(), index[reg].end(), val, [&regions, reg](int a, int b) {
                                 return a <= regions[reg][b];
                               });
          low = distance(index[reg].begin(), ref);
          up = n;
      }

      if (low >= up) {
        bef = aft;
        continue;
      }

      if (low >= aft or bef >= up) {
        bef = aft;
        continue;
      }
      bef = min(bef, low);
      aft = min(aft, up);
    }    
    if (bef >= aft) cout << "-1" << '\n';
    else cout << bef+1 << '\n';
  }
}
