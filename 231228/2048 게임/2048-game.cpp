#include <bits/stdc++.h>
using namespace std;

#define INF 1987654321

int n;
vector<vector<int>> mmap;
int res;

void dfs(int cnt,int dir,vector<vector<int>> arr){ // 0123 상하좌우
    if(cnt==5){
        return;
    }
    bool visited[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[i][j]=false;
        }
    }
    if(dir==0){ // 상
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; j++) {
                if(arr[j][i]==0) continue;
                int y=j;
                while (y > 0){
                    if(arr[y-1][i] == 0){ // 뒤가 0일때 그냥 이동
                        arr[y-1][i]=arr[y][i];
                        arr[y][i]=0;
                        y--;
                    }
                    else if(arr[y][i] != 0 && arr[y-1][i] == arr[y][i]){ // 뒤가 같을때 뒤에걸 2배
                        if(!visited[y-1][i] && !visited[y][i]) {
                            visited[y-1][i]=true;
                            arr[y - 1][i] *= 2;
                            arr[y][i] = 0;
                            y--;
                        } else break;
                    }
                    else if(arr[y][i] != 0 && arr[y-1][i] != arr[y][i]){ // 뒤랑 다를때 멈춤
                        break;
                    }
                }

            }
        }
    }
    if(dir==1){ // 하
        for (int i = 0; i < n; ++i) {
            for (int j = n-2; j >= 0; j--) {
                if(arr[j][i]==0) continue;
                int y=j;
                while (y < n - 1){
                    if(arr[y+1][i] == 0){ // 뒤가 0일때 이동
                        arr[y+1][i]=arr[y][i];
                        arr[y][i]=0;
                        y++;
                    }
                    else if(arr[y][i] != 0 && arr[y+1][i] == arr[y][i]){ // 뒤가 같을때 뒤에걸 2배
                        if(!visited[y+1][i] && !visited[y][i]) {
                            visited[y+1][i]= true;
                            arr[y + 1][i] *= 2;
                            arr[y][i] = 0;
                            y++;
                        } else break;
                    }
                    else if(arr[y][i] != 0 && arr[y+1][i] != arr[y][i]){ // 뒤랑 다를때 멈춤
                        break;
                    }
                }
            }
        }
    }
    if(dir==2){ // 좌
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; j++) {
                if(arr[i][j]==0) continue;
                int x=j;
                while (x>0){
                    if(arr[i][x-1]==0){ // 뒤가 0일때 이동
                        arr[i][x-1]=arr[i][x];
                        arr[i][x]=0;
                        x--;
                    }
                    else if(arr[i][x]!=0 && arr[i][x-1]==arr[i][x]){ // 뒤가 같을때 뒤에걸 2배
                        if(!visited[i][x-1] && !visited[i][x]) {
                            visited[i][x-1]=true;
                            arr[i][x - 1] *= 2;
                            arr[i][x] = 0;
                            x--;
                        } else break;
                    }
                    else if(arr[i][x]!=0 && arr[i][x-1]!=arr[i][x]){ // 뒤랑 다를때 멈춤
                        break;
                    }
                }
            }
        }
    }
    if(dir==3){ // 우
        for (int i = 0; i < n; ++i) {
            for (int j = n-2; j >= 0; j--) {
                if(arr[i][j]==0) continue;
                int x=j;
                while (x<n-1){
                    if(arr[i][x+1]==0){ // 뒤가 0일때 이동
                        arr[i][x+1]=arr[i][x];
                        arr[i][x]=0;
                        x++;
                    }
                    else if(arr[i][x]!=0 && arr[i][x+1]==arr[i][x]){ // 뒤가 같을때 뒤에걸 2배
                        if(!visited[i][x+1] && !visited[i][x]) {
                            visited[i][x+1]=true;
                            arr[i][x + 1] *= 2;
                            arr[i][x] = 0;
                            x++;
                        } else break;
                    }
                    else if(arr[i][x]!=0 && arr[i][x+1]!=arr[i][x]){ // 뒤랑 다를때 멈춤
                        break;
                    }
                }
            }
        }
    }
    
    vector<vector<int>> copyarr;
    for (int i = 0; i < n; ++i) {
        vector<int> tmp;
        for (int j = 0; j < n; ++j) {
            tmp.push_back(arr[i][j]);
            res=max(res,arr[i][j]);
        }
        copyarr.push_back(tmp);
    }

    for (int i = 0; i < 4; ++i) {
        dfs(cnt+1,i,copyarr);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for (int i = 0; i < n; ++i) {
        vector<int> tmp;
        for (int j = 0; j < n; ++j) {
            int num; cin>>num;
            tmp.push_back(num);
        }
        mmap.push_back(tmp);
    }

    for (int i = 0; i < 4; ++i) {
        vector<vector<int>> copyarr;
        for (int j = 0; j < n; ++j) {
            vector<int> tmp;
            for (int k = 0; k < n; ++k) {
                tmp.push_back(mmap[j][k]);
            }
            copyarr.push_back(tmp);
        }
        dfs(0,i,copyarr);
    }
    cout<<res<<'\n';
}