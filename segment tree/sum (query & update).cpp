#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define IOS ios_base::sync_with_stdio(0);  cin.tie(0); cout.tie(0);


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type, less<int>,rb_tree_tag, tree_order_statistics_node_update>order_set;
typedef pair<int,int>pr;
#define all(i)     i.begin() , i.end()
#define ft     first
#define sn     second
#define pb push_back

#define en "\n"
#define dbg cout<<"rony\n"

#define MAXN 100010
#define inf 1e6+5
const ll mod = 1e9+7;
 
int n;
int a[MAXN];
// sum - update - query 

struct SegmentTree
{
   struct node{
     int suru,ses,value;
     void initialize(int l,int r)
     {
        suru = l , ses = r;
        if(l == r) value = a[l];
     }
   }g[3*MAXN];
   
   void fillCN(node &ek, node &dui, node &tin)
   {
     ek.value = dui.value + tin.value;
   }
   void build(int CN,int l,int r)
   {
      g[CN].initialize(l,r);
      if(l == r) return;
      int md = l + (r - l)/2;

      build(CN*2,l,md);
      build(CN*2 + 1, md + 1, r);
      fillCN(g[CN],g[CN*2],g[CN*2 + 1]);
   }

   int query(int CN,int l,int r)
   {
     int x = g[CN].suru;
     int y = g[CN].ses;
     if(x > r || l > y) return 0;
     if(x >= l && y <= r) return g[CN].value;

     int md = l + (r - l)/2;
     int an = query(CN*2,l,r);
     an += query(CN*2 + 1, l,r);
     return an;
   }

   void update(int CN,int id,int val)
   {
     int x = g[CN].suru;
     int y = g[CN].ses;

     if(id > y || id < x) return;
     if(x == y && x == id){
        g[CN].value = val;
        return;
     }
     
      update(CN*2, id,val);
      update(CN*2 + 1, id,val);

      fillCN(g[CN],g[CN*2],g[CN*2 + 1]);
   }
}stre;

void solve()
{
  cin >> n;
  for(int i = 1;i <= n;i++){
    cin >> a[i];
  }
  
  stre.build(1,1,n);
  cout<<stre.query(1,1,4)<<en;
  cout<<stre.query(1,4,5)<<en;
  cout<<stre.query(1,5,5)<<en;

  stre.update(1,4,10);

  cout<<stre.query(1,4,5)<<en;

}
int main()
{
    IOS;
   ll t;
   t = 1;

   // cin >> t;

   int c = 0;
    while ( t-- )
    {
        // cout<<"Case "<<++c<<": ";
        solve();
    }
    return 0;
}   
