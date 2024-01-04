
#include <bits/stdc++.h>
#define fr first
#define sc second
#define mk make_pair
#define pb push_back
#define pii pair<int, int>
#define szof(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define debug(x) cerr << "# " << x << endl;
#define int long long
using namespace std;
 
const int MAXN = (int)2e5 + 5;
const double INF = 1e9;
 
double t[MAXN];
double dp[MAXN][51];
double sum[MAXN], pre[MAXN], rev[MAXN];
double q[MAXN];
int n, k;
 
struct Line {
    double k, b;
    double l, r;
    Line () {
        k = 1e9, b = 1e9;
    }
    Line (double k_, double b_, double l_, double r_) {
        k = k_;
        b = b_;
        l = l_;
        r = r_;
    }
    Line (double k_, double b_) {
        k = k_, b = b_;
    }
    double cost(double x) {
        return x * k + b;
    }
};
 
signed main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i - 1] + t[i];
        pre[i] = pre[i - 1] + sum[i] / t[i];
        rev[i] = rev[i - 1] + (1.0 / t[i]);
    }
    for (int i = 1; i <= n; i++) {
        q[i] = rev[i];
    }
    sort(q + 1, q + n + 1);
    for (int gr = 0; gr <= k; gr++) {
        for (int i = 0; i <= n; i++) {
            dp[i][gr] = INF;
        }
    }
    dp[0][0] = 0;
    auto cost = [&](int l, int r) {
        return pre[r] - pre[l - 1] - (rev[r] - rev[l - 1]) * sum[l - 1];
    };
    if (n == 1) {
        return cout << pre[n], 0;
    } else {
        for (int i = 1; i <= n; i++) {
            dp[i][1] = cost(1, i);
        }
        vector <Line> vec;
        auto add_line = [&](Line line) {
            while (1) {
                if (vec.empty()) {
                    vec.pb(Line(line.k, line.b, -INF, INF));
                    break;
                }
                if (vec.back().k == line.k) {
                    vec.back().b = min(vec.back().b, line.b);
                    break;
                } else {
                    double inter = (vec.back().b - line.b) / (line.k - vec.back().k);
                    if (vec.back().l < inter) {
                        vec.back().r = inter;
                        vec.pb(Line(line.k, line.b, inter, INF));
                        break;
                    } else {
                        vec.pop_back();
                    }
                }
            }
        };
        auto get_opt = [&](double x) {
            int l = -1, r = szof(vec);
            while (r - l > 1) {
                int mid = (l + r) >> 1;
                if (x <= vec[mid].r) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            return vec[r].cost(x);
        };
        for (int gr = 1; gr < k; gr++) {
            vec.clear();
            for (int l = gr; l <= n; l++) {
                Line cur_line = Line(-sum[l], dp[l][gr] - pre[l] + rev[l] * sum[l]); // было dp[gr][l]
                add_line(cur_line);
                int i = l + 1;
                if (i <= n) {
                    double kb = get_opt(rev[i]);
                    dp[i][gr + 1] = pre[i] + kb;
                }
            }
        }
        cout << setprecision(10) << fixed << dp[n][k];
    }
}
