#include <bits/stdc++.h>
using namespace std;

struct Query {
    int op, t, x, n;
    string name;

};

int l,q;

vector<Query> queries;
set<string> names;
unordered_map<string,vector<Query>> p_queries;
unordered_map<string,int> entry_time,exit_time;
unordered_map<string,int> position;

bool compare(const Query& a,const Query& b){
    if(a.t != b.t){
        return a.t<b.t;
    }
    return a.op<b.op;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>l>>q;

    while (q--){
        int op; cin>>op;
        if(op==100){
            int t,x; string name; cin>>t>>x>>name;
            queries.push_back({op,t,x,-1,name});
            p_queries[name].push_back({op,t,x,-1,name});
        }
        if(op==200){
            int t,x,n; string name; cin>>t>>x>>name>>n;
            queries.push_back({op,t,x,n,name});
            names.insert(name);
            entry_time[name]=t;
            position[name]=x;
        }
        if(op==300){
            int t; cin>>t;
            queries.push_back({op,t,-1,-1," "});
        }

    }
    for (string name:names) {
        exit_time[name]=0;

        for (Query q:p_queries[name]) {
            int time_to_removed=0;

            if(q.t<entry_time[name]){ // 초밥이 이미 존재
                int t_sushi_x= (q.x + (entry_time[name]-q.t))%l; // entry time때 초밥의 위치
                int eatable_time=(position[name]-t_sushi_x+l)%l; // 초밥을 만나는데 필요한 시간

                time_to_removed=entry_time[name]+eatable_time;
            }else{ // 사람이 왔는데 초밥이 없을때
                int eatable_time=(position[name]-q.x+l)%l;
                time_to_removed=q.t+eatable_time;
            }

            exit_time[name]=max(exit_time[name],time_to_removed);
            queries.push_back({111,time_to_removed,-1,-1,name});
            
        }
    }
    for (string name : names) {
        queries.push_back({222,exit_time[name],-1,-1,name});
    }

    sort(queries.begin(),queries.end(),compare);


    int people_num=0,sushi_num=0;
    for (int i = 0; i < queries.size(); ++i) {
        if(queries[i].op==100){
            sushi_num++;
        }
        if(queries[i].op==111){
            sushi_num--;
        }
        if(queries[i].op==200){
            people_num++;
        }
        if(queries[i].op==222){
            people_num--;
        }
        if(queries[i].op==300){
            cout<<people_num<<' '<<sushi_num<<'\n';
        }
    }

}