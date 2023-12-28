#include <bits/stdc++.h>
using namespace std;

#define INF 987654321;

typedef pair<int,int> pii;

int dx[4]={0,-1,0,1};
int dy[4]={-1,0,1,0};
int n,m;
int paper[501][501];
int visited[501][501];
int res;

void dfs(int y,int x,int sum,int cnt){
    if(cnt==4){
        res=max(res,sum);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int ny=y+dy[i];
        int nx=x+dx[i];
        if(ny>=n || ny<0 || nx>=m || nx<0) continue;
        if(!visited[ny][nx]) {
            if(cnt==2){
                visited[ny][nx]=true;
                dfs(y,x,sum + paper[ny][nx],cnt+1);
                visited[ny][nx]=false;
            }
            visited[ny][nx]=true;
            dfs(ny,nx,sum + paper[ny][nx],cnt+1);
            visited[ny][nx]=false;
        }
    }
}

int main() {
    cin>>n>>m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>paper[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = i; k < i+4; ++k) {
                for (int l = j; l < j+4; ++l) {
                    visited[i][j]=false;
                }
            }
            visited[i][j]=true;
            dfs(i,j,paper[i][j],1);
            visited[i][j]=false;
        }
    }
    cout<<res<<'\n';
}