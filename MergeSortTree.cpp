#include <bits/stdc++.h>
#define fr first
#define sc second
#define pii pair <int, int>
#define szof(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define pb push_back
#define mk make_pair
#define prev prev1331313 
using namespace std;
 
const int MAXN = (int)5e5 + 5;
 
int a[MAXN];
int prev[MAXN];
int nxt[MAXN];
int last[MAXN]; 
 
struct Merge_Sort_Tree {
    struct node {
        int x, l, r;
        node (int x_, int l_, int r_) {
            x = x_, l = l_, r = r_;
        }
        node () {
            
        }
    };
    vector <vector<node>> tree;
    vector <vector<node>> pref;
    Merge_Sort_Tree (int n) {
        tree.resize(n * 4);
        pref.resize(n * 4);
    }
    void merge(int v, vector<node> &nw, vector<node> &vecl, vector<node> &vecr) {
        int pl = 0, pr = 0;
        while (pl < szof(vecl) && pr < szof(vecr)) {
            if (vecl[pl].l != vecr[pr].l) {
                if (vecl[pl].l < vecr[pr].l) {
                    nw.pb(vecl[pl]);
                    pl++;
                } else {
                    nw.pb(vecr[pr]);
                    pr++;
                }
            } else {
                if (vecl[pl].r < vecr[pr].r) {
                    nw.pb(vecl[pl]);
                    pl++;
                } else {
                    nw.pb(vecr[pr]);
                    pr++;
                }
            }
        }
        while (pl < szof(vecl)) {
            nw.pb(vecl[pl++]);
        } 
        while (pr < szof(vecr)) {
            nw.pb(vecr[pr++]);
        }
        pii cur = {-1e9, -1e9};
        // first => max r
        // second => number
        for (auto el : nw) {
            if (cur.fr < el.r) {
                cur.fr = el.r;
                cur.sc = el.x;
            }
            pref[v].pb(node(cur.sc, -1, cur.fr));
        }
    }
    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].pb(node(a[tl], prev[tl], nxt[tl]));
            pref[v].pb(node(a[tl], prev[tl], nxt[tl]));
            return;
        }
        int mid = (tl + tr) >> 1;
        build(v + v, tl, mid);
        build(v + v + 1, mid + 1, tr);
        merge(v, tree[v], tree[v + v], tree[v + v + 1]);
    }
    int get(int l, int r, int v, int tl, int tr) { // log^2
        if (l > tr || tl > r) {
            return -1;
        }
        if (l <= tl && tr <= r) {
            if (tree[v][0].l < l) {
                int lo = 0, hi = szof(tree[v]);
                while (hi - lo > 1) {
                    int md = (hi + lo) >> 1;
                    if (tree[v][md].l < l) {
                        lo = md;
                    } else {
                        hi = md;
                    }
                }
                return (pref[v][lo].r > r ? pref[v][lo].x : -1);
            } else {
                return -1;
            }
        }
        int mid = (tl + tr) >> 1;
        return max(get(l, r, v + v, tl, mid), get(l, r, v + v + 1, mid + 1, tr));
        //int left_part = get(l, r, v + v, tl, mid);
        //if (left_part != -1) {
            //return left_part;
        //} else {
            //return get(l, r, v + v + 1, mid + 1, tr);
        //}
    }
};
 
void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        prev[i] = nxt[i] = -1;
        last[a[i]] = -1;
    }
    for (int i = 1; i <= n; i++) {
        if (last[a[i]] == -1) {
            prev[i] = 0;
        } else {
            prev[i] = last[a[i]];
        }
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        last[a[i]] = -1;
    }
    for (int i = n; i >= 1; i--) {
        if (last[a[i]] == -1) {
            nxt[i] = n + 1;
        } else {
            nxt[i] = last[a[i]];
        }
        last[a[i]] = i;
    }
    Merge_Sort_Tree T(n);
    T.build(1, 1, n);
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int ans = T.get(l, r, 1, 1, n);
        if (ans == -1) {
            ans = 0;
        }
        printf("%d\n", ans);
    }
}
 
signed main() {
    int tc = 1;
    while (tc--) {
        solve();
    }
}
