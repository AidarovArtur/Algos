#include <bits/stdc++.h>
#define fr first
#define sc second
#define pii pair <int, int>
#define szof(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define pb push_back
#define mk make_pair 
using namespace std;
 
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
 
const int MAXN = (int)3e5 + 5;
const int INF = 1e9;
const int BLOCK = 700;
const int C = 100;
 
int a[MAXN];
int cnt[MAXN];
int answer[MAXN];
 
int get_rand() {
    int x = rnd();
    if (x < 0) {
        x = -x;
    }
    return x;
}
 
int gen(int l, int r) {
    return l + get_rand() % (r - l + 1);
}
 
struct Query {
    int l, r, k, id;
    Query (int l_, int r_, int k_, int id_) {
        l = l_;
        r = r_;
        k = k_;
        id= id_;
    }
    bool operator < (const Query &other) {
        if (l / BLOCK != other.l / BLOCK) {
            return l / BLOCK < other.l / BLOCK;
        } else {
            return r < other.r;
        }
    }
};
 
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector <Query> vec;
    for (int i = 1; i <= q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        vec.pb(Query(l, r, k, i));
    }
    sort(vec.begin(), vec.end());
    auto add = [&](int x) {
        cnt[x]++;
    };
    auto del = [&](int x) {
        cnt[x]--;
    };
    int l = 1, r = 1;
    add(a[l]);
    for (int i = 0; i < q; i++) {
        int need = (vec[i].r - vec[i].l + 1) / vec[i].k;
        while (vec[i].l < l) {
            add(a[--l]);
        }
        while (r < vec[i].r) {
            add(a[++r]);
        }
        while (l < vec[i].l) {
            del(a[l++]);
        }
        while (vec[i].r < r) {
            del(a[r--]);    
        }
        int ans = INF;
        for (int j = 1, pos; j <= C; j++) {
            pos = gen(l, r);
            if (cnt[a[pos]] > need) {
                ans = min(ans, a[pos]);
            }
        }
        answer[vec[i].id] = (ans == INF ? -1 : ans);
    }
    for (int i = 1; i <= q; i++) {
        cout << answer[i] << endl;
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
}
