#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define INF 0x7fffffff

typedef pair<int,int> pii;

int n,res;
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
bool visited[102][102];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n;

    for (int i = 0; i < n; ++i) {
        vector<pii> points;
        int y,x,d,g; cin>>y>>x>>d>>g;

        points.push_back({x,y});
        points.push_back({x+dx[d],y+dy[d]});

        for (int j = 0; j < g; ++j) {
            int size=points.size();
            pii center={points[size-1].first,points[size-1].second};

            for (int k = size-2; k >= 0; k--) {
                points.push_back({-1*(points[k].second-center.second)+center.first,points[k].first-center.first+center.second});
            }
        }


        for(auto& p:points){
            if(p.first>100 || p.first<0 || p.second>100 || p.second<0) continue;
            visited[p.second][p.first]=true;
        }

    }

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if(visited[i][j] && visited[i+1][j] && visited[i][j+1] && visited[i+1][j+1]) res++;
        }
    }
    cout<<res<<'\n';
}