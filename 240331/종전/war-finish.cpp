#include <bits/stdc++.h>
using namespace std;

int n;
int res=987654321;
int mmap[21][21];
int dy[4]={-1,-1,1,1};
int dx[4]={1,-1,-1,1};
bool border[21][21];
int total_sum;
int part_sum[5];

bool check(int y,int x){
    return x>=0 && x<n && y>=0 && y<n;
}

void solve(int y,int x,int d1,int d2){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            border[i][j] = false;
        }
    }
    
    for(int i=0;i<5;i++){
        part_sum[i]=0;
    }

    int move_cnt[4]={d1,d2,d1,d2};

    // 경계
    for(int i=0;i<4;i++){
        for(int j=0;j<move_cnt[i];j++){
            y += dy[i];
            x += dx[i];
            border[y][x]=true;
        }
    }

    // 좌측 상단
    for(int i=0;i<y-d2;i++){
        for(int j=0;j<=x+d1-d2;j++){
            if(border[i][j]) break;
            part_sum[0] += mmap[i][j];
        }
    }


    // 좌측 하단
    for(int i=y-d2;i<n;i++){
        for(int j=0;j<x;j++){
            if(border[i][j]) break;
            part_sum[1] += mmap[i][j];
        }
    }

    // 우측 하단
    for(int i=y-d1+1;i<n;i++){
        for(int j=n-1;j>=x;j--){
            if(border[i][j]) break;
            part_sum[2] += mmap[i][j];
        }
    }

    // 우측 상단
    for(int i=0;i<=y-d1;i++){
        for(int j=n-1;j>x+d1-d2;j--){
            if(border[i][j]) break;
            part_sum[3] += mmap[i][j];
        }
    }
    
    part_sum[4]=total_sum;
    for(int i=0;i<4;i++){
        part_sum[4] -= part_sum[i];
    }
    sort(part_sum,part_sum+5);

    res=min(res,part_sum[4]-part_sum[0]);
}

int main() {
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mmap[i][j];
            total_sum += mmap[i][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int d1=1;d1<n;d1++){
                for(int d2=1;d2<n;d2++){
                    if(check(i-d1,j+d1) && check(i-d1-d2,j+d1-d2) && check(i-d2,j-d2)){
                        solve(i,j,d1,d2);
                    }
                }
            }
        }
    }

    cout<<res<<'\n';
}