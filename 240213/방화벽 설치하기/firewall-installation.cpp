#include <bits/stdc++.h>
using namespace std;


typedef pair<int,int> pii;

int n,m,res;
int mmap[9][9];
int copy_map[9][9];
bool wall[9][9];
bool fire_visited[9][9];
int dy[4]={0,-1,0,1};
int dx[4]={-1,0,1,0};
vector<pii> fire;

void copy(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            copy_map[i][j]=mmap[i][j];
        }
    }
}

void dfs(int y,int x){
    for (int i = 0; i < 4; ++i) {
        int ny=y+dy[i];
        int nx=x+dx[i];

        if(ny>=n || ny<0 || nx>=m || nx<0) continue;
        if(copy_map[ny][nx]==0){
            copy_map[ny][nx]=2;
            dfs(ny,nx);
        }
    }
}

int count(){
    int cnt=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(copy_map[i][j]==0)cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>mmap[i][j];
            if(mmap[i][j]==1) wall[i][j]=true;
            if(mmap[i][j]==2) {
                fire.push_back({i, j});
            }
        }
    }

    int size=n*m;

    for (int i = 0; i < size-2; ++i) {
        if(mmap[i/m][i%m] != 0) continue;
        for (int j = i+1; j < size-1; ++j) {
            if(mmap[j/m][j%m] != 0) continue;
            for (int k = j+1; k < size; ++k) {
                if(mmap[k/m][k%m] != 0) continue;
                copy();
                copy_map[i/m][i%m]=1;
                copy_map[j/m][j%m]=1;
                copy_map[k/m][k%m]=1;

                for (int l = 0; l < fire.size(); ++l) {
                    dfs(fire[l].first,fire[l].second);
                }
                res=max(res,count());
            }
        }
    }

    cout<<res<<'\n';

}