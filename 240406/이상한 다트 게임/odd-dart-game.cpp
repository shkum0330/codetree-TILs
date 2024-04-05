#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

int n,m,t,x,d,k,res;
int plate[51][51];
int dr[4]={-1,1,0,0};
int dc[4]={0,0,-1,1};
bool flag,check;


void dfs(int r, int c, bool init,int num){
    if(plate[r][c]==0) return;

    if(!init){
        flag=true;
        check=true;
        plate[r][c]=0;
    }

    for (int i = 0; i < 4; ++i) {
        int nr=r+dr[i];
        int nc=c+dc[i];
        if(nr>n || nr<=0) continue;
        if(nc==0) nc=m;
        else if(nc==m+1) nc=1;
        if(plate[nr][nc] == num) {

            dfs(nr, nc,false,num);
        }
    }
}
void calc(){
    double sum=0;
    double cnt=0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if(plate[i][j]==0) continue;
            sum += plate[i][j];
            cnt++;
        }
    }

    double avg=sum/cnt;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if(plate[i][j]==0) continue;
            if(plate[i][j]>avg) plate[i][j]--;
            else if(plate[i][j]<avg) plate[i][j]++;
        }
    }


}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin>>n>>m>>t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin>>plate[i][j];
        }
    }

    while (t--){
        cin>>x>>d>>k; // x의 배수인 원판을 d방향(0: 시계방향, 1: 반시계방향)으로 k칸 회전시킨다

        for (int i = x; i <= n; i+=x) {
            int num=k;
            if(d==0){
                while (num--) {

                    int tmp = plate[i][m];
                    for (int j = m; j > 0; j--) {
                        plate[i][j] = plate[i][j - 1];
                    }
                    plate[i][1] = tmp;
                }
            }
            if(d==1){
                while (num--) {
                    int tmp = plate[i][1];
                    for (int j = 1; j < m; ++j) {
                        plate[i][j] = plate[i][j + 1];
                    }
                    plate[i][m] = tmp;
                }
            }
        }

        check= false;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if(plate[i][j]==0) continue;
                flag = false;
                dfs(i,j,true,plate[i][j]);

                if(flag) plate[i][j]=0;
            }
        }

        if(!check) calc();
    }



    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            res += plate[i][j];
        }
    }
    cout<<res<<'\n';
}