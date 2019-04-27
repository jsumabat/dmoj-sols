#include <bits/stdc++.h>

using namespace std;

#define make_unique(a) (a.erase(unique(a.begin(),a.end()),a.end()))
#define allof(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define exists(s, e) (s.find(e)!=s.end())
#define INF 0x3f3f3f3f
#define endl '\n'
#define mp make_pair
#define readln(x) (getline(cin, x))
#define watch(x) cerr << (#x) << " is " << (x) << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); debug("%s time : %.4fs\n", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))

using pii = pair<int, int>;
using ll = long long;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll LCM(ll a, ll b) { return a*b / gcd(a, b); }
ll fpow(ll  b, ll exp, ll mod){ if(exp == 0) return 1;ll t = fpow(b,exp/2,mod);if(exp&1) return t*t%mod*b%mod;return t*t%mod; }
ll divmod(ll i, ll j, ll mod){ i%=mod;j%=mod;return i*fpow(j,mod-2,mod)%mod; }

const int MAXN = 2e5 + 5;

int n, k;
vector<pii> adj[MAXN];
bool centroid_vis[MAXN];
int par[MAXN];
int sz[MAXN];
int org_sz[MAXN];
bool vis[MAXN];

void calc_subtree_sz(int cur) {
    for(pii v_info : adj[cur]) {
        int v = v_info.first;
        if(!centroid_vis[v] and v!=par[cur]) {
            par[v] = cur;
            calc_subtree_sz(v);
            sz[cur] += sz[v];
        }
    }
}

int get_centroid(int x) {
    int tot_sz = sz[x];
    while(true) {
        pii mx = {0, 0};
        for(pii v_info : adj[x]) {
            int v = v_info.first;
            if(!centroid_vis[v] and v!=par[x]) {
                mx = max(mx, {sz[v], v});
            }
        }
        if(mx.first*2 > tot_sz) {
            x = mx.second;
        } else {
            return x;
        }
    }
}

void solve() {
    cin >> k >> n;
    for(int i=1; i<=k; i++) {
        int x;
        cin >> x;
        sz[x]++;
        org_sz[x]++;
    }

    for(int i=0; i<n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

//    number of people at node i
//    cerr << "debug" << '\n';
//    for(int i=1; i<=n; i++) {
//        cerr << sz[i] << ' ';
//    } cerr << '\n';

    calc_subtree_sz(1);
    
//    debug subtree sz
//    for(int i=1; i<=n; i++) {
//        cerr << sz[i] << ' ';
//    } cerr << '\n';

    int centroid = get_centroid(1);
//    fprintf(stderr, "centroid: %d\n", centroid);

    ll ans = 0;
    queue<pair<int, ll>> q;
    q.push({centroid, 0});
    vis[centroid] = true;
    while(sz(q)) {
        pii cur = q.front();
        q.pop();
        for(pii v_info : adj[cur.first]) {
            int v = v_info.first;
            ll curdis = 1LL * v_info.second + cur.second;
            if(!vis[v]) {
                ll add = (curdis * org_sz[v]);
//                watch(add);
                ans += add;
                q.push({v, curdis});
                vis[v] = true;
            }
        }
    }

    cout << ans << '\n';

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    solve();
    return 0;
}
