#include <bits/stdc++.h>
using namespace std;

#define INF 987654321
typedef pair<int,int> pii;
typedef long long ll;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int n,m,r,c,d,cnt;
int mmap[51][51];
int visited[51][51];

void dfs(){ // 0:북 1:동 2:남 3:서

    for (int i = 0; i < 4; ++i) {

        int nd=(d+4-(i+1))%4; // 3 2 1 0 3 2 1 0 ...
        int nr=r+dy[nd];
        int nc=c+dx[nd];
        if(nr<0 || nr>=n || nc<0 || nc>=m || mmap[nr][nc] == 1) continue;
        if(mmap[nr][nc] == 0 && !visited[nr][nc]){
            r=nr;
            c=nc;
            d=nd;
            cnt++;
            visited[r][c]= 1;
            dfs();
        }
    }
    int idx=0;
    if(d==3) idx=1; // 동쪽으로 1칸
    if(d==2) idx=0; // 북쪽으로 1칸
    if(d==1) idx=3; // 서쪽으로 1칸
    if(d==0) idx=2; // 남쪽으로 1칸

    int br=r+dy[idx];
    int bc=c+dx[idx];

    if(br>=0 && br<n && bc>=0 && bc<m){

        if(mmap[br][bc] == 0){
            r=br;
            c=bc;
            dfs();
        }
        else{
            cout<<cnt<<'\n';
            exit(0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m;
    cin>>r>>c>>d;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mmap[i][j];
        }
    }
    visited[r][c]=1;
    cnt++;
    dfs();
}