#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define IOS ios_base::sync_with_stdio(0);  cin.tie(0); cout.tie(0);

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>order_set;
typedef pair<int, int>pr;
#define all(i)     i.begin() , i.end()
#define ft     first
#define sn     second
#define pb push_back

#define totalone(mask) __builtin_popcount(mask)
#define chkbit(mask,bit) (mask&(1LL << bit))
#define setbit(mask,bit) (mask|(1LL << bit))
#define cngbit(mask,bit) (mask^(1LL << bit))

#define en "\n"
#define dbg(x) cerr<<#x<<" is : "<<x<<en;
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define report cout<<-1<<en
#define sum(n) ((1LL*(n)*(n+1))/ 2LL)
#define sqr(n) (1LL*(n)*(n))
#define vag(a,b) ((a + b - 1)/b)
#define coutv(v) for(auto i: v) cout<<i<<" ";cout<<en;
#define cinv(v) for(auto &i: v) cin >> i;

#define MAXN 200010
#define inf 1e6+5
const int mod = 1e9 + 7;

// the modification query is to add a number to all elements in a range,
//and the reading query is to find the maximum in a range.

int n;
int a[MAXN];

struct segment_tree
{
    struct node {
        int suru , ses, mx, lazy;

        void init(int l, int r) {
            suru = l, ses = r; lazy = 0;
            if (l == r) mx = a[l];
        }
    } g[4 * MAXN];

    void fill_cn(node &cn, node &ln, node &rn) // fill_current_node
    {
        cn.mx = max(ln.mx, rn.mx);
    }

    void build(int cn, int l, int r)
    {
        g[cn].init(l, r);

        if (l == r ) return;
        int md = l + (r - l) / 2;

        build(cn * 2, l, md);
        build(cn * 2 + 1, md + 1, r);

        fill_cn (g[cn], g[cn * 2] , g[cn * 2 + 1]);
    }

    void distribute(node &cn, node &ln, node &rn)
    {
        ln.lazy += cn.lazy;
        rn.lazy += cn.lazy;
        ln.mx += cn.lazy;
        rn.mx += cn.lazy;
        cn.lazy = 0;
    }

    void update(int cn, int l, int r, int val)
    {
        int x = g[cn].suru;
        int y = g[cn].ses;

        if (y < l || x > r) return;
        if (l <= x && r >= y ) {
            g[cn].mx += val;
            g[cn].lazy += val;
            return;
        }

        distribute(g[cn], g[cn * 2], g[cn * 2 + 1]);

        update(cn * 2, l, r, val);
        update(cn * 2 + 1, l, r, val);

        fill_cn(g[cn], g[cn * 2], g[cn * 2 + 1]);
    }

    int query(int cn, int l, int r)
    {
        int x = g[cn].suru;
        int y = g[cn].ses;
        if (y < l || x > r) return INT_MIN;

        if (l <= x && r >= y ) {
            return g[cn].mx;
        }

        distribute(g[cn], g[cn * 2], g[cn * 2 + 1]);

        int ans = query(cn * 2, l, r);
        ans = max(ans, query(cn * 2 + 1, l, r));
        return ans;
    }

} stre;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
/*
input:
5
5 8 2 9 2
*/
  
    stre.build(1, 1, n);

    cout << stre.query(1, 1, 4) << en;
    cout << stre.query(1, 2, 3) << en;

    stre.update(1, 3, 4, -10);
    cout << stre.query(1, 3, 4) << en;
    cout << stre.query(1, 3, 3) << en;

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
