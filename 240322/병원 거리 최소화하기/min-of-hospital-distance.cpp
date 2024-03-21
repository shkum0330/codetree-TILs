#include <bits/stdc++.h>
using namespace std;

#define MAX 50
#define INF 1999999999

int n,m;
int res=INF;
int field[51][51];
vector<pair<int,int>> house,chicken;
bool visited[14];

void dfs(int idx,int selected){

    if(selected==m){
        int tmp=0;
        for(int i=0;i<house.size();i++) {
            int dist=INF;
            for(int j=0;j<chicken.size();j++){
                if(visited[j]) dist=min(dist,abs(house[i].first-chicken[j].first)+abs(house[i].second-chicken[j].second));

            }
            tmp += dist;
        }
        res= min(res,tmp);
        return;
    }

    if(idx==chicken.size()) return;

    visited[idx]=true;
    dfs(idx+1,selected+1);
    visited[idx]= false;
    dfs(idx+1,selected);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
            if(field[i][j]==1) house.push_back({i,j});
            else if(field[i][j]==2) chicken.push_back({i,j});
        }
    }
    dfs(0,0);
    cout<<res<<'\n';
}