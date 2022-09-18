
#include<bits/stdc++.h>
using namespace std;

#define N 1005
int parent[N];

int Find(int u)
{
   if(parent[u] == u) return u;
   return parent[u] = Find(parent[u]);
}
void Union(int u,int v)
{
    parent[v] = u;
}
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) parent[i] = i;

    for(int i = 1;i <= m;i++)
    {
        int u,v;
        cin >> u >> v;

         int x = Find(u);
         int y = Find(v);
            
         if(x != y)
        Union(x,y);
    }

    for(int i = 1;i <= n;i++){
        cout<<parent[i]<<" ";
    }
    cout<<endl;

}

