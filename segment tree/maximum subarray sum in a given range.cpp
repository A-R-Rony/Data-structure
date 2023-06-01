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

#define dbg cout<<"rony\n"
#define en "\n"

#define MAXN 100010
#define inf 1e6+5
const ll mod = 1e9 + 7;

int n;
int a[MAXN];

// maximum subarray sum in a given range
struct SegmentTree
{
    struct node {
        int suru, ses, pre, suf, sm, an;
        void init(int l, int r)
        {
            suru = l, ses = r;

            if (l == r) {
                sm = a[l];
                pre = suf = an = max(0, a[l]);
            }
        }
    } g[4 * MAXN], ans;

    node fill_cn( int l, int r, node &B, node &C)
    {
        node A;
        A.suru = l; A.ses = r;
        A.pre = max(B.sm + C.pre, B.pre);
        A.suf = max(C.sm + B.suf, C.suf);
        A.sm = B.sm + C.sm;
        A.an = max({B.an, C.an, B.suf + C.pre});

        return A;
    }
    void build(int cn, int l, int r)
    {
        g[cn].init(l, r);
        if (l == r) return ;
        int md = l + (r - l) / 2;
        build(cn * 2, l, md);
        build(cn * 2 + 1, md + 1, r);
        g[cn] = fill_cn(l, r, g[cn * 2], g[cn * 2 + 1]);
    }

    node NodeMaker(int x)
    {
        node nd;
        nd.sm = nd.pre = nd.suf = nd.an = 0;
        return nd;
    }

    node query(int cn, int l, int r)
    {
        int x = g[cn].suru;
        int y = g[cn].ses;

        if (x > r || l > y) {
            return NodeMaker(0);
        }
        if (x >= l && y <= r) {
            return g[cn];
        }

        node nd1 = query(cn * 2, l, r);
        node nd2 = query(cn * 2 + 1 , l , r);
        return fill_cn(x, y, nd1, nd2);
    }

    void update(int cn, int id, int val)
    {
        int x = g[cn].suru;
        int y = g[cn].ses;
        if (x > id || id > y) {
            return;
        }
        if (x == y) {
            g[cn].sm = val;
            g[cn].pre = g[cn].suf = g[cn].an = max(0, val);
            return;
        }
        update(cn * 2, id, val);
        update(cn * 2 + 1, id, val);
        g[cn] = fill_cn(x, y, g[cn * 2], g[cn * 2 + 1]);
    }

} stre;
void solve()
{
    /*input:
    5
    1 2 -3 4 5
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    stre.build(1, 1, n);

    stre.ans = stre.query(1, 1, 5);
    cout << stre.ans.an << en;

    stre.ans = stre.query(1, 3, 3);
    cout << stre.ans.an << en;

    stre.ans = stre.query(1, 3, 5);
    cout << stre.ans.an << en;

    stre.ans = stre.query(1, 5, 5);
    cout << stre.ans.an << en;

    stre.ans = stre.query(1, 4, 4);
    cout << stre.ans.an << en;

    stre.update(1, 3, 6);

    stre.ans = stre.query(1, 1, 5);
    cout << stre.ans.an << en;

    stre.update(1, 4, -10);
    stre.ans = stre.query(1, 4, 4);
    cout << stre.ans.an << en;

    stre.ans = stre.query(1, 1, 4);
    cout << stre.ans.an << en;



}
int main()
{
    IOS;
    ll t;
    t = 1;
    // cin >> t;

    ll c = 0;
    while ( t-- )
    {
        // cout<<"Case "<<++c<<": ";
        solve();
    }
    return 0;
}
