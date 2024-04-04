#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Player{
    int y,x,d;
};
int n,k,res;
int board[13][13];
vector<int> tower[13][13];
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
map<int, Player> m;

bool check(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tower[i][j].size()>=4) return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>k;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }
    for(int i=0;i<k;i++){
        int y,x,d; cin>>y>>x>>d;
        m[i]={y-1,x-1,d-1};
        tower[y-1][x-1].push_back(i);
    }

    bool flag=true;
    while(flag && res<=1000){
        res++;
        for(int i=0;i<m.size();i++){  // 순서대로 말 이동

            int d=m[i].d;
            int y=m[i].y;
            int x=m[i].x;
            int ny=y+dy[d];
            int nx=x+dx[d];
            vector<int> tmp=tower[y][x];

            if(board[ny][nx]==2 || (ny>=n || ny<0 || nx>=n || nx<0)){ // 다음 칸이 파랑이거나 체스판을 벗어난 경우
                // 반대방향 이동 가능한지 체크
                if(d%2==0) d++;
                else if(d%2==1) d--;
                int ty= y + dy[d];
                int tx= x + dx[d];
                m[i].d=d;
                if(board[ty][tx]==2 || ty>=n || ty<0 || tx>=n || tx<0){ // 이동이 불가능하면
                    continue;
                }
                int idx=-1;
                for(int j=0;j<tmp.size();j++){ // 말 찾기
                    if(tmp[j]==i){
                        idx=j;
                        break;
                    }
                }
                for(int j=idx;j<tmp.size();j++){ // 위에 있는 말 전부 이동
                    m[tmp[j]].y=ty;
                    m[tmp[j]].x=tx;
                    tower[ty][tx].push_back(tmp[j]);
                }
                tower[y][x].erase(tower[y][x].begin()+idx,tower[y][x].end());

                if(board[ty][tx]==1) {
                    idx = -1;
                    for (int j = 0; j < tower[ty][tx].size(); j++) { // 옮긴 후 해당 말을 찾아서
                        if (tower[ty][tx][j] == i) {
                            idx = j;
                        }
                    }
                    std::reverse(tower[ty][tx].begin() + idx, tower[ty][tx].end()); // 위에 있는 말들과 뒤집어준다.
                }

                if(tower[ty][tx].size()>=4){
                    flag=false;
                    break;
                }
                continue;
            }

            if(board[ny][nx]==0){ // 다음 칸이 흰색일때
                int idx=-1;
                for(int j=0;j<tmp.size();j++){ // 해당 말을 찾아서
                    if(tmp[j]==i){
                        idx=j;
                    }
                }
                for(int j=idx;j<tmp.size();j++){ // 위에 있는 말 전부 이동
                    m[tmp[j]].y=ny;
                    m[tmp[j]].x=nx;
                    tower[ny][nx].push_back(tmp[j]);
                }
                tower[y][x].erase(tower[y][x].begin()+idx,tower[y][x].end());

                if(tower[ny][nx].size()>=4){
                    flag=false;
                    break;
                }
            }

            if(board[ny][nx]==1){ // 다음 칸이 빨강일때
                int idx=-1;
                for(int j=0;j<tmp.size();j++){ // 해당 말을 찾아서
                    if(tmp[j]==i){
                        idx=j;
                    }
                }
                for(int j=idx;j<tmp.size();j++){ // 위에 있는 말 전부 이동
                    m[tmp[j]].y=ny;
                    m[tmp[j]].x=nx;
                    tower[ny][nx].push_back(tmp[j]);
                }

                if(tower[ny][nx].size()>=4){
                    flag=false;
                    break;
                }

                tower[y][x].erase(tower[y][x].begin()+idx,tower[y][x].end());

                idx=-1;
                for(int j=0;j<tower[ny][nx].size();j++){ // 옮긴 후 해당 말을 찾아서
                    if(tower[ny][nx][j]==i){
                        idx=j;
                    }
                }
                std::reverse(tower[ny][nx].begin()+idx,tower[ny][nx].end()); // 위에 있는 말들과 뒤집어준다.

            }
        }
    }
    if(res>1000) cout<<-1<<'\n';
    else cout<<res<<'\n';
}