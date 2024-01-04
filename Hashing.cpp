// S1mple example of Hash
#include <bits/stdc++.h>
#define int long long
#define szof(s) (int)s.size()
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
 
struct Hash {
  string s;
  vector <int> hsh, pw;
  int p, mod;
  Hash(string s_, int p_, int mod_) {
    s = s_;
    hsh.resize(szof(s) + 1, 0);
    pw.resize(szof(s) + 1, 0);
    p = p_, mod = mod_;
  }
  void build() {
    hsh[0] = (s[0] - 'a' + 1 + mod) % mod;
    pw[0] = 1;
    for (int i = 1; i <= szof(s); i++) {
      pw[i] = (pw[i - 1] * p) % mod;
    }
    for (int i = 1; i < szof(s); i++) {
      hsh[i] = (((hsh[i - 1] * p) % mod) + ((s[i] - 'a' + 1 + mod) % mod)) % mod;
    }
  }
  void Rbuild() {
    int n = szof(s);
    hsh[n - 1] = (s[n - 1] - 'a' + 1 + mod) % mod;
    pw[0] = 1;
    for (int i = 1; i <= szof(s); i++) {
      pw[i] = (pw[i - 1] * p) % mod;
    }
    for (int i = n - 2; i >= 0; i--) {
      hsh[i] = (((hsh[i + 1] * p) % mod) + ((s[i] - 'a' + 1 + mod) % mod)) % mod;
    }
  }
  int get(int l, int r) {
    if (l == 0) {
      return hsh[r];
    }
    return (hsh[r] - ((hsh[l - 1] * pw[r - l + 1]) % mod) + mod) % mod;
  }
  int Rget(int l, int r) {
    if (r == szof(s) - 1) {
      return hsh[l];
    }
    return (hsh[l] - ((hsh[r + 1] * pw[r - l + 1]) % mod) + mod) % mod;
  }
};
 
bool ok(Hash& a, Hash& b, int l, int r) {
  return (a.get(l, r) == b.Rget(l, r));
}
 
signed main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string s, a, b;
  cin >> s >> a >> b;
  Hash S(s, 167, (1 << 31) - 1);
  Hash A(a, 167, (1 << 31) - 1);
  Hash B(b, 167, (1 << 31) - 1);
  Hash S1(s, 997, (int)1e9 + 13);
  Hash A1(a, 997, (int)1e9 + 13);
  Hash B1(b, 997, (int)1e9 + 13);
  S.build();
  A.build();
  B.build();
  S1.build();
  A1.build();
  B1.build();
  vector <int> pos[2];
  int n = szof(s);
  if (max(szof(a), szof(b)) > szof(s)) {
    return cout << 0, 0;
  }
  int aa = szof(a), bb = szof(b);
  int ans = 0;
  
  vector <pii> vec;
 
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (j - i + 1 >= max(szof(a), szof(b))) {
        bool ok = 1;
        ok &= (S.get(i, i + aa - 1) == A.get(0, aa - 1));
        ok &= (S.get(j - bb + 1, j) == B.get(0, bb - 1));
        ok &= (S1.get(i, i + aa - 1) == A1.get(0, aa - 1));
        ok &= (S1.get(j - bb + 1, j) == B1.get(0, bb - 1));
        if (ok) {
          vec.push_back({ S.get(i, j), S1.get(i, j) });
        }
      }
    }
  }
 
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  cout << szof(vec);
}
