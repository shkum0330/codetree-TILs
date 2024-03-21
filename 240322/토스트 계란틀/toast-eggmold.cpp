#include <bits/stdc++.h>
using namespace std;

int n,l,r,res;

int mmap[51][51];
bool visited[51][51];
int dy[4]={0,-1,0,1};
int dx[4]={-1,0,1,0};


void bfs(int y,int x){
    int sum=0;
    int cnt=0;
    queue<pair<int,int>> q;
    q.push({y,x});

    while(!q.empty()){
        cnt++;
        visited[y][x]=true;
        int y=q.front().first;
        int x=q.front().second;
        sum += mmap[y][x];
        q.pop();
        
        for(int i=0;i<4;i++){
            int ny=y+dy[i];
            int nx=x+dx[i];
            if(ny>=n || ny<0 || nx>=n || nx<0) continue;
            int diff=abs(mmap[ny][nx]-mmap[y][x]);
            if(!visited[ny][nx] && diff>=l && diff<=r){
                visited[ny][nx]=true;
                q.push({ny,nx});
            }
        }
    }
    if(cnt>1){
        int num= sum/cnt;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(visited[i][j]) mmap[i][j]=num;
            }
        }
    }

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>l>>r;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mmap[i][j];
        }
    }

    bool flag=true;
 
    while(true){
        int cnt=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                visited[i][j]=false;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!visited[i][j]){
                    bfs(i,j);
                    cnt++;
                }
            }
        }
        if(cnt==n*n) break;
        res++;
    }

    cout<<res<<'\n';
    return 0;
}