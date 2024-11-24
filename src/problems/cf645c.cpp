#include <cstdio>
#include <cstring>

inline int max (int a, int b) { return (a > b) ? a : b;}
inline int min (int a, int b) { return (a < b) ? a : b;}
int main() {
  int len, k;
  scanf("%d %d", &len, &k);
  char* rooms = NULL;
  scanf("%ms", &rooms);
  int* opts = new int[len];
  int j = 0;
  for (int i = 0; i < len; i++) {
    if (rooms[i] == '0') opts[j++] = i;
  }
  int l = 0, m = 0, cost = 1e9;
  {
    while (l+k < j) {
      while(max(opts[m] - opts[l], opts[l+k] - opts[m]) > max(opts[m+1] - opts[l], opts[l+k] - opts[m+1])) m++;
      cost = min(cost, max(opts[m] - opts[l], opts[l+k]-opts[m]));
      l++;
    }
  }
  printf("%d\n", cost);
}
