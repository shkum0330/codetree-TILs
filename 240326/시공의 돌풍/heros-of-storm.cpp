#include <iostream>
using namespace std;

int n,m,t,res;
int mmap[51][51],tmp[51][51];
int dy[4]={0,-1,0,1};
int dx[4]={-1,0,1,0};
pair<int,int> cleaner[2];

void move_right(int y,int x){
    for(int i=m-1;i>1;i--){
        mmap[y][i]=mmap[y][i-1];
    }
    mmap[y][1]=0;
}
void move_left(int y,int x){
    for(int i=0;i<m;i++){
        mmap[y][i]=mmap[y][i+1];
    }
}
void move_up(int y,int x,int boundary){
    for(int i=y;i<boundary;i++){
        if(mmap[i][x]==-1) continue;
        mmap[i][x]=mmap[i+1][x];
    }
}
void move_down(int y,int x,int boundary){
    for(int i=y;i>boundary;i--){
        if(mmap[i][x]==-1) continue;
        mmap[i][x]=mmap[i-1][x];
    }
}
int main() {
    cin>>n>>m>>t;
    int idx=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mmap[i][j];
            if(mmap[i][j]==-1) cleaner[idx++]={i,j};
        }
    }

    while(t--){
        // 먼지 확산
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                tmp[i][j]=mmap[i][j];
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mmap[i][j]==-1 || mmap[i][j]==0) continue;
                int diff= tmp[i][j]/5;
                for(int k=0;k<4;k++){
                    int ny=i+dy[k];
                    int nx=j+dx[k];
                    if(ny>=n || ny<0 || nx>=m || nx<0) continue;
                    if(mmap[ny][nx]==-1) continue;
                    mmap[ny][nx] += diff;
                    mmap[i][j] -= diff;

                }
            }
        }
        // 윗부분 청소 시작
        int y=cleaner[0].first;
        int x=cleaner[0].second;
        move_down(y,x,0);
        move_left(0,0);
        move_up(0,m-1,y);
        move_right(y,m-1);
        // 아랫부분 청소 시작
        y=cleaner[1].first;
        x=cleaner[1].second;
        move_up(y,x,n-1);
        move_left(n-1,0);
        move_down(n-1,m-1,y);
        move_right(y,m-1);
    }

     for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // cout<<mmap[i][j]<<' ';
            if(mmap[i][j]==-1) continue;
            res+=mmap[i][j];
        }
        // cout<<'\n';
    }

    cout<<res<<'\n';
}