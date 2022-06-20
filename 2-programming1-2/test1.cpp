#include<iostream>
using namespace std;
#define mod 1000003 

long** mat(long** a,long** b, int n){
    long **c = new long*[n+2];
    for(int i=1;i<=n;i++){
        c[i] = new long[n+2];
        for(int j=1;j<=n;j++){
            c[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
            }
        }
    }
    return c;
}

int main(){
    int n,m,s,t,k;
    cin>>n>>m>>s>>t>>k;
    int u,v;
    long **a= new long*[n+2];
    long **ans= new long*[n+2];
    for(int i=1;i<=n;i++){
        a[i] = new long[n+2];
        ans[i]=new long[n+2];
        for(int j=1;j<=n;j++){
            a[i][j]=0;
            ans[i][j]=0;
        }
        ans[i][i]=1;
    }
    for(int i=0;i<m;i++){
        cin>>u>>v;
        a[u][v]++;
    }
    while(k--){
        ans=mat(ans,a,n);
    }
   /*while(k){
        if(k%2){
            ans =mat(ans,a,n);
        }
        k =k/2;
        a= mat(a,a,n);
    }*/
    cout<<ans[s][t];  
}