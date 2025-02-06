// Need to keep track of the number of successive steps leading to a block
// The occupancy matrix would be 2*10^5 bytes or 200 KB if it's just 1 byte per
// vertex. Otherwise, 400KB if its 2 bytes
//
// The simple idea is that the visited list is <i,j,dir,consec_count>
// Each vertex in this graph is the location + direction and consecutive moves
// used to reach it. Leave out the consecutive moves and the graph becomes
// cyclic and the search is infinite.
//
// Implementation of the visited matrix using chinese remainder theorem
// Like any BFS/DFS problem, if you can see the traversal, the debugging becomes
// easier

#include <bits/stdc++.h>
#ifdef DEBUG
constexpr bool debug = true;
#else
constexpr bool debug = false;
#endif
using namespace std;
using u8 = uint8_t;
using u16 = uint16_t;

constexpr u16 calcmoves(array<u8, 4> moves) {
  u16 ans = 0;
  ans += (moves[0] * 8 * 11 * 13 * 10) % 12870;
  ans += (moves[1] * 3 * 9 * 13 * 10) % 12870;
  ans += (moves[2] * 7 * 9 * 11 * 10) % 12870;
  ans += (moves[3] * 3 * 9 * 11 * 13) % 12870;
  return ans;
}
int main() {
  int n,m;
  cin >> n >> m;
  u16* grid = (u16*) calloc(n*m, sizeof(u16));
  const u8 dirs[4] = {0b0001, 0b0010, 0b0100, 0b1000};
  // This grid doubles as the occupancy matrix
  auto access = [grid, m, n](int i, int j) -> u16* {
    if (i < 0 or i >= n or j < 0 or j >= m) return nullptr;
    return (grid + i*m + j);
  };
  auto countmoves = [access](u16 val) {
    return array<u8,4> {val % 9, val % 11, val % 13, val % 10};
  };
  int start_i = 0, start_j = 0, end_i = 0, end_j = 0;
  for (int i = 0; i < n; i++) {
    string line;
    cin >> line;
    for (int j = 0; j < m; j++) {
      int c = line[j];
      if (c == 'S') {
        start_i = i;
        start_j = j;
      }
      if (c == '.') {
        *access(i, j) = 0;
      }
      if (c == 'T') {
        end_i = i;
        end_j = j;
      }
      if (c == '#') {
        *access(i,j) = 0xFFFF; // All walls are already visited
      }
    }
  }

  queue<vector<u8>> parents;
  parents.emplace(vector<u8>{0});
  queue<vector<pair<int, int>>> next;
  next.emplace(vector<pair<int,int>>{make_pair(start_i, start_j)});
  int cost = 0;
  if constexpr (debug) {
    printf("Start: %d, %d | Target: %d %d\n", start_i, start_j, end_i, end_j);
  }

  while (not next.empty()) {
    auto current = next.front();
    next.pop();
    auto parent = parents.front();
    parents.pop();
    vector<pair<int, int>> nextlvl;
    vector<u8> nextpar;
    if constexpr (debug) {
      printf("----LVL%d-----\n", cost);
    }
    for (int k = 0; k < current.size(); k++) {
      auto [loc_i, loc_j] = current[k];
      int p = parent[k];
      int prev_move = p & 0x0f;
      int succ_count = (p & 0xf0) >> 4;
      if (loc_i == end_i and loc_j == end_j) {
        printf("%d\n", cost);
        return 0;
      }
      if constexpr (debug) {
        printf("At: %d, %d | %d , %d\n", loc_i, loc_j, prev_move, succ_count);
      }
      u16 *neighbours[4] = {access(loc_i + 1, loc_j), access(loc_i - 1, loc_j),
                           access(loc_i, loc_j + 1), access(loc_i, loc_j - 1)};
      for (int a = 0; a < 4; a++) {
        if (dirs[a] == prev_move and succ_count == 2) {
          continue;
        }
        if (neighbours[a] == nullptr) continue;
        if (*neighbours[a] > 12870) continue;
        auto moves = countmoves(*neighbours[a]);
        if constexpr (debug) {
          printf("Moves: %d %d %d %d\n", moves[0], moves[1], moves[2], moves[3]);
        }
        int ts = 0;
        if (prev_move == dirs[a]) ts = succ_count + 1;
        if (moves[a] > 0 and moves[a] & (1 << ts)) continue; 
        moves[a] |= 1 << ts;
        *neighbours[a] = calcmoves(moves);
        nextlvl.emplace_back(loc_i + (a==0) - (a==1), loc_j + (a==2) - (a==3));
        nextpar.emplace_back(dirs[a] | ((succ_count + 1) * (dirs[a] == prev_move) << 4));
      }
    }
    if (not nextlvl.empty()) {
      next.push(nextlvl);
      parents.push(nextpar);
      cost++;
    }
  }
  printf("-1\n");
  return 0;
}
