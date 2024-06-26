#include <bits/stdc++.h>
using namespace std;

int q,n,m;

struct Belt{
    int head,tail,size;
};
struct Present{
    int prev,next;
};
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
            int num=1;
            for(int i=0;i<m;i++){ // n개의 벨트와 m개의 물건
                int belt_num; cin>>belt_num;
                belt[belt_num].size++; // 벨트 사이즈 증가

                if(belt[belt_num].size==1){ // 해당 벨트의 첫 물건일때
                    belt[belt_num].head=num;
                    belt[belt_num].tail=num;
                    num++;
                    continue;
                }
                int tail=belt[belt_num].tail;
                present[tail].next=num;
                present[num].prev=tail;
                belt[belt_num].tail=num;
                num++;
            }

        }
        if(op==200){
            int m_src,m_dst; cin>>m_src>>m_dst;
            if(belt[m_src].size==0){
                cout<<belt[m_dst].size<<'\n';
                continue;
            }
            int src_head=belt[m_src].head;
            int src_tail=belt[m_src].tail;
            int dest_head=belt[m_dst].head;

            belt[m_dst].head=src_head;
            if(belt[m_dst].size==0) {
                belt[m_dst].tail=src_tail;
            }else{
                present[dest_head].prev=src_tail;
                present[src_tail].next=dest_head;
            }

            belt[m_dst].size+=belt[m_src].size;
            belt[m_src].head=0;
            belt[m_src].tail=0;
            belt[m_src].size=0;

            cout<<belt[m_dst].size<<'\n';
        }
        if(op==300){
            int m_src,m_dst; cin>>m_src>>m_dst;
            int src=belt[m_src].head; // 1
            int dst=belt[m_dst].head; // 0

            if(src!=0 && dst != 0){ // 둘다 있을때
                belt[m_src].head=dst;
                belt[m_dst].head=src;
                if(belt[m_src].size==1){
                    belt[m_src].tail=dst;
                }else{
                    int next=present[src].next;
                    present[next].prev=dst;
                    present[dst].next=next;
                }
                if(belt[m_dst].size==1){
                    belt[m_dst].tail=src;
                }else{
                    int next=present[dst].next;
                    present[next].prev=src;
                    present[src].next=next;
                }

                swap(present[src],present[dst]);

            }
            else if(src!=0 && dst == 0){ // 출발지에만 있을때
                belt[m_dst].size++;

                belt[m_dst].head=src;
                belt[m_dst].tail=src;
                if(belt[m_src].size==1){
                    belt[m_src].size--;
                    belt[m_src].head=0;
                    belt[m_src].tail=0;
                    present[src].prev=0;
                    present[src].next=0;
                    belt[m_dst].tail=src;
                }else{
                    belt[m_src].size--;
                    belt[m_src].head=present[src].next;
                    present[src].prev=0;
                    present[src].next=0;
                }

            }
            else if(src==0 && dst != 0){ // 도착지에만 있을때
                belt[m_src].size++;

                belt[m_src].head=dst;
                belt[m_src].tail=dst;
                if(belt[m_dst].size==1){
                    belt[m_dst].size--;
                    belt[m_dst].head=0;
                    belt[m_dst].tail=0;
                    present[dst].prev=0;
                    present[dst].next=0;

                }else{
                    belt[m_dst].size--;
                    belt[m_dst].head=present[dst].next;
                    present[dst].prev=0;
                    present[dst].next=0;
                }
            }

            cout<<belt[m_dst].size<<'\n';
        }

        if(op==400){
            int m_src,m_dst; cin>>m_src>>m_dst;
            if(belt[m_src].size<=1){
                cout<<belt[m_dst].size<<'\n';
                continue;
            }
            int src_head=belt[m_src].head;
            int dst_head=belt[m_dst].head;
            int cnt=belt[m_src].size/2;

            int size=cnt;
            belt[m_src].size-= cnt;
            belt[m_dst].size+= cnt;
            int tmp=src_head;
            int src_tail=-1;
            while (cnt--){ // 옮기는 부분 벨트번호 바꾸기

                if(cnt==0) src_tail=tmp;
                tmp=present[tmp].next;
            }

            belt[m_src].head=tmp;
            present[tmp].prev=0;

            int dest_head=belt[m_dst].head;
            present[dest_head].prev=src_tail;
            present[src_tail].next=dst_head;

            belt[m_dst].head=src_head;

            if(belt[m_dst].size==size) {
                belt[m_dst].tail=src_tail;
            }
            cout<<belt[m_dst].size<<'\n';
        }
        if(op==500){
            int p_num; cin>>p_num;
            int a=-1;
            int b=-1;
            if(present[p_num].prev != 0){
                a=present[p_num].prev;
            }
            if(present[p_num].next != 0){
                b=present[p_num].next;
            }

            cout<<a+2*b<<'\n';
        }
        if(op==600){
            int b_num; cin>>b_num;
            int a=-1;
            int b=-1;
            int c=0;
            if(belt[b_num].size>0){
                a=belt[b_num].head;
                b=belt[b_num].tail;
                c=belt[b_num].size;
            }
            cout<<a+2*b+3*c<<'\n';
        }
    }
}