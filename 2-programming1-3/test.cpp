#include<iostream>
#include<queue>
#include<stack>

using namespace std;

struct edge
{
    int v;
    int next=0;
};

int main(){
    int n,m,s;
    cin>>n>>m>>s;
    int u,v;
    edge* Node[n+10];
    for(int i=1;i<=n;i++){
        Node[i]=nullptr;
    }
    edge* E=new edge[m+10];
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        E[i].v=v;
        if(Node[u]!=nullptr){
            E[i].next=Node[u]-E;
        }
        Node[u] = &E[i];
    }
    queue<int> qu;
    int hash[n+10]={0};
    qu.push(s);
    while(qu.size()){
        int cur =qu.front();
        qu.pop();
        if(hash[cur])
            continue;
        cout<< cur<<' ';
        hash[cur]=1;
        if(Node[cur]!=nullptr){
            if(hash[Node[cur]->v]==0){
                qu.push(Node[cur]->v);
            }
            int ne =Node[cur]->next;
            while(ne){
                if(hash[E[ne].v]==0){
                    qu.push(E[ne].v);
                }
                ne = E[ne].next;
            }
        }
    }
    cout<<endl;


    stack<int> st;
    int map[n+10]={0};
    st.push(s);
    while(st.size()){
        int cur =st.top();
        st.pop();
        if(map[cur])
            continue;
        cout<< cur<<' ';
        map[cur]=1;
        if(Node[cur]!=nullptr){
            stack<int> ve;
            if(map[Node[cur]->v]==0){
                ve.push(Node[cur]->v);  
            }
            int ne =Node[cur]->next;
            while(ne){
                if(map[E[ne].v]==0){
                    ve.push(E[ne].v);
                }
                ne = E[ne].next;
            }
            while(ve.size()){
                st.push(ve.top());
                ve.pop();
            }
        }
    }
}