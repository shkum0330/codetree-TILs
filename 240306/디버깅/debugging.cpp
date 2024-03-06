#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007
typedef pair<int,int> pii;

int n,m,h,boundary;
int res=INF;
bool linked[31][11][11];
bool flag;

bool move(int start_x){
    int x=start_x;
    int y=h;
    while (y>0){
        if(linked[y][x-1][x]){
            x--;
            y--;
            continue;
        }
        if(linked[y][x][x+1]){
            x++;
            y--;
            continue;
        }
        y--;
    }

    if(x == start_x) return true;
    else return false;
}

bool check(){
    for (int i = 1; i <= n; ++i) {
        if(!move(i)){
            return false;
        }
    }
    return true;
}

void dfs(int y,int cnt){
    if(cnt==boundary){
        if(check()){
            flag=true;
        }
        return;
    }

    for (int i = y; i <= h; ++i) {
        for (int j = 1; j < n; ++j) {
            if(linked[i][j][j+1] || linked[i][j-1][j]) continue;
            linked[i][j][j+1]=true;
            dfs(i,cnt+1);
            linked[i][j][j+1]=false;
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m>>h;
    for (int i = 0; i < m; ++i) {
        int a,b; cin>>a>>b;
        linked[a][b][b+1]=true;
    }

    for (int i = 0; i <= 3; ++i) {
        boundary=i;
        dfs(0,0);
        if(flag){
            cout<<i<<'\n';
            return 0;
        }
    }

    cout<<-1<<'\n';
}