#include <bits/stdc++.h>
using namespace std;

int arr[1000001];
int n,b,c;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>arr[i];
    }
    cin>>b>>c;
    long long cnt=0;
    for (int i = 0; i < n; ++i) {
        if(arr[i]<=b){
            cnt++;
            continue;
        }
        arr[i]-=b;
        cnt++;
        if(arr[i]%c!=0) cnt += arr[i]/c+1;
        else cnt += arr[i]/c;

    }
    cout<<cnt<<'\n';
}