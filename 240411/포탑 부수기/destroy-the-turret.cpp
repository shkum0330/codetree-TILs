#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
struct Turret{
    int power,time; // 공격력, 최근 공격 시간
};
int n,m,k,res;
Turret mmap[11][11];
int dy[8]={0,1,0,-1,-1,1,1,-1};
int dx[8]={1,0,-1,0,1,1,-1,-1};
bool visited[11][11];
bool attacked[11][11];
int dist[11][11];
int dir[11][11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m>>k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin>>mmap[i][j].power;
        }
    }

    for (int t = 1; t <= k; ++t) {
        int cnt=0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if(mmap[i][j].power>0) cnt++;
            }
        }
        if(cnt<2) break;
        // 1. 공격자 선정
        int a_y=-1; int a_x=-1; int power=1000000007; int time=-1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if(mmap[i][j].power==0) continue;
                if(mmap[i][j].power==power){ // 공격력이 같으면
                    if(mmap[i][j].time==time){ // 시간이 같으면
                        if(i+j == a_y + a_x){ // 행과 열의 합이 같으면
                            if(j > a_x){
                                a_y=i; a_x=j; power= mmap[i][j].power;
                                time = mmap[i][j].time;
                            }
                        }else if(i+j > a_y + a_x){
                            a_y=i; a_x=j; power= mmap[i][j].power;
                            time = mmap[i][j].time;
                        }
                    }else if(mmap[i][j].time>time){ // 최근에 공격한 포탑 찾기
                        a_y=i; a_x=j; power= mmap[i][j].power;
                        time = mmap[i][j].time;
                    }
                }else if(mmap[i][j].power<power){
                    a_y=i; a_x=j; power = mmap[i][j].power;
                    time = mmap[i][j].time;
                }
            }
        }
        mmap[a_y][a_x].time=k; // 공격 시간 설정
        mmap[a_y][a_x].power += n + m; // 공격력 설정
//        cout << a_y << ' ' << a_x << '\n';

        // 2. 피해자 선정
        int d_y=-1; int d_x=-1; power=0; time=-1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if(mmap[i][j].power==0 || (i==a_y && j==a_x)) continue;
                if(mmap[i][j].power==power){ // 공격력이 같으면
                    if(mmap[i][j].time==time){ // 시간이 같으면
                        if(i+j == d_y + d_x){ // 행과 열의 합이 같으면
                            if(j < d_x){
                                d_y=i; d_x=j; power= mmap[i][j].power;
                                time = mmap[i][j].time;
                            }
                        }else if(i+j < d_y + d_x){
                            d_y=i; d_x=j; power= mmap[i][j].power;
                            time = mmap[i][j].time;
                        }
                    }else if(mmap[i][j].time<time){ // 가장 오래전에 공격한 포탑 찾기
                        d_y=i; d_x=j; power= mmap[i][j].power;
                        time = mmap[i][j].time;
                    }
                }else if(mmap[i][j].power>power){
                    d_y=i; d_x=j; power = mmap[i][j].power;
                    time = mmap[i][j].time;
                }
            }
        }
//        cout << d_y << ' ' << d_x << '\n';

        // 2-1. 레이저 공격
        bool flag= false;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                attacked[i][j]=false;
                visited[i][j]= false;
                dist[i][j]=0;
            }
        }
        queue<pii> q;
        q.push({a_y,a_x});
        visited[a_y][a_x]=true;
        while (!q.empty()){

            int y=q.front().first;
            int x=q.front().second;
//            cout<<y<<' '<<x<<'\n';
            if(y==d_y && x==d_x){
                flag=true;
                break;
            }
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int ny=y+dy[i];
                int nx=x+dx[i];
                if(ny==n+1) ny=1;
                if(nx==m+1) nx=1;
                if(ny==0) ny=n;
                if(nx==0) nx=m;
                if(!visited[ny][nx] && mmap[ny][nx].power>0){
                    if(dist[ny][nx] != 0 && dist[ny][nx]<=dist[y][x]+1) continue;
                    visited[ny][nx]=true;
                    q.push({ny,nx});
                    dist[ny][nx]=dist[y][x]+1;
                    dir[ny][nx]=i;
                }

            }
        }
//        for (int i = 1; i <= n; ++i) {
//            for (int j = 1; j <= m; ++j) {
//                cout<<dist[i][j]<<' ';
//            }
//            cout<<'\n';
//        }
        if(flag){
            // 경로 추적
//            cout<<123<<'\n';
            int d=dist[d_y][d_x];
            int y=d_y; int x=d_x;
//            cout<<y<<' '<<x<<'\n';

            while (d > 0){
//                cout<<d<<'\n';
                int dr=(dir[y][x]+2)%4;
                int ny=y+dy[dr];
                int nx=x+dx[dr];
                if(ny==n+1) ny=1;
                if(nx==m+1) nx=1;
                if(ny==0) ny=n;
                if(nx==0) nx=m;
//                    if(ny==a_y && nx==a_x) break;
                if(!visited[ny][nx] || mmap[ny][nx].power==0) continue;
                if(dist[ny][nx]==d-1 && !attacked[ny][nx]){
                    d--;
                    if(ny==a_y && nx==a_x) break;
//                    cout<<ny<<' '<<nx<<' '<<d<<'\n';
                    mmap[ny][nx].power -= mmap[a_y][a_x].power/2;
                    attacked[ny][nx]=true;
                    y=ny; x=nx;
                    break;
                }

            }
            mmap[d_y][d_x].power -= mmap[a_y][a_x].power;
        }
        else {
//            cout<<mmap[a_y][a_x].power<<'\n';
            // 2-2. 포탄 공격
            for (int i = 0; i < 8; ++i) {
                int ny = d_y + dy[i];
                int nx = d_x + dx[i];
                if (ny == n + 1) ny = 1;
                if (nx == m + 1) nx = 1;
                if (ny == 0) ny = n;
                if (nx == 0) nx = m;
                if(ny==a_y && nx==a_x) continue;
                if (mmap[ny][nx].power == 0) continue;
                attacked[ny][nx]=true;
                mmap[ny][nx].power -= mmap[a_y][a_x].power / 2;
            }
            mmap[d_y][d_x].power -= mmap[a_y][a_x].power;

        }
        // 3. 포탑 부서짐
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                mmap[i][j].power=max(mmap[i][j].power,0);
            }
        }

        // 4. 포탑 정비
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if(i==a_y && j==a_x) continue;
                if(i==d_y && j==d_x) continue;
                if(attacked[i][j] || mmap[i][j].power==0) continue;
                mmap[i][j].power++;
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
//                cout<<mmap[i][j].power<<' ';
                if(mmap[i][j].power==0) continue;
                res=max(res,mmap[i][j].power);
            }
//            cout<<'\n';
        }
//        cout<<'\n';
    }
    cout<<res<<'\n';
}