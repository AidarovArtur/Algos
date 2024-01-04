#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define szof(s) (int)s.size()
#define fr first
#define sc second
#define pii pair<int, int>
using namespace std;
const int MAXN = (int)2e5 + 5;
const int P = pow(1e5, 2.0 / 3.0);  // was 3.0 / 2.0 :)
const int S = 600;
struct Query {
  int l, r, t, id;
  Query(int l_, int r_, int t_, int id_) {
    l = l_, r = r_, t = t_, id = id_;
  }
  bool operator < (const Query& other) {
    if (t / P != other.t / P) {
      return t / P < other.t / P;
    } else if (l / P != other.l / P) {
      return l / P < other.l / P;
    } else {
      return r < other.r;
    }
  }
};
int a[MAXN];
int cnt[MAXN];
pair <int, int> change[MAXN];
bool need_to_ans[MAXN];
int ans[MAXN];
 
signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector <Query> query;
  vector <int> num;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    num.push_back(a[i]);
  }
  int tcnt = 0;
  for (int i = 1; i <= q; i++) {
    int tp;
    cin >> tp;
    if (tp == 1) {
      int l, r;
      cin >> l >> r;
      query.push_back(Query(l, r, tcnt, i));
      need_to_ans[i] = true;
    } else {
      int pos, x;
      cin >> pos >> x;
      num.push_back(x);
      change[++tcnt] = {pos, x};
    }
  }
  sort(all(num));
  num.erase(unique(all(num)), num.end());
  auto get = [&](int x) {
    int pos = lower_bound(all(num), x) - num.begin();
    return pos;
  };
  for (int i = 1; i <= n; i++) {
    a[i] = get(a[i]);
  }
  for (int i = 1; i <= tcnt; i++) {
    change[i].sc = get(change[i].sc);
  }
  vector <int> cur[MAXN];
  vector <int> ind(MAXN, 0);
  for (int i = 1; i <= n; i++) {
    cur[i].push_back(a[i]);
  }
  for (int i = 1; i <= tcnt; i++) {
    cur[change[i].fr].push_back(change[i].sc);
  }
  vector <int> cnt(MAXN, 0);
  vector <int> cc(MAXN, 0);
  auto add = [&](int x) {
    cc[cnt[x]]--;
    cnt[x]++;
    cc[cnt[x]]++;
  };
  auto del = [&](int x) {
    cc[cnt[x]]--;
    cnt[x]--;
    cc[cnt[x]]++;
  };
  auto add_change = [&](int t, int l, int r) {
    int pos = change[t].fr;
    int x = change[t].sc;
    if (cur[pos][ind[pos]]== x) {
      ind[pos]++;
      return;
    }
    if (l <= pos && pos <= r) {
      del(cur[pos][ind[pos]]);
      add(x);
    } else {
      // nothing
    }
    ind[pos]++;
  };
  auto del_change = [&](int t, int l, int r) {
    int pos = change[t].fr;
    if (cur[pos][ind[pos]] == cur[pos][ind[pos] - 1]) {
      ind[pos]--;
      return;
    }
    if (l <= pos && pos <= r) {
      del(cur[pos][ind[pos]]);
      add(cur[pos][ind[pos] - 1]);
    } else {
      // nothing
    }
    ind[pos]--;
  };
  auto get_mex = [&]() {
    for (int i = 1; i <= 600; i++) {
      if (!cc[i]) {
        return i;
      }
    }
    assert(false);
    return -1;
  };
  int l = 1, r = 1, t = 0;
  add(a[l]);
  sort(all(query));
  for (auto el : query) {
    while (t < el.t) {
      add_change(++t, l, r);
    }
    while (t > el.t) {
      del_change(t--, l, r);
    }
    while (el.l < l) {
      add(cur[l - 1][ind[l - 1]]);
      l--;
    }
    while (r < el.r) {
      add(cur[r + 1][ind[r + 1]]);
      r++;
    }
    while (l < el.l) {
      del(cur[l][ind[l]]);
      l++;
    }
    while (el.r < r) {
      del(cur[r][ind[r]]);
      r--;
    }
    ans[el.id] = get_mex();
  }
  for (int i = 1; i <= q; i++) {
    if (need_to_ans[i]) {
      cout << ans[i] << endl;
    }
  }
}
