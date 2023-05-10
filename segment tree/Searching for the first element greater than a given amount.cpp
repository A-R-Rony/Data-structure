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

/*The task is as follows: for a given value x
and a range a[l...r] find the smallest i
in the range a[l .. r], such that a[i] is 
greater than x.
*/

struct segment_tree
{
    struct NODE{
        int st , EN, value;// start , end

         void init(int L,int R){
           st = L, EN = R; 
           if(L == R) value = a[L];
         }
    }g[3*MAXN];

    void fill_CN(NODE &CN, NODE &LN, NODE &RN) // fill_current_node
    {
        CN.value = max(LN.value,RN.value);
    }

    void build(int CN,int L,int R)
    {
        g[CN].init(L,R);

        if(L == R ) return;
        int mid = (L+R)>>1;
        int LN = CN << 1;

        build(LN,L,mid);
        build(LN|1,mid+1,R);

        fill_CN (g[CN], g[LN] , g[LN|1]);
    }

    void update(int CN, int pos,int val)
    {
        int x = g[CN].st;
        int y = g[CN].EN;

        if(x == y)
        {
            g[CN].value = val;
            return;
        }

        int md = x + (y - x)/2;
        if(pos <= md) update(CN*2,pos,val);
        else update(CN*2 + 1, pos,val);

        fill_CN(g[CN], g[2*CN],g[2*CN + 1]);
    }

    int work(int CN,int x)
    {
        if(g[CN].st == g[CN].EN) return g[CN].st;

         if(g[CN*2].value > x) return work(CN*2,x);
         return work(CN*2 + 1, x);
    }

    int query(int CN, int L,int R,int val)
    {
        int x = g[CN].st;
        int y = g[CN].EN;
        if(y < L || x > R) return -1;
        
        if(g[CN].value <= val) return -1;

        if(L <= x && R >= y ) {
           return work(CN,val);
        }

        int LN = CN<<1;

        int ans = query(LN,L,R,val);
        if(ans != -1) return ans;
        ans = query(LN|1,L,R,val);
        return ans;
    }

} s_tree;

void solve()
{
  cin >> n;
  for(int i = 1;i <= n;i++) cin >> a[i];
   
   s_tree.build(1,1,n);

   cout<<s_tree.query(1,2,4,5)<<en;
   cout<<s_tree.query(1,1,1,7)<<en;
   cout<<s_tree.query(1,3,4,2)<<en;

   s_tree.update(1,3,10);
   cout<<s_tree.query(1,3,4,9)<<en;

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
