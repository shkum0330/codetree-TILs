#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Belt{
    int head,tail;
    bool broken;
};
struct Present{
    int weight,prev,next,belt_num;
    bool removed;
};

int n,m,q;
unordered_map<int,Belt> belt;
unordered_map<int,Present> present;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin>>q;

    while (q--){
        int op; cin>>op;

        if(op==100){
            cin>>n>>m;
            vector<int> ids;
            vector<int> weights;
            for (int i = 0; i < n; ++i) {
                int id; cin>>id;
                ids.push_back(id);
            }
            for (int i = 0; i < n; ++i) {
                int w; cin>>w;
                weights.push_back(w);
            }

            for (int i = 0; i < n; ++i) {
                present[ids[i]]={weights[i],0,0};
            }

            int size=n/m;
            for (int i = 0; i < m; ++i) {
                belt[i].head=ids[size*i];
                belt[i].tail=ids[size*(i+1)-1];

                for (int j = size*i; j < size*(i+1); ++j) {
                    present[ids[j]].belt_num=i;
                    if(j==size*i){
                        present[ids[j]].next=ids[j+1];
                        continue;
                    }
                    if(j==size*(i+1)-1){
                        present[ids[j]].prev=ids[j-1];
                        continue;
                    }
                    present[ids[j]].next=ids[j+1];
                    present[ids[j]].prev=ids[j-1];
                }

            }

        }
        if(op==200){
            int w_max; cin>>w_max;
            long long res=0;
            for (int i = 0; i < m; ++i) {
                if(belt[i].broken) continue;
                int head=belt[i].head;
                int tail=belt[i].tail;

                if(present[head].weight <= w_max){ // 하차 진행
//                    cout<<i<<'\n';
                    res += present[head].weight;

                    int next=present[head].next;
                    present[next].prev=0;
                    belt[i].head=present[head].next;
                    present[head].prev=0;
                    present[head].next=0;

                }else{ // 맨 뒤로 보내기
                    int next=present[head].next;
                    belt[i].head=present[head].next;
                    present[head].prev=tail;
                    belt[i].tail=head;
                    present[head].next=0;
                    present[tail].next=head;

                    present[next].prev=0;
                }

            }

            cout<<res<<'\n';
        }
        if(op==300){
            int r_id; cin>>r_id;
            if(present[r_id].prev==0 && present[r_id].next==0){
                cout<<-1<<'\n';
                continue;
            }
            int belt_num=present[r_id].belt_num;
            int prev=present[r_id].prev;
            int next=present[r_id].next;
            if(present[r_id].prev==0){ // head라면
                belt[belt_num].head=present[r_id].next;
            }
            if(present[r_id].next==0){ // tail이라면
                belt[belt_num].tail=present[r_id].prev;
            }
            present[r_id].prev=0;
            present[r_id].next=0;

            present[prev].next=next;
            present[next].prev=prev;

            cout<<r_id<<'\n';
        }
        if(op==400){
            int f_id; cin>>f_id;
            if(present[f_id].prev==0 && present[f_id].next==0){
                cout<<-1<<'\n';
                continue;
            }
            int head=belt[present[f_id].belt_num].head;
            int tail=belt[present[f_id].belt_num].tail;

            int prev=present[f_id].prev;
            int next=present[f_id].next;
            present[prev].next=0;

            present[head].prev=tail;
            present[tail].next=head;

            belt[present[f_id].belt_num].head=f_id;
            belt[present[f_id].belt_num].tail=prev;
            present[f_id].prev=0;

            cout<<present[f_id].belt_num+1<<'\n';
        }
        if(op==500){
            int b_num; cin>>b_num;
            b_num--;
            if(belt[b_num].broken){
                cout<<-1<<'\n';
                continue;
            }
            belt[b_num].broken=true;
            int to=b_num;
            while (true){
                to++;
                if(to==m) to=0;
                if(!belt[to].broken){

                    int head=belt[b_num].head;
                    int tail=belt[b_num].tail;

                    int to_head=belt[to].head;
                    int to_tail=belt[to].tail;
                    belt[to].tail=tail;

                    present[to_tail].next=head;
                    present[head].prev=to_tail;

                    int t=head;

                    while (t != 0){
                        present[t].belt_num=to;
                        t=present[t].next;
                    }

                    break;
                }

            }
            cout<<b_num+1<<'\n';
        }


    }
}