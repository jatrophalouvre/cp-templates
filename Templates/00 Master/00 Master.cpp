// 2D Fenwick Tree (point updates)
struct FWT
{
	int v[N][N];
	
	FWT() {}
	void update(int x, int y, int val)
	{
		x++; y++;
		while (x<=n)
		{
			int ty=y;
			while (ty<=n)
			{
				v[x][ty]+=val;
				ty+=(ty&-ty);
			}
			x+=(x&-x);
		}
	}
	int query(int x, int y)
	{
		int ans=0;
		while (x>0)
		{
			int ty=y;
			while (ty>0)
			{
				ans+=v[x][ty];
				ty-=(ty&-ty);
			}
			x-=(x&-x);
		}
		return ans;
	}
	int query(int x1, int y1, int x2, int y2)
	{
		x2++; y2++;
		return query(x2, y2)-query(x2, y1)-query(x1, y2)+query(x1, y1);
	}
} *fwt;

// Convex Hull Trick (deque)
struct line
{
    int a=0, b=-1e18;
    int operator()(int x) { return a*x+b; }
};
struct CHT
{
    deque<line> q;
    
    CHT() {}
    void insert(line x)
    {
        while (q.size()>=2 && intersect(x, q[q.size()-2])>=intersect(x, q[q.size()-1])) q.pop_back();
        q.push_back(x);
    }
    int query(int x)
    {
        if (q.size()==1) return q[0](x);
        if (intersect(q[0], q[1])>x) return q[0](x);
        int l=1, r=q.size();
        while (l+1<r)
        {
            int mid=(l+r)>>1;
            if (intersect(q[mid-1], q[mid])<=x) l=mid;
            else r=mid;
        }
		return q[l](x);
    }
    double intersect(line x, line y)
    {
        if (x.a==y.a) return -1e18;
        else return (double)(x.b-y.b)/(double)(y.a-x.a);
    }
} *cht;

// Convex Hull Trick (LC)
struct line
{
    mutable int a, b, p;
    int operator()(int x) { return a*x+b; }
    bool operator<(line x) const { return a<x.a; }
    bool operator<(int x) const { return p<x; }
};
struct CHT:multiset<line, less<>>
{
    CHT() {}
    void add(line l)
    {
        auto z=insert(l);
        auto y=z++, x=y;
        while (isect(y, z)) z=erase(z);
        if (x!=begin() && isect(--x, y)) isect(x, y=erase(y));
        while ((y=x)!=begin() && ((--x)->p)>=(y->p)) isect(x, erase(y));
    }
    int query(int x)
    {
        auto l=*lower_bound(x);
        return (int)l(x);
    }
    int div(int x, int y) { return x/y-((x^y)<0 && x%y); }
    bool isect(iterator x, iterator y)
    {
        if (y==end()) return x->p=1e18, 0;
        if (x->a==y->a) x->p=(x->b)>(y->b)?1e18:-1e18;
        else x->p=div((y->b)-(x->b), (x->a)-(y->a));
        return (x->p)>=(y->p);
    }
} *cht;

// Fenwick Tree (point updates)
struct FWT
{
    int v[N]={0};
    
    FWT() {}
    void update(int pos, int val)
    {
		pos++;
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    int query(int pos)
    {
        int ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    int query(int l, int r)
    {
		l++; r++;
		return query(r)-query(l-1);
	}
} *fwt;

// Fenwick Tree
struct FWT
{
    int v1[N], v2[N];
    
    FWT() {}
    void update(int v[N], int pos, int val)
    {
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    void update(int l, int r, int val)
    {
        l++; r++;
        update(v1, l, val); update(v1, r+1, -val);
        update(v2, l, l*val); update(v2, r+1, -(r+1)*val);
    }
    int query(int v[N], int pos)
    {
        int ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    int query(int l, int r)
    {
		l++; r++;
        return ((r+1)*query(v1, r)-query(v2, r))-(l*query(v1, l-1)-query(v2, l-1));
    }
} *fwt;

// Lichao Tree
struct line
{
    int a=0, b=-1e18;
    int operator()(int x) { return a*x+b; }
    bool operator==(line x) { return a==x.a && b==x.b; }
};
struct LCT
{
    int l, r, mid;
    line v;
    LCT *lptr, *rptr;
    
    LCT(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lptr=rptr=nullptr;
    }
    void build()
    {
        if (lptr==nullptr) lptr=new LCT(l, mid);
        if (rptr==nullptr) rptr=new LCT(mid+1, r);
    }
    void insert(line x)
    {
        bool bl=(x(l)>v(l)), bm=(x(mid)>v(mid)), br=(x(r)>v(r));
        if (bm) swap(x, v);
        if (l==r || x==v || bl==br) return;
        build();
        if (bl!=bm) lptr->insert(x);
        else rptr->insert(x);
    }
    int query(int x)
    {
        if (l==r || lptr==nullptr) return v(x);
        build();
        if (x<=mid) return max(v(x), lptr->query(x));
        else return max(v(x), rptr->query(x));
    }
} *lct;

// Segment Tree Beats
struct SEG
{
    int l, r, mid;
    int sum, v;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r)
        {
            lptr=rptr=nullptr;
            sum=v=s[l];
        }
        else
        {
            lptr=new SEG(l, mid);
            rptr=new SEG(mid+1, r);
            sum=lptr->sum+rptr->sum;
            v=max(lptr->v, rptr->v);
        }
    }
    void update(int x, int y)
    {
        if (v<10) return;
        if (l==r)
        {
            sum=v=sod(v);
            return;
        }
        if (y<=mid) lptr->update(x, y);
        else if (x>=mid+1) rptr->update(x, y);
        else
        {
            lptr->update(x, mid);
            rptr->update(mid+1, y);
        }
        sum=lptr->sum+rptr->sum;
        v=max(lptr->v, rptr->v);
    }
    int query(int pos)
    {
        if (l==r) return v;
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    int sod(int x)
    {
        string str=to_string(x);
        int ans=0;
        for (auto i:str) ans+=(int)(i-'0');
        return ans;
    }
} *seg;

// Segment Tree
struct SEG
{
    int l, r, mid;
    int v, lazy;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lazy=0;
        if (l==r)
        {
            lptr=rptr=nullptr;
            v=s[l];
        }
        else
        {
            lptr=new SEG(l, mid);
            rptr=new SEG(mid+1, r);
            v=lptr->v+rptr->v;
        }
    }
    void update(int pos, int val)
    {
        if (l==r)
        {
            v=val;
            return;
        }
        prop();
        if (pos<=mid) lptr->update(pos, val);
        else rptr->update(pos, val);
        v=lptr->v+rptr->v;
    }
    void update(int x, int y, int val)
    {
        if (l==x && r==y)
        {
            v+=val*(r-l+1);
            lazy+=val;
            return;
        }
        prop();
        if (y<=mid) lptr->update(x, y, val);
        else if (x>=mid+1) rptr->update(x, y, val);
        else
        {
            lptr->update(x, mid, val);
            rptr->update(mid+1, y, val);
        }
        v=lptr->v+rptr->v;
    }
    int query(int pos)
    {
        if (l==r) return v;
        prop();
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    int query(int x, int y)
    {
        if (l==x && r==y) return v;
        prop();
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid)+rptr->query(mid+1, y);
    }
    void prop()
    {
        if (lazy==0) return;
        lptr->v+=lazy*(mid-l+1);
        lptr->lazy+=lazy;
        rptr->v+=lazy*(r-mid);
        rptr->lazy+=lazy;
        lazy=0;
    }
} *seg;

// Sparse Table
struct ST
{
    int st[N][L], lg[N]={0};
    
    ST()
    {
        for (int i=2; i<=n; i++) lg[i]=lg[i>>1]+1;
        for (int i=0; i<n; i++) st[i][0]=s[i];
        
        for (int j=1; (1<<j)<=n; j++)
        {
            for (int i=0; i+(1<<j)-1<n; i++)
            {
                st[i][j]=max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r)
    {
        int i=lg[r-l+1];
        return max(st[l][i], st[r-(1<<i)+1][i]);
    }
} *st;

// Sqrt Decomposition
struct SD
{
    int lptr[N], rptr[N];
    int v[N]={0}, lazy[N]={0};
    
    SD()
    {
        for (int j=0; j*B<n; j++)
        {
            lptr[j]=j*B;
            rptr[j]=min((j+1)*B-1, n-1);
            for (int i=lptr[j]; i<=rptr[j]; i++) v[j]+=s[i];
        }
    }
    void update(int pos, int val)
    {
        v[pos/B]+=val-s[pos];
        s[pos]+=val-s[pos];
    }
    void update(int l, int r, int val)
    {
        int bl=l/B, br=r/B;
        if (bl==br)
        {
            for (int i=l; i<=r; i++) s[i]+=val;
            v[bl]+=val*(r-l+1);
        }
        else
        {
            for (int j=bl+1; j<=br-1; j++)
            {
                v[j]+=val*(rptr[j]-lptr[j]+1);
                lazy[j]+=val;
            }
            for (int i=l; i<=rptr[bl]; i++) s[i]+=val;
            v[bl]+=val*(rptr[bl]-l+1);
            for (int i=lptr[br]; i<=r; i++) s[i]+=val;
            v[br]+=val*(r-lptr[br]+1);
        }
    }
    int query(int pos) { return s[pos]+lazy[pos/B]; }
    int query(int l, int r)
    {
        int ans=0;
        int bl=l/B, br=r/B;
        if (bl==br) for (int i=l; i<=r; i++) ans+=s[i]+lazy[bl];
        else
        {
            for (int j=bl+1; j<=br-1; j++) ans+=v[j];
            for (int i=l; i<=rptr[bl]; i++) ans+=s[i]+lazy[bl];
            for (int i=lptr[br]; i<=r; i++) ans+=s[i]+lazy[br];
        }
        return ans;
    }
} *sd;

// Trie
struct TRIE
{
    int ne[N][3], idx=1;
    int sz[N];
    
    TRIE() { for (int i=0; i<3; i++) fill(ne[i], ne[i]+N, -1); }
    void insert(int x)
    {
        int u=0;
        for (int i=L; i>=0; i--)
        {
            int cur=(x>>i)&1;
            if (ne[u][cur]==-1) ne[u][cur]=idx++;
            u=ne[u][cur];
            sz[u]++;
        }
    }
    int query(int x)
    {
        int u=0, ans=0;
        bool flag=1;
        for (int i=L; i>=0; i--)
        {
            int cur=(x>>i)&1, req=(m>>i)&1;
            cur^=req;
            if (req==1 && ne[u][!cur]!=-1) ans+=sz[ne[u][!cur]];
            if (ne[u][cur]==-1)
            {
                flag=0;
                break;
            }
            u=ne[u][cur];
        }
        if (flag) ans+=sz[u];
        return ans;
    }
} *trie;

// UFDS
int find(int x)
{
    if (g[x]==x) return x;
    else return g[x]=find(g[x]);
}
void unite(int x, int y)
{
    x=find(x); y=find(y);
    if (x==y) return;
    g[y]=x;
}

// Line Sweep
signed main()
{
	cin>>n;
    for (int i=0; i<n; i++)
	{
		cin>>h[i];
		s[i]={h[i], i};
	}
	sort(s, s+n);
	
    for (int i=0; i<n; i++)
	{
		if (s[i].sec==0 || h[s[i].sec-1]<s[i].fir) cur--;
		else if (h[s[i].sec-1]>s[i].fir) cur++;
		if (s[i].sec==n-1 || h[s[i].sec+1]<s[i].fir) cur--;
		else if (h[s[i].sec+1]>s[i].fir) cur++;
		if (i==n-1 || s[i].fir!=s[i+1].fir) ans=max(ans, cur/2);
	}
	cout<<ans<<endl;
	return 0;
}

// Linear Scan
void scan(int i)
{
    sort(st[i&1].begin(), st[i&1].end());
    for (auto b:st[i&1]) dp[i&1][b]=1e18;
    int k, minn;
    
    // scan left
    k=0, minn=1e18;
    for (auto j:st[i&1])
    {
        while (k<st[1-i&1].size() && st[1-i&1][k]<=j)
        {
            minn=min(minn, dp[1-i&1][st[1-i&1][k]]-(st[1-i&1][k]-*st[1-i&1].begin())*s[i]);
            k++;
        }
        if (minn!=1e18) dp[i&1][j]=min(dp[i&1][j], minn+(j-st[1-i&1][0])*s[i]);
    }
    
    // scan right
    k=st[1-i&1].size()-1, minn=1e18;
    for (int _=st[i&1].size()-1; _>=0; _--)
    {
        int j=st[i&1][_];
        while (k>=0 && st[1-i&1][k]>=j)
        {
            minn=min(minn, dp[1-i&1][st[1-i&1][k]]-(*st[1-i&1].rbegin()-st[1-i&1][k])*s[i]);
            k--;
        }
        if (minn!=1e18) dp[i&1][j]=min(dp[i&1][j], minn-(j-*st[1-i&1].rbegin())*s[i]);
    }
}

// Mo's Algorithm
void add(int pos)
{
    cnt[s[pos]]++;
    if (cnt[s[pos]]==1) cur++;
}
void del(int pos)
{
    cnt[s[pos]]--;
    if (cnt[s[pos]]==0) cur--;
}

    sort(q.begin(), q.end(), [](node x, node y)
    {
        if (x.l/B!=y.l/B) return x.l<y.l;
        else if ((x.l/B)&1) return x.r<y.r;
        else return x.r>y.r;
    });

// Monotonic Queue
signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    deque<int> q; q.push_back(0);
    for (int i=1; i<n; i++)
    {
        while (q.size() && q.front()<=i-m) q.pop_front();
        while (q.size() && s[q.back()]>s[i]) q.pop_back();
        q.push_back(i);
        if (i+1>=m) cout<<s[q.front()]<<' ';
    }
    cout<<endl;
    return 0;
}

// A-star Algorithm
struct node
{
    int d, u;
    bool operator<(const node x) const { return d+rd[u]>x.d+rd[x.u]; }
};
void dijkstra()
{
    bool vis[N]={0};
    for (int i=0; i<n; i++) rd[i]=1e18;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    rd[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:rs[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                q.push({rd[v], v});
            }
        }
    }
}
void astar()
{
    priority_queue<node> q;
    
    q.push({0, n-1});
    while (q.size())
    {
        auto [d, u]=q.top(); q.pop();
        if (u==0)
        {
            cnt++; ans[cnt]=d;
            if (cnt==k) return;
            continue;
        }
        for (auto [v, w]:s[u]) q.push({d+w, v});
    }
}

// BFS (0-1)
void bfs()
{
    fill(d, d+n, 1e18);
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (w==0) q.push_front(v);
                else q.push_back(v);
            }
        }
    }
}

// Condensation Graph
int n, m;
int x[M], y[M];
vector<int> s[N], rs[N];
int a[N], val[N]={0};
bool vis[N]={0};
stack<int> st;
int g[N];
int dp[N], ans;

void dfs_topo(int u)
{
    vis[u]=1;
    for (auto v:s[u]) if (!vis[v]) dfs_topo(v);
    st.push(u);
}
void dfs_scc(int u, int r)
{
    vis[u]=1; g[u]=r;
    val[r]+=a[u];
    for (auto v:rs[u]) if (!vis[v]) dfs_scc(v, r);
}
void dfs_dp(int u)
{
    vis[u]=1;
    for (auto v:s[u])
    {
        if (!vis[v]) dfs_dp(v);
        dp[u]=max(dp[u], dp[v]);
    }
    dp[u]+=val[u];
}

    for (int i=0; i<n; i++) if (!vis[i]) dfs_topo(i);
	fill(vis, vis+n, 0);
    while (st.size())
    {
        int u=st.top(); st.pop();
        if (!vis[u]) dfs_scc(u, u);
    }
    
    for (int i=0; i<n; i++) s[i].clear();
    for (int i=0; i<m; i++)
    {
        if (g[x[i]]!=g[y[i]])
        {
            x[i]=g[x[i]]; y[i]=g[y[i]];
            s[x[i]].push_back(y[i]);
        }
    }

// Dial's Algorithm
void dial()
{
	bool vis[N]={0};
	fill(d, d+n, 1e18);
	queue<int> q[W];
	
	q[0].push(0);
	d[0]=0;
	int cur=0, sz=1;
	while (sz>0)
	{
		while (!q[cur%W].size()) cur=(cur+1)%W;
		int u=q[cur].front(); q[cur].pop(); sz--;
		if (vis[u]) continue;
		vis[u]=1;
		
		for (auto [v, w]:s[u])
		{
			if (d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q[d[v]%W].push(v); sz++;
			}
		}
	}
}

// Dijkstra's Algorithm
void dijkstra()
{
    bool vis[N]={0};
    fill(d, d+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    d[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
            }
        }
    }
}

// Floyd-Warshall Algorithm
void floyd()
{
    for (int i=0; i<n; i++)
    {
        for (int u=0; u<n; u++)
        {
            for (int v=0; v<n; v++)
            {
                d[u][v]=min(d[u][v], d[u][i]+d[i][v]);
            }
        }
    }
}

// Johnson's Algorithm
bool spfa()
{
    bool inq[N]={0}; int cnt[N]={0};
    fill(rd, rd+n, 1e18);
    queue<int> q;
    
    q.push(n);
    rd[n]=0;
    inq[n]=1;
    cnt[n]=0;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (auto [v, w]:s[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                cnt[v]=cnt[u]+1;
                if (cnt[v]>n) return 0;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return 1;
}
void dijkstra(int src)
{
    bool vis[N]={0};
    fill(d, d+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, src});
    d[src]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
            }
        }
    }
}

    if (!spfa())
    {
        cout<<-1<<endl;
        return 0;
    }
    
    for (int u=0; u<n; u++)
    {
        for (int i=0; i<s[u].size(); i++)
        {
            s[u][i].sec+=rd[u]-rd[s[u][i].fir];
        }
    }
    for (int u=0; u<n; u++)
    {
        dijkstra(u);
        for (int v=0; v<n; v++)
        {
            if (d[v]==1e18) cout<<1e18<<' ';
            else cout<<d[v]+rd[v]-rd[u]<<' ';
        }
        cout<<endl;
    }

// SPFA Algorithm
void spfa()
{
    bool inq[N]={0};
    fill(d, d+n, 1e18);
    queue<int> q;
    
    q.push(0);
    d[0]=0;
    inq[0]=1;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
}

// Binary Exp & Mul
int mul(int x, int y)
{
    int ans=0;
    x%=mod; y%=mod;
    while (y)
    {
        if (y&1) ans=(ans+x)%mod;
        x=(2*x)%mod;
        y>>=1;
    } 
    return ans;
}
int pow(int x, int y)
{
    int ans=1;
    x%=mod;
    while (y)
    {
        if (y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans;
}

// Prime Sieve
void init()
{
    for (int i=2; i<=N; i++)
    {
        if (lp[i]==0)
        {
            lp[i]=i;
            p.push_back(i);
        }
        for (int j=0; i*p[j]<=N; j++)
        {
            lp[i*p[j]]=p[j];
            if (p[j]==lp[i]) break;
        }
    }
}

// __int128
inline bll read()
{
	bll x=0, f=1; char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x*f;
}
inline void print(bll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9) print(x/10);
	putchar(x%10+'0');
}

// Custom Hash
struct CHASH
{
    int h[N];
    
    CHASH() { fill(h, h+N, -1); }
    int add(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
    int find(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
} *chash;

// Discretization
void discretize()
{
    vector<int> t; for (int i=0; i<n; i++) t.push_back(s[i]);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int i=0; i<n; i++) s[i]=lower_bound(t.begin(), t.end(), s[i])-t.begin();
}

// Optimizations
#define getchar() getchar_unlocked()
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

inline int read()
{
	int x=0, f=1; char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x*f;
}
inline void print(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9) print(x/10);
	putchar(x%10+'0');
}

// PBDS
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define pbds_map gp_hash_table<int, int>;
#define pbds_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
#define pbds_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>; // cannot erase()

// Stress Testing
#include <chrono>
#include <random>

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct WRONG
{
    signed main() {}
} *wrong;

struct CORRECT
{
    signed main() {}
} *correct;

signed main()
{
    for (int _=0; _<100013; _++)
    {
        wrong=new WRONG; correct=new CORRECT;
        int out_wrong=wrong->main();
        int out_correct=correct->main();
        if (out_wrong!=out_correct)
        {
            cerr<<endl;
            cerr<<"WRONG: "<<out_wrong<<endl;
            cerr<<"CORRECT: "<<out_correct<<endl;
            return 0;
        }
        cerr<<"PASSED "<<_<<endl;
    }
    cerr<<"PASSED ALL"<<endl;
    return 0;
}

// BFS (double-ended)
int de_bfs()
{
    if (st==te) return 0;
    unordered_map<string, int> vis;
    queue<string> q;
    
    q.push(st); q.push(te);
    d[st]=d[te]=0;
    vis[st]=1; vis[te]=2;
    while (q.size())
    {
        string u=q.front(); q.pop();
        string ne=u;
        int x, y, cnt=0;
        while (cnt<9)
        {
            s[cnt/3][cnt%3]=ne[cnt]-'0';
            if (ne[cnt]=='0') { x=cnt/3; y=cnt%3; }
            cnt++;
        }
        for (int i=0; i<4; i++)
        {
            int tx=x+dx[i], ty=y+dy[i];
            if (0>tx || tx>=3 || 0>ty || ty>=3) continue;
            swap(s[x][y], s[tx][ty]);
            ne="";
            for (int j=0; j<3; j++) for (int k=0; k<3; k++) ne+=(char)('0'+s[j][k]);
            
            if (vis[ne]==vis[u])
            {
                swap(s[x][y], s[tx][ty]);
                continue;
            }
            if ((vis[ne]==1 && vis[u]==2) || (vis[ne]==2 && vis[u]==1)) return d[ne]+d[u]+1;
            
            q.push(ne);
            d[ne]=d[u]+1;
            vis[ne]=vis[u];
            swap(s[x][y], s[tx][ty]);
        }
    }
    return -1;
}

// Rabin-Karp Algorithm
struct RK
{
    const int mod[2]={1000000007, 1000000009};
    int pwr[2][N];
    unordered_map<string, vector<vector<int>>> h;
    
    RK()
    {
        pwr[0][0]=pwr[1][0]=1;
        for (int i=1; i<N; i++)
        {
            pwr[0][i]=(pwr[0][i-1]*131)%mod[0];
            pwr[1][i]=(pwr[1][i-1]*131)%mod[1];
        }
    }
    void insert(string x)
    {
        h[x].resize(2, vector<int>(lx+1));
        h[x][0][0]=h[x][1][0]=0;
        for (int i=0; i<lx; i++)
        {
            h[x][0][i+1]=(h[x][0][i]+x[i]*pwr[0][i])%mod[0];
            h[x][1][i+1]=(h[x][1][i]+x[i]*pwr[1][i])%mod[1];
        }
    }
    vector<int> query(string x, string y)
    {
        vector<int> ans;
        for (int i=0; i+ly-1<lx; i++) if (check(i, x, y)) ans.push_back(i);
        return ans;
    }
    bool check(int pos, string x, string y)
    {
        bool t1=calc(0, h[x][0][pos+ly]-h[x][0][pos]) == calc(0, h[y][0][ly]*pwr[0][pos]);
        bool t2=calc(1, h[x][1][pos+ly]-h[x][1][pos]) == calc(1, h[y][1][ly]*pwr[1][pos]);
        return t1 && t2;
    }
    int calc(int i, int x) { return (x%mod[i]+mod[i])%mod[i]; }
} *rk;

// Centroid Decomposition
struct CD
{
    int sz[N];
    
    CD()
    {
        for (int i=0; i<n; i++) fill(c[i], c[i]+L, -1);
        fill(lvl, lvl+n, -1);
        decomp(0, 0, 0);
    }
    void decomp(int u, int p, int dep)
    {
        dfs_sz(u, u);
        int cent=get(u, u, sz[u]);
        lvl[cent]=dep;
        dfs_c(cent, cent, dep, cent, 0);
        for (auto v:s[cent]) if (lvl[v]==-1) decomp(v, cent, dep+1);
    }
    int get(int u, int p, const int tsz)
    {
		for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            if (tsz<sz[v]*2) return get(v, u, tsz);
        }
        return u;
    }
    void dfs_sz(int u, int p)
    {
        sz[u]=1;
        for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            dfs_sz(v, u);
            sz[u]+=sz[v];
        }
    }
    void dfs_c(int u, int p, const int level, const int cent, int dep)
    {
        c[u][level]=cent; d[u][level]=dep;
        for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            dfs_c(v, u, level, cent, dep+1);
        }
    }
} *cd;

// Heavy-Light
struct HLD
{
    int dep[N], p[N], sz[N];
    int heavy[N], head[N];
    
    HLD()
    {
        fill(heavy, heavy+n, -1);
        dfs_sz(0);
        dfs_hl(0, 0);
    }
    void dfs_sz(int u)
    {
        sz[u]=1;
        for (auto v:s[u]) if (v!=p[u])
        {
            dep[v]=dep[u]+1; p[v]=u;
            dfs_sz(v);
            if (heavy[u]==-1 || sz[heavy[u]]<sz[v]) heavy[u]=v;
            sz[u]+=sz[v];
        }
    }
    void dfs_hl(int u, int H)
    {
        seq[idx]=u; pre[u]=idx++;
        head[u]=H;
        if (heavy[u]!=-1) dfs_hl(heavy[u], H);
        for (auto v:s[u]) if (v!=p[u] && v!=heavy[u]) dfs_hl(v, v);
        post[u]=idx-1;
    }
    void update(int x, int y, int val)
    {
        int fx=head[x], fy=head[y];
        while (fx!=fy)
        {
            if (dep[fx]<dep[fy])
            {
                swap(x, y);
                swap(fx, fy);
            }
            seg->update(pre[fx], pre[x], val);
            x=p[fx]; fx=head[x];
        }
        if (dep[x]>dep[y]) swap(x, y);
        seg->update(pre[x], pre[y], val);
    }
    int query(int x, int y)
    {
        int fx=head[x], fy=head[y]; int ans=0;
        while (fx!=fy)
        {
            if (dep[fx]<dep[fy])
            {
                swap(x, y);
                swap(fx, fy);
            }
            ans += seg->query(pre[fx], pre[x]);
            x=p[fx]; fx=head[x];
        }
        if (dep[x]>dep[y]) swap(x, y);
        return ans + seg->query(pre[x], pre[y]);
    }
} *hld;

// LCA (binary lifting)
struct LCA
{
    int pre[N], post[N], idx=0;
    int anc[N][L], dep[N];
    
    LCA()
    {
        for (int i=0; i<n; i++) fill(anc[i], anc[i]+L, -1);
        dep[0]=0; dfs(0, 0);
    }
    void dfs(int u, int p)
    {
        pre[u]=idx++;
        anc[u][0]=p;
        for (int i=1; i<L; i++)
        {
            anc[u][i]=anc[anc[u][i-1]][i-1];
            if (anc[u][i]==-1) break;
        }
        for (auto v:s[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
        }
        post[u]=idx-1;
    }
    bool check(int u, int v) { return pre[u]<=pre[v] && post[u]>=post[v]; }
    int query(int u, int v)
    {
        if (check(u, v)) return u;
        if (check(v, u)) return v;
        if (dep[u]>dep[v]) swap(u, v);
        for (int i=L-1; i>=0; i--) if (anc[u][i]!=-1 && !check(anc[u][i], v)) u=anc[u][i];
        return anc[u][0];
    }
} *lca;

// LCA (FCB Algorithm)
struct LCA
{
    int st[N][L], lg[N];
    int pre[N], dep[N], idx=0;
    
    LCA()
    {
        dep[0]=0; dfs(0, 0);
        for (int i=2; i<=idx; i++) lg[i]=lg[i>>1]+1;
        for (int j=1; (1<<j)<=idx; j++)
        {
            for (int i=0; i+(1<<j)-1<idx; i++)
            {
                st[i][j]=f(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    void dfs(int u, int p)
    {
        st[idx][0]=u; pre[u]=idx++;
        for (auto v:s[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
            st[idx][0]=u; idx++;
        }
    }
    int query(int u, int v)
    {
        u=pre[u]; v=pre[v];
        if (u>v) swap(u, v);
        int i=lg[v-u+1];
        return f(st[u][i], st[v-(1<<i)+1][i]);
    }
    int f(int u, int v) { return dep[u]<dep[v]?u:v; }
} *lca;

// Prim's Algorithm
int prim()
{
    int key[N]; bool vis[N]={0};
    fill(key, key+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    key[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:s[u])
        {
            if (key[v]>w)
            {
                key[v]=w;
                q.push({key[v], v});
            }
        }
    }
    
    int ans=0;
    for (int u=1; u<n; u++) ans+=key[u];
    return ans;
}

// Tarjan Algorithm & DFS Tree
void tarjan(int u, int p)
{
	vis[u]=1;
	pre[u]=low[u]=i++;
	int cnt=0;
	
    for (auto v:s[u])
	{
		if (v==p) continue;
		if (!vis[v])
		{
			tarjan(v, u);
			low[u]=min(low[u], low[v]);
			if (low[v]>=pre[u] && u!=p) cut[u]=1;
			cnt++;
		}
		else low[u]=min(low[u], pre[v]);
	}
	if (cnt>=2 && u==p) cut[u]=1;
}