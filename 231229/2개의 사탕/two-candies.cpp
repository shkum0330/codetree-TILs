#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
char board[11][11];
int n,m;
pii red,blue,hole;
int dy[4]={0,0,-1,1};
int dx[4]={-1,1,0,0};
int res=30;

void moving(int cnt,int dir,int ry,int rx,int by,int bx){
    if(cnt>10) return;

    bool r_flag=false; // 파란 구슬의 진행 경로에 빨간 구슬이 있는지 확인
    bool b_flag=false; // 빨간 구슬의 진행 경로에 파란 구슬이 있는지 확인
    bool r_in=false;
    bool b_in=false;

    if(dir==0){ // 왼쪽으로 기울이기
        if(ry==by) {
            if (rx < bx) { // RB
                r_flag = true;
            }
            if (bx < rx) { // BR
                b_flag = true;
            }
        }
        while (true){
            rx += dx[dir];
            if(board[ry][rx]=='O'){
                r_in= true;
                break;
            }
            if(board[ry][rx]=='#'){
                rx -= dx[dir];
                break;
            }
        }
        while (true){
            bx += dx[dir];
            if(board[by][bx]=='O'){
                b_in= true;
                break;
            }
            if(board[by][bx]=='#'){
                bx -= dx[dir];
                break;
            }
        }
        if(rx==bx){
            if(r_flag) bx -= dx[dir];
            if(b_flag) rx -= dx[dir];
        }
    }
    if(dir==1){ // 오른쪽으로 기울이기
        if(ry==by) {
            if (rx < bx) { // RB
                b_flag = true;
            }
            if (bx < rx) { // BR
                r_flag = true;
            }
        }
        while (true){
            rx += dx[dir];
            if(board[ry][rx]=='O'){
                r_in= true;
                break;
            }
            if(board[ry][rx]=='#'){
                rx -= dx[dir];
                break;
            }
        }
        while (true){
            bx += dx[dir];
            if(board[by][bx]=='O'){
                b_in= true;
                break;
            }
            if(board[by][bx]=='#'){
                bx -= dx[dir];
                break;
            }
        }
        if(rx==bx){
            if(r_flag) bx -= dx[dir];
            if(b_flag) rx -= dx[dir];
        }
    }
    if(dir==2){ // 위로 기울이기
        if(rx==bx) {
            if (ry < by) {
                r_flag = true;
            }
            if (by < ry) {
                b_flag = true;
            }
        }
        while (true){
            ry += dy[dir];
            if(board[ry][rx]=='O'){
                r_in= true;
                break;
            }
            if(board[ry][rx]=='#'){
                ry -= dy[dir];
                break;
            }
        }
        while (true){
            by += dy[dir];
            if(board[by][bx]=='O'){
                b_in= true;
                break;
            }
            if(board[by][bx]=='#'){
                by -= dy[dir];
                break;
            }
        }
        if(ry==by){
            if(r_flag) by -= dy[dir];
            if(b_flag) ry -= dy[dir];
        }
    }
    if(dir==3){ // 아래로 기울이기
        if(rx==bx) {
            if (ry < by) { // RB
                b_flag = true;
            }
            if (by < ry) { // BR
                r_flag = true;
            }
        }
        while (true){
            ry += dy[dir];
            if(board[ry][rx]=='O'){
                r_in= true;
                break;
            }
            if(board[ry][rx]=='#'){
                ry -= dy[dir];
                break;
            }
        }
        while (true){
            by += dy[dir];
            if(board[by][bx]=='O'){
                b_in= true;
                break;
            }
            if(board[by][bx]=='#'){
                by -= dy[dir];
                break;
            }
        }
        if(ry==by){
            if(r_flag) by -= dy[dir];
            if(b_flag) ry -= dy[dir];
        }
    }
    if(b_in) return;
    if(r_in && !b_in){
        res=min(cnt,res);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        moving(cnt+1,i,ry,rx,by,bx);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m;
    for (int i = 0; i < n; ++i) {
        string s; cin>>s;
        for (int j = 0; j < m; ++j) {
            board[i][j]=s[j];
            if(board[i][j]=='R') {
                red = {i, j};
                board[i][j]='.';
            }
            if(board[i][j]=='B') {
                blue={i,j};
                board[i][j]='.';
            }
            if(board[i][j]=='O') hole={i,j};
        }
    }
    for (int i = 0; i < 4; ++i) {
        int ry=red.first; int rx=red.second;
        int by=blue.first; int bx=blue.second;
        moving(1,i,ry,rx,by,bx);
    }

    if(res>10) cout<<-1<<'\n';
    else cout<<res<<'\n';
}