#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

int n,res,min_x,min_y,min_dist,eat;
int size_of_robot=2;
int mmap[21][21];
int dist[21][21];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,1,-1};
queue<pii> q;

void bfs(int y,int x){
    dist[y][x]=0;
    q.push({y,x});
    while (!q.empty()){
        int y=q.front().first;
        int x=q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny=y+dy[i];
            int nx=x+dx[i];
            if (ny>=n || ny<0 || nx>=n || nx<0) continue;
            if(dist[ny][nx] != -1 || mmap[ny][nx] > size_of_robot) continue;
            dist[ny][nx]=dist[y][x]+1;

            if(mmap[ny][nx] != 0 && mmap[ny][nx] < size_of_robot){
                if(min_dist>dist[ny][nx]){
                    min_dist=dist[ny][nx];
                    min_y=ny;
                    min_x=nx;
                }else if(min_dist==dist[ny][nx]){
                    if(min_y==ny){
                        if(min_x>nx) {
                            min_y = ny;
                            min_x = nx;
                        }
                    }else if(min_y>ny){
                        min_y=ny;
                        min_x=nx;
                    }
                }
            }
            q.push({ny,nx});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    int startX,startY;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mmap[i][j];
            if(mmap[i][j] == 9){
                startY=i;
                startX=j;
                mmap[i][j]=0;
            }
        }
    }

    while (true){
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j]=-1;
            }
        }
        min_dist = 9999;
        min_x = 21;
        min_y = 21;
        bfs(startY,startX);
        if(min_x != 21 && min_y != 21){
            res += dist[min_y][min_x];
            eat++;
            mmap[min_y][min_x]=0;
            startY=min_y;
            startX=min_x;
            if(eat == size_of_robot){
                size_of_robot++;
                eat=0;
            }
        } else break;

    }
    cout<<res;
}