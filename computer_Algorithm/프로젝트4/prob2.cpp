#include <iostream>
#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <vector>

/*
	코드 구현에 감이 안 와서 Dijkstra 구현을 외부 코드를 참조했습니다.
	구현된 코드를 분석하고, 이를 이해하는 것을 중점적으로 하였고, 보고서에도 그렇게 썼으니 참고 부탁드립니다.
*/


typedef long long ll;
using namespace std;

#define INF 987654321

struct Edge {
	int v;
	int w;
	Edge() {};
	Edge(int v, int w) : v(v), w(w) {}
	bool operator > (const Edge &a) const {
		return w < a.w;
	}
};

vector<vector<Edge> > graph;
int n, m;

vector<int> dijkstra(int source)
{
	vector<int> dis(n + 1, INF);
	vector<int> parent(n + 1, -1);
	dis[source] = 0;
	priority_queue < Edge, vector<Edge>, greater<Edge> > pq;
	pq.push(Edge(source, 0));
	while (!pq.empty())
	{
		int here = pq.top().v;
		int cost = pq.top().w;
		pq.pop();
		if (dis[here] < cost) continue;
		for (Edge next : graph[here]) 
		{
			int next_cost = cost + next.w;
			if (dis[next.v] > next_cost)
			{
				dis[next.v] = next_cost;
				pq.push(Edge(next.v, next_cost));
				parent[next.v] = here;
			}
		}
	}
	vector<int> result(n + 1, -1);
	for (int i = 1; i <= n; ++i)
	{
		int temp = i;
		if (source != temp && parent[temp] != -1)
		{
			while (parent[temp] != source && result[temp] == -1)
				temp = parent[temp];
			if (result[temp] == -1)
				result[i] = temp;
			else
				result[i] = result[temp];
		}
	}
	return result;
}

int main() {

	cin >> n;
	cin >> m;

	graph = vector<vector<Edge> >(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u;
		cin >> v;
		cin >> w;
		graph[u].push_back(Edge(v, w));
		graph[v].push_back(Edge(u, w));

	}
	for (int i = 1; i <= n; ++i)
	{
		vector<int> ans = dijkstra(i);
		for (int i = 1; i <= n; i++) {
			if (ans[i] == -1)
				cout << "- ";
			else
				cout << ans[i] << " ";
		}
		cout << "\n";
	}
	//system("pause");
	return 0;
}
