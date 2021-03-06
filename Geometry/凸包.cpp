// 点集凸包
// 如果不希望在凸包的边上有输入点,把两个 <= 改成 <
// 注意:输入点集会被修改
struct P
{
    double x, y;
    P() {}
    P(double xx, double yy) { x=xx, y=yy; }
    P operator - (P b) { return P(x-b.x, y-b.y); }
    bool operator < (P b) const
    {
        return x < b.x || (x == b.x && y < b.y);
    }
    bool operator == (P b) const
    {
        return x==b.x && y==b.y;
    }
} p[233];
double dis(P a, P b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int dcmp(double x) {return x<1e-8 ? -1 : x>1e-8;}
bool cmp(P a, P b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
double Cross(P a, P b) { return a.x * b.y - a.y *b.x; }

vector<P> ConvexHull(vector<P>& p)
{
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    int n=p.size();
    int m=0;
    vector<P> ch(n+1);
    for(int i=0; i<n; i++)
    {
        while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<0) m--;
        ch[m++]=p[i];
    }
    int k=m;
    for(int i=n-2; i>=0; i--)
    {
        while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<0) m--;
        ch[m++]=p[i];
    }
    if(n>1) m--;
    ch.resize(m);
    return ch;
}
bool In(vector<P> p, P b)  /// 是否在凸包边界或者内部
{
	int n = p.size();
	int sign = 0;
	for (int i=0;i<n;i++) {
		int x = cmp(det(p[i] - b, p[(i+1)%n] - b) );
		if (x) {
			if (sign==0) sign = x;
			else if (sign - x)  return false;
		}
	}
	return true;
}
bool on(P p, P s, P t)  ///判断点是否在线段上（包括端点）
{
    return cmp(dis(p, s) + dis(p, t) - dis(s, t)) == 0;
}
bool On(vector<P> p, P b)  /// 是否在凸包边界上
{
	int n = p.size();
	for (int i=0;i<n;i++) {
		if (on(b, p[i] , p[(i+1)%n] ) ) return true;
	}
	return false;
}
