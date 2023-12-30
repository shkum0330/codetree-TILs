#include <bits/stdc++.h>
using namespace std;

int num[12];
int n;
int maxres = -1000000000;
int minres = 1000000000;

void dfs(int add, int sub, int mul, int div, int cnt, int sum) {
    if (cnt == n) {
        maxres = max(sum, maxres);
        minres = min(sum, minres);
    }
    if (add > 0) dfs(add - 1, sub, mul, div, cnt + 1, sum + num[cnt]);
    if (sub > 0) dfs(add , sub - 1, mul, div, cnt + 1, sum - num[cnt]);
    if (mul > 0) dfs(add , sub, mul - 1, div, cnt + 1, sum * num[cnt]);
    if (div > 0) dfs(add , sub, mul, div - 1, cnt + 1, sum / num[cnt]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    int add, sub, mul, div;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    cin >> add >> sub >> mul >> div;
    dfs(add, sub, mul, div, 1, num[0]);
    cout << minres << ' ' << maxres << '\n';
}