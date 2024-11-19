#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll index_lbound(const int* index, vector<ll> const & val, ll n, ll obj) {
  ll count = n, step = 0, i = 0, first = 0;
  while (count > 0) {
    i = first;
    step = count >> 1;
    i += step;
    if (val[index[i]] <= obj) {
      first = i + 1;
      count -= step + 1;
    } else count = step;
  }
  return first;
}
int main() {
  ll n, k, q;
  cin >> n >> k >> q;
  vector<vector<ll>> regions(k, vector<ll>(n, 0));
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < k; j++) {
      cin >> regions[j][i];
    }
  }

  for (ll i = 0; i < k; i++) {
    for (ll j = 1; j < n; j++) regions[i][j] |= regions[i][j-1];
  }

  int** index = static_cast<int**>(calloc(n*k, sizeof(ll)));
  // vector<vector<ll>> index(k, vector<ll>(n, 0));
  for (ll j = 0; j < n; j++) {
    index[0][j] = j;
  }
  // for (ll i = 1; i < k; i++)
  //   copy(index[0].begin(), index[0].end(), index[i].begin());

  for (ll i = 0; i < 1; i++) {
    sort(index[i], index[i]+n, [&regions, i, n](ll a, ll b) {
         if (a >= n or b >= n) {
           cout << a << ", " << b << '\n';
           return false;
         }
           return regions[i][a] <= regions[i][b];
       });
  }

  while (q--) {
    ll bef = 0, aft = n;
    bool done = false;
    ll conds, reg; cin >> conds;
    while (conds--) {
      ll val; char c;
      cin >> reg >> c >> val;
      if (bef >= aft) {
         done = true;
         continue;
      }
      reg -= 1;
      ll low, up;

      if (c == '>') {
        ll ref = index_lbound(index[reg], regions[reg], n, val);
        low = ref;
        up = n;
        // cout << c << "| ref: " << ref << "| [" << low << "," << up << ")" << '\n';
      }      
      else {
        ll ref = index_lbound(index[reg], regions[reg], n, val);
        low = 0;
        up = ref;
        // cout << c << "| ref: " << ref << "| [" << low << "," << up << ")" << '\n';
      }

      if (low >= up) {
        done = true;
        continue;
      }

      if (low >= aft or bef >= up) {
        done = true;
        continue;
      }
      bef = max(bef, low);
      aft = min(aft, up);
    }    
    if (done) cout << "-1" << '\n';
    else cout << bef + 1 << '\n';
  }
}
