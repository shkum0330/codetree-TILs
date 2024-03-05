#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007
typedef pair<int,int> pii;

int n,m,res;
int mmap[9][9];
bool visited[9][9];
vector<pii> piece;
vector<pair<pii,int>> v;
int dy[4]={0,-1,0,1};
int dx[4]={-1,0,1,0};

int count_space(){
    int ret=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(mmap[i][j]==6) continue;
            if(!visited[i][j]) ret++;
        }
    }
    return ret;
}


void move_piece(int y, int x, int d){
    while (y>=0 && y<n && x>=0 && x<m){
        visited[y][x]=true;
        if(mmap[y][x]==6) break;
        y += dy[d];
        x += dx[d];
    }
}

void dfs(int idx){
    if(idx==piece.size()){

        for (int i = 0; i < v.size(); ++i) {
            int y=v[i].first.first; int x=v[i].first.second;
            if(mmap[y][x]==1){
                int dir=v[i].second;
                move_piece(y, x, dir);
            }
            if(mmap[y][x]==2){
                int dir[2];
                dir[0]=v[i].second;
                dir[1]=dir[0]+2;
                for (int j = 0; j < 2; ++j) {
                    move_piece(y,x,dir[j]);
                }
            }
            if(mmap[y][x]==3){
                int dir[4];
                dir[0]=v[i].second;
                dir[1]=dir[0]+1;
                if(dir[1]==4) dir[1]=0;
                for (int j = 0; j < 2; ++j) {
                    move_piece(y,x,dir[j]);
                }
            }

            if(mmap[y][x]==4){
                int dir[3];
                dir[0]=v[i].second;
                for (int j = 1; j < 3; ++j) {
                    dir[j]=dir[j-1]+1;
                    if(dir[j]>=4) dir[j] -= 4;
                }
                for (int j = 0; j < 3; ++j) {
                    move_piece(y,x,dir[j]);
                }
            }
            if(mmap[y][x]==5){
                for (int j = 0; j < 4; ++j) {
                    move_piece(y, x, j);
                }
            }
        }

        res=min(res, count_space());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                visited[i][j]=false;
            }
        }
    }

    // 체스말의 위치와 첫 이동 방향을 벡터에 담는다.
    if(mmap[piece[idx].first][piece[idx].second]== 1){
        for (int i = 0; i < 4; ++i) {
            v.push_back({{piece[idx].first,piece[idx].second},i});
            dfs(idx+1);
            v.pop_back();
        }
    }
    if(mmap[piece[idx].first][piece[idx].second] == 2){
        for (int i = 0; i < 2; ++i) {
            v.push_back({{piece[idx].first,piece[idx].second},i});
            dfs(idx+1);
            v.pop_back();
        }
    }
    if(mmap[piece[idx].first][piece[idx].second] == 3){
        for (int i = 0; i < 4; ++i) {
            v.push_back({{piece[idx].first,piece[idx].second},i});
            dfs(idx+1);
            v.pop_back();
        }
    }
    if(mmap[piece[idx].first][piece[idx].second] == 4){
        for (int i = 0; i < 4; ++i) {
            v.push_back({{piece[idx].first,piece[idx].second},i});
            dfs(idx+1);
            v.pop_back();
        }
    }
    if(mmap[piece[idx].first][piece[idx].second] == 5){
        v.push_back({{piece[idx].first,piece[idx].second},0});
        dfs(idx+1);
        v.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m;
    res=n*m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>mmap[i][j];
            if(mmap[i][j]>=1 && mmap[i][j]<=5) piece.push_back({i,j});
        }
    }
    if(piece.size()>0)dfs(0);
    cout<<res<<'\n';
}