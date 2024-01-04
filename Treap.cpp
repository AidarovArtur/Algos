/*
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░▄▄███▄▄▄░▄▄██▄░░░░░░░
░░░░░░░░░██▀███████████████▀▀▄█░░░░░░
░░░░░░░░█▀▄▀▀▄██████████████▄░░█░░░░░
░░░░░░░█▀▀░▄██████████████▄█▀░░▀▄░░░░
░░░░░▄▀░░░▀▀▄████████████████▄░░░█░░░
░░░░░▀░░░░▄███▀░░███▄████░████░░░░▀▄░
░░░▄▀░░░░▄████░░▀▀░▀░░░░░░██░▀▄░░░░▀▄
░▄▀░░░░░▄▀▀██▀░░░░░▄░░▀▄░░██░░░▀▄░░░░
█░░░░░█▀░░░██▄░░░░░▀▀█▀░░░█░░░░░░█░░░
█░░░▄▀░░░░░░██░░░░░▀██▀░░█▀▄░░░░░░▀▀▀
▀▀▀▀░▄▄▄▄▄▄▀▀░█░░░░░░░░░▄█░░█▀▀▀▀▀█░░
░░░░█░░░▀▀░░░░░░▀▄░░░▄▄██░░░█░░░░░▀▄░
░░░░█░░░░░░░░░░░░█▄▀▀▀▀▀█░░░█░░░░░░█░
░░░░▀░░░░░░░░░░░░░▀░░░░▀░░░░▀░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ░░░░░░░░
*/
 
#include <bits/stdc++.h>
#define ll long long
#include <random>
#include <chrono>
using namespace std;
 
 
struct Treap {
  struct node {
    int prior;
    ll sz = 0, key = 0, sum = 0;
    node* l, * r;
    node(ll x) : key(x), prior((rand() << 15) + rand()), sum(x), sz(1), l(0), r(0) {}
  };
 
  using pNode = node*;
  pNode root = 0;
 
  int getsz(pNode t) {
    if (!t) {
      return 0;
    }
    return t->sz;
  }
  ll getsum(pNode t) {
    if (!t) {
      return 0;
    }
    return t->sum;
  }
  void calc(pNode t) {
    if (!t) {
      return;
    }
    t->sum = getsum(t->l) + getsum(t->r) + t->key;
    t->sz = getsz(t->l) + getsz(t->r) + 1;
  }
  pair<pNode, pNode> split(pNode t, ll x) {
    if (!t) {
      return { 0, 0 };
    }
    if (t->key <= x) {
      auto res = split(t->r, x);
      t->r = res.first;
      calc(t);
      return { t, res.second };
    }
    if (t->key > x) {
      auto res = split(t->l, x);
      t->l = res.second;
      calc(t);
      return { res.first, t };
    }
  }
 
  // all_key_of l <= all_key_of r
  pNode merge(pNode l, pNode r) {
    if (!l) {
      return r;
    }
    if (!r) {
      return l;
    }
    if (l->prior > r->prior) {
      l->r = merge(l->r, r);
      calc(l);
      return l;
    }
    else {
      r->l = merge(l, r->l);
      calc(r);
      return r;
    }
  }
  bool exist(pNode t, ll x) {
    if (!t) {
      return false;
    }
    if (t->key == x) {
      return true;
    }
    else if (t->key < x) {
      return exist(t->r, x);
    }
    else {
      return exist(t->l, x);
    }
  }
  void insert(ll x) {
    if (exist(root, x)) {
      return;
    }
    auto res = split(root, x);
    root = merge(merge(res.first, new node(x)), res.second);
  }
  void erase(ll x) {
    if (!exist(root, x)) {
      return;
    }
    auto res = split(root, x);
    auto mid = split(res.first, x - 1);
    root = merge(mid.first, res.second);
  }
  ll get_sum(ll l, ll r) {
    auto res = split(root, l - 1); // res.fr < l res.sc >= l
    auto mid = split(res.second, r); // l <= mid.fr <= r mid.sc > r
    ll ans = getsum(mid.first);
    res.second = merge(mid.first, mid.second);
    root = merge(res.first, res.second);
    return ans;
  }
  ll get_sum_min(pNode t, ll x) {
    if (getsz(t) <= x) {
      return getsum(t);
    }
    if (getsz(t->l) + 1 == x) {
      return getsum(t->l) + t->key;
    }
    if (getsz(t->l) + 1 > x) {
      return get_sum_min(t->l, x);
    }
    else {
      return getsum(t->l) + t->key + get_sum_min(t->r, x - getsz(t->l) - 1);
    }
  }
};
 
signed main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  string type = "";
  ll x, l, r;
  Treap t;
  for (int i = 1; i <= n; i++) {
    cin >> type;
    if (type == "insert") {
      cin >> x;
      t.insert(x);
    }
    if (type == "erase") {
      cin >> x;
      t.erase(x);
    }
    if (type == "sum") {
      cin >> l >> r;
      cout << t.get_sum(l, r) << endl;
    }
    if (type == "sum_min") {
      cin >> x;
      cout << t.get_sum_min(t.root, x) << endl;
    }
  }
}
