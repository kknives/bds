#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
  int n, q;
  scanf("%d", &n);  
  int* prices = new int[n];
  for (int i = 0; i < n; i++) scanf("%d", prices+i);
  sort(prices, prices+n);
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    ll val;
    scanf("%lld", &val);
    int l=-1;
    {
      int r = n;
      while (r-l > 1) {
        int m = (l+r) >> 1;
        if (val < prices[m]) r = m;
        else l = m;
      }
    }
    // printf("%d\n", l);
    if (l == -1) printf("%d\n", 0);
    else printf("%d\n", l+1);
  }
}
