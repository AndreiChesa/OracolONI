#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

ifstream f("oracol.in");
ofstream g("oracol.out");

int n;
const int NMAX = 1005;
struct nod
{
	int x, y;
	int cost;
};

vector<nod>G;
vector<pair<int,int>>G2[NMAX];

int mat[NMAX][NMAX];

int cost_minim = 0;
bool viz[NMAX];

/*
void dij(int nod)
{
	priority_queue<pair<int,int>> pq;
	pq.push({ 0,nod });
	bool times = 0;
	
	while(!pq.empty())
	{
		int nod_curent = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		
		if (viz[nod_curent])
			continue;
		
		if (times == 1)
		{
			viz[nod_curent] = 1;
		}
		else {
			times = 1;
		}
		cost_minim += cost;

		for (auto it : G2[nod_curent])
		{
			if (!viz[it.first])
			{
				pq.push({ -it.second,it.first });
			}
		}
	}
}*/

int repr[NMAX];

int find(int x)
{
	if (x == repr[x])
		return x;
	return repr[x] = find(repr[x]);
}

void do_union(int x, int y)
{
	int x1 = find(x);
	int y1 = find(y);

	if (x1 < y1)
	{
		repr[y1] = x1;
	}
	else
	{
		repr[x1] = y1;
	}
}

int main()
{
	f >> n;
	int ct;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			f >> ct;
			G.push_back({ i-1,j,ct });
		}
	}

	for (int i = 0; i <= n; i++)
	{
		repr[i] = i;
	}
	sort(G.begin(), G.end(), [](nod a, nod b) {
		return a.cost < b.cost;
	});

	int i = 0;
	int marime = G.size();

	while (i < marime)
	{
		int x = G[i].x;
		int y = G[i].y;
		int cost = G[i].cost;

		if(find(x) != find(y))
		{
			cost_minim += cost;
			do_union(x, y);
		}
		i++;
	}

	g << cost_minim;

}