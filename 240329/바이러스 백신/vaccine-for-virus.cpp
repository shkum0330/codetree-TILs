#include <bits/stdc++.h>
using namespace std;

int n,m;
int res=987654321;
bool flag=false;
int mmap[51][51];
int dist[51][51];
bool visited[51][51];
bool tmp_visited[51][51];
int dy[4]={-1,0,1,0};
int dx[4]={0,-1,0,1};
vector<pair<int,int>> hospital;
vector<int> v;

bool check(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mmap[i][j]==1 || mmap[i][j]==2) continue;
            else if(!visited[i][j]) return false;
        }
    }
    return true;
}

void bfs(int y,int x){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tmp_visited[i][j]=false;
        }
    }
    queue<pair<int,int>> q;
    q.push({y,x});
    tmp_visited[y][x]=true;
    visited[y][x]=true;
    dist[y][x]=0;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second;
        q.pop();
        // cout<<y<<' '<<x<<'\n';
        for(int i=0;i<4;i++){
            int ny=y+dy[i];
            int nx=x+dx[i];

            if(ny>=n || ny<0 || nx>=n || nx<0) continue;
            
            if(!tmp_visited[ny][nx] && mmap[ny][nx]!=1 ){
                // cout<<ny<<' '<<nx<<'\n';
                if(dist[ny][nx]==0) dist[ny][nx]=dist[y][x]+1;
                else dist[ny][nx]=min(dist[y][x]+1,dist[ny][nx]);
     
                q.push({ny,nx});
                tmp_visited[ny][nx]=true;
                visited[ny][nx]=true;
   
            }
        }
    }
}
void combi(int idx){
    if(v.size()==m){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                dist[i][j]=0;
                visited[i][j]=false;
            }
        }
        for(int i=0;i<m;i++){
            bfs(hospital[v[i]].first,hospital[v[i]].second);
        }
       
        for(int i=0;i<hospital.size();i++){
            dist[hospital[i].first][hospital[i].second]=0;
        }

        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //         cout<<dist[i][j]<<' ';
        //     }
            // cout<<'\n';
        // }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //         cout<<visited[i][j]<<' ';
        //     }
        //     cout<<'\n';
        // }

        if(check()){

            flag=true;
            int tmp=0;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(mmap[i][j]==1) continue;
                    tmp=max(tmp,dist[i][j]);
                }
            }

            res=min(res,tmp);
        }
        return;
    }
    for(int i=idx+1;i<hospital.size();i++){
        // cout<<i<<'\n';
        v.push_back(i);
        combi(i);
        v.pop_back();
    }
}
int main() {
    cin>>n>>m;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> mmap[i][j];
            if(mmap[i][j]==2) hospital.push_back({i,j});
        }
    }

    for(int i=0;i<=hospital.size()-m;i++){
        v.push_back(i);
        combi(i);
        v.pop_back();
    }
    if(!flag) cout<<-1<<'\n';
    else cout<<res<<'\n';
}