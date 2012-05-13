#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 30010
#define INF 3000000
#define MAXD 5010

class Monopoly
{
private:
	int gD;
	int find(int a);
	int merge (int a, int b);
	int getResult (int a, int d);
	vector <int> parent;
	vector <int> store;
	vector <vector <int> > cache;
public:
	Monopoly(int a, int b) : cache(a)
	{
		parent.assign(a, 0);
		store.assign(b, 0);
		vector<int> tmp(b);
		for (int i = 0; i < a; ++i) cache[i] = tmp;
	}
	int testcase();
};

int Monopoly::find(int a)
{
    if (a == parent[a]) 
		return a;
    return parent[a] = find(parent[a]);
}

int Monopoly::merge(int a, int b)
{
    a = find(a);
    b = find(b);
    return parent[a] = b;
}

int Monopoly::getResult(int a, int d){
    if (gD < d) 
		return INF;
    return cache[a][d];
}

int Monopoly::testcase()
{
    int n, d; 
	cin >> n >> d;
    gD = d;
    for (int i = 0; i < n; i++)
	{
        parent[i] = i;
        for (int j = 0; j <= d; j++)
		{
			cache[i][j] = 1;
		}
    }
    for (int w = 0; w < n-1; w++)
	{
        int a, b; 
		cin >> a >> b;
        a--; b--;
        a = find(a);
        b = find(b);
        
        int bb = INF, aa = INF;

        for (int i = 0; i <= d; i++) 
		{
			bb = min(bb, getResult(b, i));
		}
        for (int i = 0; i <= d; i++) 
		{
			aa = min(aa, getResult(a, i));
		}

        int old = INF;

        for (int i = d; i >= 0; i--)
		{
            int tmp = max(getResult(a, i+1), bb + 1);
            tmp = min(tmp, max(getResult(b, i+1), aa + 1));
            tmp = min(tmp, old);
            old = tmp;
            store[i] = tmp;
        }

        int c = merge(a, b);

        for(int i = 0; i <= d; i++)
		{
            cache[c][i] = store[i];
        }
    }
    return getResult(find(0), 0);
}

int main()
{
	int n; 
	cin >> n;
	Monopoly mono (MAXN, MAXD);
	for(int i = 1; i <= n; i++)
	{
		cout << "Case #" << i << ": " << mono.testcase();
	}
	//system ("pause");
	return 0;
}