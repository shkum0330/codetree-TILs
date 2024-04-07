#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Player{
    int y,x,d,s;
    int g=0;
    int point=0;
};
int n,m,k;
vector<int> mmap[21][21];
vector<Player> p;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
map<pair<int,int>, int> mp; // key: 위치, value: 플레이어 번호

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m>>k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int g; cin>>g;
            mmap[i][j].push_back(g);
            mp[{i,j}]=-1;
        }
    }

    for (int i = 0; i < m; ++i) {
        int y,x,d,s;
        cin>>y>>x>>d>>s;
        p.push_back({y-1,x-1,d,s});
        mp[{y-1,x-1}]=i;
    }

    while (k--){
        for (int i = 0; i < p.size(); ++i) { // 1.1. 이동
            int ny=p[i].y+dy[p[i].d];
            int nx=p[i].x+dx[p[i].d];
            if(ny>=n || ny<0 || nx>=n || nx<0){
                p[i].d=(p[i].d+2)%4;
                ny=p[i].y+dy[p[i].d];
                nx=p[i].x+dx[p[i].d];
            }

            mp[{p[i].y,p[i].x}]=-1;
            p[i].y=ny;
            p[i].x=nx;
            sort(mmap[ny][nx].begin(),mmap[ny][nx].end(),greater<>());
            if(mp[{ny,nx}]==-1){ // 사람이 아무도 없을땐, 총을 먹는다.
                for (int j =0; j < mmap[ny][nx].size(); ++j) {
                    if(p[i].g<mmap[ny][nx][j]){ // 2-1. 총 먹기
                        int damage=p[i].g;
                        p[i].g=mmap[ny][nx][j];
                        mmap[ny][nx].erase(mmap[ny][nx].begin()+j);
                        mmap[ny][nx].push_back(damage);
                        break;
                    }
                }
                mp[{ny,nx}]=i;
            }else{ // 2.2. 사람이 있는 경우
                int enemy_idx=mp[{ny,nx}];
                Player enemy=p[enemy_idx];
                int winner=-1;
                int loser=-1;
                if(p[i].s+p[i].g == enemy.s+enemy.g){
                    if(p[i].s > enemy.s){
                        winner=i;
                        loser=enemy_idx;
                    }else{
                        winner=enemy_idx;
                        loser=i;
                    }
                }else if(p[i].s+p[i].g > enemy.s+enemy.g){
                    winner=i;
                    loser=enemy_idx;
                }else if(p[i].s+p[i].g < enemy.s+enemy.g){
                    winner=enemy_idx;
                    loser=i;
                }
                p[winner].point += abs((p[i].s+p[i].g) - (enemy.s+enemy.g));

                // 진 사람 총 내려놓고 이동
                mmap[ny][nx].push_back(p[loser].g);
                p[loser].g=0;

                int ty=p[loser].y+dy[p[loser].d];
                int tx=p[loser].x+dx[p[loser].d];
                if(ty>=n || ty<0 || tx>=n || tx<0){
                    p[loser].d=(p[loser].d+1)%4; // 90도 회전
                    ty=p[loser].y+dy[p[loser].d];
                    tx=p[loser].x+dx[p[loser].d];
                }

                sort(mmap[ty][tx].begin(),mmap[ty][tx].end(),greater<>());
                for (int j =0; j < mmap[ty][tx].size(); ++j) {
                    if(p[loser].g<mmap[ty][tx][j]){ // 총 먹기
                        int damage=p[loser].g;
                        p[loser].g=mmap[ty][tx][j];
                        mmap[ty][tx].erase(mmap[ty][tx].begin()+j);
                        mmap[ty][tx].push_back(damage);
                        break;
                    }
                }
                p[loser].y=ty;
                p[loser].x=tx;
                mp[{ty,nx}]=loser;

                // 이긴 사람 포인트 획득
                sort(mmap[ny][nx].begin(),mmap[ny][nx].end(),greater<>());
                for (int j =0; j < mmap[ny][nx].size(); ++j) {
                    if(p[winner].g<mmap[ny][nx][j]){ // 총 먹기
                        int damage=p[winner].g;
                        p[winner].g=mmap[ny][nx][j];
                        mmap[ny][nx].erase(mmap[ny][nx].begin()+j);
                        mmap[ny][nx].push_back(damage);
                        break;
                    }
                }
                mp[{ny,nx}]=winner;

            }
        }
    }

    for (auto l:p) {
        cout<<l.point<<' ';
    }
    cout<<'\n';
}