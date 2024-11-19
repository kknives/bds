#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline ll idx(ll x, ll y, ll maxX) {return y*maxX + x;}
vector<vector<ll>> regions;
static ll glob_i = 0;
int cmp(const void* a, const void* b) {
  return regions[glob_i][*(ll*)a] - regions[glob_i][*(ll*)b];
  // return ((*glob_regions)[*(ll*)a]) <= ((*glob_regions)[*(ll*)b]);
}
ll index_lbound(const ll* index, vector<ll> const & val, ll n, ll obj) {
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
  vector<vector<ll>> temp(k, vector<ll>(n, 0));
  regions.swap(temp);
  // regions(k, vector<ll>(n, 0));
  // glob_regions.emplace(regions);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < k; j++) {
      cin >> regions[j][i];
    }
  }

  for (ll i = 0; i < k; i++) {
    for (ll j = 1; j < n; j++) regions[i][j] |= regions[i][j-1];
  }

  ll *index = static_cast<ll*>(calloc(k*n, sizeof(ll)));
  for (ll j = 0; j < n; j++) {
    index[idx(j, 0, n)] = j;
  }
  for (ll i = 1; i < k; i++) {
    memcpy((void*)&index[idx(0,i,n)], (void*)&index[idx(0,0,n)], n*sizeof(*index));
  }

  for (ll i = 0; i < k; i++) {
    glob_i = i;
    qsort(&index[idx(0,i,n)], n, sizeof(*index), cmp);
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
        ll ref = index_lbound(&index[idx(0,reg,n)], regions[reg], n, val);
        low = ref;
        up = n;
        cout << c << "| ref: " << ref << "| [" << low << "," << up << ")" << '\n';
      }      
      else {
        ll ref = index_lbound(&index[idx(0,reg,n)], regions[reg], n, val);
        low = 0;
        up = ref;
        cout << c << "| ref: " << ref << "| [" << low << "," << up << ")" << '\n';
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
