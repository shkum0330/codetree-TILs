#include <bits/stdc++.h>
using namespace std;

int tme[16];
int pay[16];
int n,maxValue=0;

void cal(int idx,int sum) {
	if (idx > n) return;
	if (idx == n) {
		if (sum > maxValue) maxValue = sum;
		return;
	}
	cal(idx + tme[idx], sum + pay[idx]);
	cal(idx + 1, sum);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> tme[i] >> pay[i];
	}
	cal(0,0);
	cout << maxValue<<'\n';
}