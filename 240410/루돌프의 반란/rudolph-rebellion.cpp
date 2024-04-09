#include <bits/stdc++.h>
using namespace std;

struct Santa{
    int y,x;
    int time=0;
    int point=0;
    bool faint,out;
};
int n,m,p,c,d;
int mmap[51][51];
int point[31];
pair<int,int> r; // 루돌프
Santa s[31]; // 산타
int ry[8]={-1,-1,0,1,1,1,0,-1};
int rx[8]={0,1,1,1,0,-1,-1,-1};
int sy[4]={-1,0,1,0};
int sx[4]={0,1,0,-1};

bool check(){
    for (int i = 1; i <= p; ++i) {
        if(!s[i].out) return false;
    }
    return true;
}
int get_dist(pair<int,int> a, pair<int,int> b){
    return pow(a.first-b.first,2)+pow(a.second-b.second,2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m>>p>>c>>d; // c: 산타의 힘 d: 루돌프의 힘
    cin>>r.first>>r.second;
    mmap[r.first][r.second]=-1;
    for (int i = 0; i < p; ++i) {
        int num,y,x; cin>>num>>y>>x;
        s[num]={y,x,0,0, false,false};
        mmap[y][x]=num;
    }

    while (m--){

        if(check()) break; // 산타가 모두 나갔는지 확인

        // 루돌프 이동
        int dist=100000007; int idx=-1;
        for (int i = 1; i <= p; ++i) {
            if(s[i].out) {
                // cout<<i<<'\n';
                continue;
            }
            if(dist == get_dist(r,{s[i].y,s[i].x})){
                if(s[idx].y==s[i].y){
                    if(s[idx].x<s[i].x){
                        idx=i;
                    }
                }else if(s[idx].y<s[i].y){
                    idx=i;
                }
            } else if(dist > get_dist(r,{s[i].y,s[i].x})){
                dist=get_dist(r,{s[i].y,s[i].x});
                idx=i;
            }
        }

//        cout<<s[idx].num<<'\n';
        dist=get_dist(r,{s[idx].y,s[idx].x});
        int r_move_idx=0;
        for (int i = 0; i < 8; ++i) {
            int ny=r.first+ry[i];
            int nx=r.second+rx[i];
            if(ny>n || ny<=0 || nx>n || nx<=0) continue;
            if(dist>get_dist({ny,nx},{s[idx].y,s[idx].x})){
                r_move_idx=i;
                dist=get_dist({ny,nx},{s[idx].y,s[idx].x});
            }
        }
        int ny=r.first+ry[r_move_idx];
        int nx=r.second+rx[r_move_idx];
        if(mmap[ny][nx]==0){ // 그냥 이동
            mmap[r.first][r.second]=0;
            r.first=ny;
            r.second=nx;
            mmap[ny][nx]=-1;

        }else{ // 충돌
            int santa_num=mmap[ny][nx];
            s[santa_num].point+=c;
            s[santa_num].faint=true;
    
            int ty=ny + c*ry[r_move_idx];
            int tx=nx + c*rx[r_move_idx];
            s[santa_num].y=ty;
            s[santa_num].x=tx;
            mmap[r.first][r.second]=0;
            r.first=ny;
            r.second=nx;
            mmap[ny][nx]=-1;
//            cout<<ty<<' '<<tx<<'\n';

            if(ty>n || ty<=0 || tx>n || tx<=0){
                s[santa_num].out=true;
            }else {
                if(mmap[ty][tx]==0){
                    mmap[ty][tx]=santa_num;
                    s[santa_num].y=ty;
                    s[santa_num].x=tx;
                } else{
                    int tmp_santa_num=santa_num;
                    while (mmap[ty][tx] != 0){
                        s[santa_num].y=ty;
                        s[santa_num].x=tx;
                        tmp_santa_num=mmap[ty][tx];
                        mmap[ty][tx]=santa_num;
                        santa_num=tmp_santa_num;
                        ty = ty + ry[r_move_idx];
                        tx = tx + rx[r_move_idx];
                        if(ty>n || ty<=0 || tx>n || tx<=0){
                            s[tmp_santa_num].out=true;
                            break;
                        }
                    }
                    if(mmap[ty][tx] == 0){
                        s[santa_num].y=ty;
                        s[santa_num].x=tx;
                        mmap[ty][tx]=santa_num;
                    }
                }
            }
        }

        // 산타 이동
        for (int i = 1; i <= p; ++i) {
            // cout<<r.first<<' '<<r.second<<'\n';
            if(s[i].faint || s[i].out) continue;
            dist=get_dist(r,{s[i].y,s[i].x});
            int s_move_idx=0;
            for (int j = 0; j < 4; ++j) {
                int ny=s[i].y+sy[j];
                int nx=s[i].x+sx[j];
                if(ny>n || ny<=0 || nx>n || nx<=0 || mmap[ny][nx]>0) continue;
                if(dist>get_dist({ny,nx},{r.first,r.second})){
                    s_move_idx=j;
                    dist=get_dist({ny,nx},{r.first,r.second});
                }
            }
            if(dist==get_dist(r,{s[i].y,s[i].x})) continue;
            ny=s[i].y+sy[s_move_idx];
            nx=s[i].x+sx[s_move_idx];
            mmap[s[i].y][s[i].x]=0;

            if(mmap[ny][nx]==0){ // 그냥 이동
                s[i].y=ny;
                s[i].x=nx;
                mmap[ny][nx]=i;
            }else if(mmap[ny][nx]==-1){ // 충돌
                int santa_num=i;
                s[i].point+=d;
                s[i].faint= true;
                s_move_idx=(s_move_idx+2)%4;
                int ty=ny+d*sy[s_move_idx];
                int tx=nx+d*sx[s_move_idx];
      
                if(ty>n || ty<=0 || tx>n || tx<=0){
                    s[i].out=true;
                    continue;
                }
                if(mmap[ty][tx]==0){
                    s[i].y=ty;
                    s[i].x=tx;
                    mmap[ty][tx]=i;
                }else{ // 상호작용
                    int tmp_santa_num=santa_num;
                    while (mmap[ty][tx] != 0){
                        s[santa_num].y=ty;
                        s[santa_num].x=tx;
                        tmp_santa_num=mmap[ty][tx];
                        mmap[ty][tx]=santa_num;
                        santa_num=tmp_santa_num;
                        ty = ty + sy[s_move_idx];
                        tx = tx + sx[s_move_idx];
                        if(ty>n || ty<=0 || tx>n || tx<=0){
                            s[tmp_santa_num].out=true;
                            break;
                        }
                    }
                    if(mmap[ty][tx] == 0){
                        s[santa_num].y=ty;
                        s[santa_num].x=tx;
                        mmap[ty][tx]=santa_num;
                    }
                }
            }
            // cout<<r.first<<' '<<r.second<<'\n';
        }


        // 점수 계산하고 time 1 증가
        for (int i = 1; i <= p; ++i) {
            if(!s[i].out){
                s[i].point++; // 점수 증가
                if(s[i].faint) {
                    s[i].time++; // 기절 시간 증가
                    if(s[i].time==2){ // 기절 시간 2 넘었으면 기절 풀기
                        s[i].time=0;
                        s[i].faint=false;
                    }
                }

            }
        }
        // for (int i = 1; i <= n; ++i) {
        //     for (int j = 1; j <= n; ++j) {
        //         cout<<mmap[i][j]<<' ';
        //     }
        //     cout<<'\n';
        // }
        // cout<<'\n';
        // for(int i = 1; i <= p; ++i){
        //     if(!s[i].out) cout<<s[i].y<<' '<<s[i].x<<'\n';
        // }
        
    }
   for (int i = 1; i <= p; ++i) {
        cout<<s[i].point<<' ';
    }
    cout<<'\n';
}