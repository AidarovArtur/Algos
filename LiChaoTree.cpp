#include <bits/stdc++.h>
#define fr first
#define sc second
#define pb push_back
#define pii pair<int, int>
#define szof(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define int long long
using namespace std;
 
const int MAXN = (int)1e5 + 5;
const int INF = INT64_MAX;
 
int a[MAXN];
int b[MAXN];
int dp[MAXN];
 
struct Line {
    int k, b;
    Line (int k_, int b_) {
        k = k_, b = b_;
    }
    Line () {
    }
    int cost(int x) {
        return k * x + b;
    }
};
 
vector <int> g[MAXN];
vector <Line> vec[MAXN];
 
int used_type[MAXN];
 
int cnt = 1e9;
 
bool F = false;
 
struct Dynamic_Li_Chao {
    int my_id;
    struct node {
        Line line;
        node *lson, *rson;
        int used;
        int tl, tr;
        node (int tl_, int tr_) {
            tl = tl_, tr = tr_;
            lson = nullptr, rson = nullptr;
            line = Line();
            used = -1;
        }
        node () {
            tl = tr = 0;
            lson = rson = nullptr;
            line = Line();
            used = -1;
        }
    };
    void clean() {
        my_id = cnt++;
    }
    using pNode = node*;
    pNode root = new node(-MAXN, MAXN);
    void add_line(Line cur_line, pNode vertex) {
        int tl = vertex->tl, tr = vertex->tr;
        if (vertex->used != my_id) {
            vertex->line = cur_line;
            vertex->used = my_id;
            return;
        }
        if (tl == tr) {
            if (cur_line.cost(tl) < vertex->line.cost(tl)) {
                vertex->line = cur_line;
            }
            return;
        }
        int mid = (tl + tr) >> 1;
        bool f_mid = cur_line.cost(mid + 1) < vertex->line.cost(mid + 1);
        bool f_tl = cur_line.cost(tl) < vertex->line.cost(tl);
        if (f_mid) {
            swap(cur_line, vertex->line);
        }
        if (f_mid == f_tl) {
            if (vertex->rson == nullptr) {
                vertex->rson = new node(mid + 1, tr);
            }
            add_line(cur_line, vertex->rson);
        } else {
            if (vertex->lson == nullptr) {
                vertex->lson = new node(tl, mid);
            }
            add_line(cur_line, vertex->lson);
        }
    }
    int get_opt(int x, pNode vertex) {
        int tl = vertex->tl;
        int tr = vertex->tr;
        if (vertex->used != my_id) {
            return INF;
        }
        if (tl == tr) {
            return vertex->line.cost(x);
        }
        int mid = (tl + tr) >> 1;
        if (x <= mid) {
            if (vertex->lson == nullptr) {
                vertex->lson = new node(tl, mid);
            }
            return min(vertex->line.cost(x), get_opt(x, vertex->lson));
        } else {
            if (vertex->rson == nullptr) {
                vertex->rson = new node(mid + 1, tr);
            }
            return min(vertex->line.cost(x), get_opt(x, vertex->rson));
        }
    }
}T[MAXN];
 
set <int> free_tree;
int tree_id[MAXN];
 
void dfs(int v, int par) {
    tree_id[v] = v;
    free_tree.erase(tree_id[v]);
    T[tree_id[v]].clean();
    if (szof(g[v]) == 1 && v != 1) {
        dp[v] = 0;
        vec[v].pb(Line(b[v], 0));
        T[tree_id[v]].add_line(Line(b[v], 0), T[tree_id[v]].root);
        return;
    }
    for (int to : g[v]) {
        if (to == par) {
            continue;
        }
        dfs(to, v);
        if (szof(vec[v]) < szof(vec[to])) {
            swap(vec[v], vec[to]);
            swap(tree_id[v], tree_id[to]);
        }
        for (auto el : vec[to]) {
            vec[v].pb(el);
            T[tree_id[v]].add_line(el, T[tree_id[v]].root);
        }
        free_tree.insert(tree_id[to]);
        vec[to].clear();
    }
    dp[v] = T[tree_id[v]].get_opt(a[v], T[tree_id[v]].root);
    vec[v].pb(Line(b[v], dp[v]));
    T[tree_id[v]].add_line(Line(b[v], dp[v]), T[tree_id[v]].root);
}
 
signed main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        free_tree.insert(i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
    }
}
 
/*
slow
-5520 0 -44 0 
fast
184 0 -44 0 
 
4
-92 84 22 -91 
-7 -2 -36 60 
3 2
1 3
4 3
*/
