#include <bits/stdc++.h>
using namespace std;

#define INF 987654321

typedef long long ll;
typedef pair<int,int> pii;

struct mold {
    int r, c, speed, dir, size; // r,c,속력,방향(1234 상하우좌),크기
    bool dead; // 죽었는지 여부
};

int r,c,m,res;
vector<mold> molds;
int dy[4]={-1,1,0,0};
int dx[4]={0,0,1,-1};
priority_queue<pii,vector<pii>,greater<pii>> pq[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>r>>c>>m;
    for (int i = 0; i < m; ++i) {
        mold mold;
        cin >> mold.r >> mold.c >> mold.speed >> mold.dir >> mold.size;
        mold.dead=false;
        molds.push_back(mold);
        pq[mold.r][mold.c].push({mold.size, i}); // {사이즈, 인덱스} 저장
    }
    int div=r+c;
    for (int i = 1; i <=c ; ++i) {
        for (int j = 1; j <= r; ++j) {
            if(!pq[j][i].empty()){
                res += pq[j][i].top().first;
                molds[pq[j][i].top().second].dead=true;
                pq[j][i].pop();
                break;
            }
        }

        for (int j = 1; j <= r; ++j) {
            for (int k = 1; k <= c; ++k) {
                while (!pq[j][k].empty()) pq[j][k].pop();
            }
        }

        for (int j=0; j < molds.size(); j++) {
            if(molds[j].dead) continue;
            int dist;
            if(molds[j].dir == 1 || molds[j].dir == 2){
                dist= molds[j].speed % (r * 2 - 2);
            }
            if(molds[j].dir == 3 || molds[j].dir == 4){
                dist= molds[j].speed % (c * 2 - 2);
            }
            for (int k = 0; k < dist; ++k) {
                // 방향 설정
                if(molds[j].r == 1 && molds[j].dir == 1){
                    molds[j].dir=2;
                }
                if(molds[j].r == r && molds[j].dir == 2){
                    molds[j].dir=1;
                }
                if(molds[j].c == 1 && molds[j].dir == 4){
                    molds[j].dir=3;
                }
                if(molds[j].c == c && molds[j].dir == 3){
                    molds[j].dir=4;
                }

                molds[j].r += dy[molds[j].dir - 1];
                molds[j].c += dx[molds[j].dir - 1];
            }
            pq[molds[j].r][molds[j].c].push({molds[j].size, j});
        }

        for (int j = 1; j <= r; ++j) {
            for (int k = 1; k <= c; ++k) {
                if(!pq[j][k].empty() && pq[j][k].size()>1){
                    while (pq[j][k].size()!=1){
                        molds[pq[j][k].top().second].dead=true;
                        pq[j][k].pop();
                    }
                }
            }
        }
    }

    cout<<res<<'\n';
}