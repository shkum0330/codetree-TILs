#include <bits/stdc++.h>
using namespace std;

int n,m,x,y,k;
int mmap[21][21];
int dice[7];
pair<int,int> mov[4]={{0,1},{0,-1},{-1,0},{1,0}};
vector<int> op;
pair<int,int> location;

void moving(int dir){
    int newDice[7];
    if(dir==1){
        newDice[1]=dice[4]; newDice[2]=dice[2]; newDice[3]=dice[1]; newDice[4]=dice[6]; newDice[5]=dice[5]; newDice[6]=dice[3];
    }
    if(dir==2){
        newDice[1]=dice[3]; newDice[2]=dice[2]; newDice[3]=dice[6]; newDice[4]=dice[1]; newDice[5]=dice[5]; newDice[6]=dice[4];
    }
    if(dir==3){
        newDice[1]=dice[2]; newDice[2]=dice[6]; newDice[3]=dice[3]; newDice[4]=dice[4]; newDice[5]=dice[1]; newDice[6]=dice[5];
    }
    if(dir==4){
        newDice[1]=dice[5]; newDice[2]=dice[1]; newDice[3]=dice[3]; newDice[4]=dice[4]; newDice[5]=dice[6]; newDice[6]=dice[2];
    }
    for (int i = 1; i <= 6; ++i) {
        dice[i]=newDice[i];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>n>>m>>x>>y>>k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin>>mmap[i][j];
        }
    }
    for (int i = 0; i < k; ++i) {
        int num; cin>>num;
        op.push_back(num);
    }

    location={x,y};
    for (int i = 0; i < k; ++i) {
        if(location.first+mov[op[i]-1].first>=n || location.first+mov[op[i]-1].first<0 || location.second+mov[op[i]-1].second>=m || location.second+mov[op[i]-1].second<0) {
            continue;
        }

        location.first += mov[op[i]-1].first;
        location.second += mov[op[i]-1].second;

        moving(op[i]);

        if(mmap[location.first][location.second]==0) mmap[location.first][location.second]=dice[6];
        else {
            dice[6]=mmap[location.first][location.second];
            mmap[location.first][location.second]=0;
        }
        cout<<dice[1]<<'\n';
    }
}