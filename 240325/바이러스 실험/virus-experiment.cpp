#include <bits/stdc++.h>

using namespace std;

int n,m,k,res;

struct Virus{
    int y,x,age;
};

bool compare(const Virus& a, const Virus& b){
    return a.age<b.age;
}

int mmap[11][11];
int inc[11][11];
int dy[8]={-1,0,1,1,1,0,-1,-1};
int dx[8]={1,1,1,0,-1,-1,-1,0};
vector<Virus> v;


int main() {
    // 여기에 코드를 작성해주세요.
    
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>inc[i][j];
            mmap[i][j]=5;
        }
    }

    for(int i=0;i<m;i++){
        int r,c,l;
        cin>>r>>c>>l;
        v.push_back({r,c,l});
    }

    while(k--){
        sort(v.begin(),v.end(),compare);
        vector<Virus> d; // 죽은 바이러스들

        // 양분 섭취
        for(int i=0;i<v.size();i++){
            int y=v[i].y;
            int x=v[i].x;
            int age=v[i].age;

            if(age==0) continue;

            if(mmap[y][x]<age){
                d.push_back({y,x,age});
                v[i].age=0;
                continue;
            }
            mmap[y][x] -= age;
            v[i].age++;
            
        }

        // 죽은 바이러스 양분으로 변환
        for(auto &i:d){
            mmap[i.y][i.x] += i.age/2;
        }

        // 바이러스 번식
        for(auto &l:v){
            if(l.age==0 || l.age%5 != 0) continue;
            for(int i=0;i<8;i++){
                int ny=l.y+dy[i];
                int nx=l.x+dx[i];
                if(ny>n || ny<=0 || nx>n || nx<=0) continue;
                v.push_back({ny,nx,1});
            }
        }

        // 양분 추가
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mmap[i][j] += inc[i][j];
            }
        }
    }

    for(auto& k:v){
        if(k.age==0) continue;
        res++;
    }

    cout<<res<<'\n';
}