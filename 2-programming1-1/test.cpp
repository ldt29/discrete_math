#include<iostream>
using namespace std;

struct edge{
    int x;
    int w;
    int next;
};
int main(){
    int n ,m;
    cin >> n >> m;
    edge* E = new edge[m+10];
    edge* node[n+10]={nullptr};
    int u,v,w;
    int **a = new int*[n+10];
    for(int i=1;i<=n;i++)
    {
        a[i] = new int[n+10];
        for(int j=1;j<=n;j++){
            a[i][j]=0;
        }
    }
    for(int i=1;i<=m;i++){
        cin >> u>> v>> w;
        if(a[u][v]){
            a[u][v]=-1;
        }else{
            a[u][v]=w;
        }
        E[i].x=v;
        E[i].w=w;
        E[i].next=0;
        if(node[u]!= nullptr){
            E[i].next=node[u]-E;
        }      
        node[u] = &E[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
    for(int i=1;i<=n;i++){
        if(node[i]==nullptr)
        cout<< 0<<endl;
        else
        cout<<node[i]-E<<endl;
    }
    for(int i=1;i<=m;i++){
        cout<< E[i].x <<' '<<E[i].w<<' '<<E[i].next<<endl;
    }
}
