#include <bits/stdc++.h>

using namespace std;

map<int,int> m;
int arr[201][201];
int r,c,k;
int cnt[101];
int res=-1;

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>r>>c>>k;

    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cin>>arr[i][j];
        }
    }
    int time=0;
    int row_size=3;
    int col_size=3;

    while(time<=100){
        if(arr[r][c]==k){
            res=time;
            break;
        }

        int tmp_size=0;

        if(row_size>=col_size){    
            for(int i=1;i<=row_size;i++){
                vector<pair<int,int>> v; // {등장 홧수, 숫자}

                for(int j=1;j<=100;j++){ // cnt 배열 초기화
                    cnt[j]=0;
                }

                for(int j=1;j<=col_size;j++){
                    if(arr[i][j]==0) break;
                    cnt[arr[i][j]]++;
                }

                for(int j=1;j<=100;j++){
                    if(cnt[j]==0) continue;
                    v.push_back({cnt[j],j});
                }
       
                sort(v.begin(),v.end());
                
                int idx=1;
                for(int j=0;j<v.size();j++){
                    if(idx==101) break;
                    arr[i][idx++]=v[j].second;
                    arr[i][idx++]=v[j].first;
                }
                for(int j=idx; j<=100;j++){
                    arr[i][idx]=0;
                }
         
                tmp_size=max(idx-1,tmp_size);
            }
            
            col_size=tmp_size;
    
        }else{
   
            for(int i=1;i<=col_size;i++){
                vector<pair<int,int>> v; // {등장 홧수, 숫자}

                for(int j=1;j<=100;j++){ // cnt 배열 초기화
                    cnt[j]=0;
                }

                for(int j=1;j<=row_size;j++){
                    if(arr[j][i]==0) break;
                    cnt[arr[j][i]]++;
                }

                for(int j=1;j<=100;j++){
                    if(cnt[j]==0) continue;
                    v.push_back({cnt[j],j});
                }
       
                sort(v.begin(),v.end());
                
                int idx=1;
                for(int j=0;j<v.size();j++){
                    if(idx==101) break;
                    arr[idx++][i]=v[j].second;
                    arr[idx++][i]=v[j].first;
                }
                for(int j=idx; j<=100;j++){
                    arr[idx][i]=0;
                }
         
                tmp_size=max(idx-1,tmp_size);
            }
            
            row_size=tmp_size;
        }
        time++;
    }
    
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            cout<<arr[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<res<<'\n';
}