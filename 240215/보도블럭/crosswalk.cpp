#include <bits/stdc++.h>
using namespace std;

#define INF 987654321;

typedef pair<int,int> pii;

int n,x,res;
int mmap[101][101];

int main() {
    cin>> n>>x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin>>mmap[i][j];
        }
    }

    if(x==1){
        bool flag;
        for (int i = 0; i < n; i++) {
            flag=true;
            for (int j = 1; j < n; j++) {
                if(abs(mmap[i][j]-mmap[i][j-1])>1){
                    flag=false;
                    break;
                }
            }
            for (int j = 1; j < n-1; j++) {
                if(mmap[i][j-1]==mmap[i][j+1] && mmap[i][j-1] > mmap[i][j]) {
                    flag=false;
                    break;
                }
            }
            if(flag){
                res++;
            }
        }

        for (int i = 0; i < n; i++) {
            flag=true;
            for (int j = 1; j < n; j++) {
                if(abs(mmap[j][i]-mmap[j-1][i])>1){
                    flag=false;
                    break;
                }
            }
            for (int j = 1; j < n-1; j++) {
                if(mmap[j-1][i]==mmap[j+1][i] && mmap[j-1][i] > mmap[j][i]) {
                    flag=false;
                    break;
                }
            }
            if(flag){
                res++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            int cnt = 1;
            bool can_construct = false;
            bool flag = true;
            for (int j = 1; j < n; j++) {
                if (abs(mmap[i][j] - mmap[i][j - 1]) > 1) { // 높이 차이가 1보다 크면 건설 못함
                    flag = false;
                    break;
                }
                if (mmap[i][j] == mmap[i][j - 1]) cnt++;
                if (cnt == x) {
                    can_construct = true; // x만큼 평지를 전진하여 경사로를 건설할 수 있는 상태
                }
                if (mmap[i][j] - mmap[i][j - 1] == 1) { // 낮은곳에서 높은곳으로
                    if (can_construct) {
                        cnt = 1;
                        can_construct = false;
                    } else break;
                } else if (mmap[i][j] - mmap[i][j - 1] == -1) { // 높은곳에서 낮은곳으로
                    bool is_same_height = true;
                    for (int k = j; k < j + x - 1; k++) {
                        if (mmap[i][k] != mmap[i][k + 1]) is_same_height = false;
                    }
                    if (!is_same_height) {
                        flag = false;
                        break;
                    } else {
                        cnt = 0;
                        j += (x - 1);
                        can_construct = false;
                        if (j >= n) break;
                        if (j < n - 1) continue;
                    }
                }
                if (j == n - 1) { // 끝까지 도착
                    res++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int cnt = 1;
            bool canConstruct = false;
            bool flag = true;
            for (int j = 1; j < n; j++) {
                if (abs(mmap[j][i] - mmap[j - 1][i]) > 1) { // 높이 차이가 1보다 크면 건설 못함
                    flag = false;
                    break;
                }
                if (mmap[j][i] == mmap[j - 1][i]) cnt++;
                if (cnt == x) {
                    canConstruct = true; // x만큼 평지를 전진하여 경사로를 건설할 수 있는 상태
                }
                if (mmap[j][i] - mmap[j - 1][i] == 1) { // 낮은곳에서 높은곳으로
                    if (canConstruct) {
                        cnt = 1;
                        canConstruct = false;
                    } else break;
                } else if (mmap[j][i] - mmap[j - 1][i] == -1) { // 높은곳에서 낮은곳으로
                    bool is_same_height = true;
                    for (int k = j; k < j + x - 1; k++) {
                        if (mmap[k][i] != mmap[k + 1][i]) is_same_height = false;
                    }
                    if (!is_same_height) {
                        flag = false;
                        break;
                    } else {
                        cnt = 0;
                        canConstruct = false;
                        j += (x - 1);

                        if (j >= n) break;
                        if (j < n - 1) continue;

                    }
                }
                if (j == n - 1) { // 끝까지 도착
                    res++;
                }
            }
        }
    }
    cout<<res<<'\n';
}