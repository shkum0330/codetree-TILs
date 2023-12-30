#include <bits/stdc++.h>
using namespace std;

#define INF 987654321

typedef long long ll;
typedef pair<int,int> pii;

int k,res;
int arr[5][8];


void clock_lotate(int idx){
    int tmp=arr[idx][7];
    for (int i = 7; i > 0; i--) {
        arr[idx][i]=arr[idx][i-1];
    }
    arr[idx][0]=tmp;
}

void counter_clock_lotate(int idx){
    int tmp=arr[idx][0];
    for (int i = 0; i < 7; i++) {
        arr[idx][i]=arr[idx][i+1];
    }
    arr[idx][7]=tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    for (int i = 1; i <= 4; ++i) { // 2-6 2-6 2-6
        string s; cin>>s;
        for (int j = 0; j < 8; ++j) {
            arr[i][j]=s[j]-'0';
        }
    }

    cin>>k;
    for (int i = 0; i < k; ++i) {
        int num,dir; cin>>num>>dir;
        vector<pii> v; // {번호, 방향}
        int t=dir;
        v.push_back({num,dir});
        for (int j = num; j < 4; ++j) {
            if(arr[j][2]!=arr[j+1][6]) {
                v.push_back({j + 1, -t});
                t=-t;
            }
            else break;
        }
        t=dir;
        for (int j = num; j > 1; j--) {
            if(arr[j][6]!=arr[j-1][2]) {
                v.push_back({j - 1, -t});
                t=-t;
            }
            else break;
        }

        for (int j = 0; j < v.size(); ++j) {
            if(v[j].second==1){
                clock_lotate(v[j].first);
            }
            if(v[j].second==-1){
                counter_clock_lotate(v[j].first);
            }
        }
    }

    int num=1;
    for (int i = 1; i <= 4; ++i) {
        res += (arr[i][0]==1)? num:0;
        num *=2;
    }
    cout<<res<<'\n';
}