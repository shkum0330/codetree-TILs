#include <bits/stdc++.h>
using namespace std;

#define INF 987654321

int n;
int s[22][22];
int res=INF;
int visited[22];
vector<int> v;

void dfs(int size,int pos){
    if(size == n / 2){
        int teamA=0; int teamB=0;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(visited[i]==true && visited[j]==true) teamA += s[i][j];
                if(visited[i]==false && visited[j]==false) teamB += s[i][j];
            }
        }
        res=min(res,abs(teamA-teamB));
        return;
    }

    for(int i=pos;i<n;i++){
            visited[i]=true;
            dfs(size+1,i+1);
            visited[i]=false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[i][j];
        }
    }

    dfs(0,1);
    cout<<res<<'\n';
}