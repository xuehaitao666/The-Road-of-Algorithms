#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;//你在看我的代码对吧 
const LL N=100010;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
LL T,n,w,h,C[N];
struct Segment{
	LL l,r,h;
	LL val;
	bool operator <(const Segment &a)const{
		return (h!=a.h)?h<a.h:val>a.val;
	}
}Seg[N<<2];
struct SegmentTree{
	LL l,r;
	LL mx,add;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define mx(x) tree[x].mx
	#define add(x) tree[x].add
}tree[N<<2];
void init(){
	memset(Seg,0,sizeof(Seg));
	memset(tree,0,sizeof(tree));
}
void Pushup(LL x){
	mx(x)=max(mx(x<<1),mx(x<<1|1));
}
void Build(LL x,LL l,LL r){
	l(x)=l,r(x)=r,mx(x)=add(x)=0;
	if(l==r)return;
	LL mid=(l+r)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
}
void Pushdown(LL x){
	mx(x<<1)+=add(x);
	mx(x<<1|1)+=add(x);
	add(x<<1)+=add(x);
	add(x<<1|1)+=add(x);
	add(x)=0;
}
void Change(LL x,LL L,LL R,LL d){
	LL l=l(x),r=r(x);
	if(L<=l&&r<=R){
		mx(x)+=d;
		add(x)+=d;
		return;
	}
	Pushdown(x);
	LL mid=(l+r)>>1;
	if(L<=mid)Change(x<<1,L,R,d);
	if(R>mid)Change(x<<1|1,L,R,d);
	Pushup(x);
}
int main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld%lld%lld",&n,&w,&h);
		for(LL i=1;i<=n;i++){
			LL x,y,l;
			scanf("%lld%lld%lld",&x,&y,&l);
			C[(i<<1)-1]=y;
			C[i<<1]=y+h-1;
			Seg[(i<<1)-1]=(Segment){y,y+h-1,x,l};
			Seg[i<<1]=(Segment){y,y+h-1,x+w-1,-l};
		}
		n<<=1;
		sort(C+1,C+n+1);
		sort(Seg+1,Seg+n+1);
		LL cnt=unique(C+1,C+n+1)-C-1;
		for(LL i=1;i<=n;i++){
			LL pos1=lower_bound(C+1,C+cnt+1,Seg[i].l)-C;
			LL pos2=lower_bound(C+1,C+cnt+1,Seg[i].r)-C;
			Seg[i].l=pos1;
			Seg[i].r=pos2;
		}
		Build(1,1,cnt);
		LL ans=0;
		for(LL i=1;i<=n;i++){
			Change(1,Seg[i].l,Seg[i].r,Seg[i].val);
			ans=max(ans,mx(1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
