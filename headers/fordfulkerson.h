#ifndef __INCLUDED_FORD_FULKERSON_CLASS_ONCE__
#define __INCLUDED_FORD_FULKERSON_CLASS_ONCE__

#include "bits/stdc++.h"
#include "maxflow.h"
using namespace std;

class FordFulkerson : public MaxFlowBase {
private:
	/**
	 * @param u - current node
	 * @param flow - bottleNeck flow for choosen path
	 * @return bottleNeck value for choosen path
	 */
	int dfs(int u, int flow) {
		if(u == t) return flow;
		visit(u);

		int rCapacity;
		for(Edge &e: g[u]) {
			rCapacity = e.remainingCapacity();
			if(rCapacity > 0 && !isVisited(e.to)) {
				int bottleNeck = min(flow, rCapacity);
				bottleNeck = dfs(e.to, bottleNeck);
				if(bottleNeck > 0) {
					e.augment(bottleNeck);
					return bottleNeck;
				}
			}
		}
		return 0;
	}

public:
	FordFulkerson(int _n = 0, int _s = 0, int _t = 0) : MaxFlowBase(_n, _s, _t) {}

	void solve() {
		// we will run dfs untill we get non-augmenting path
		for(int f = dfs(s, INF); f > 0; f = dfs(s, INF)) {
			maxFlow += f;
			markAllNodesUnvisited();
		}

		// Finding minCut
		for(int i = 0; i <= n; i++) {
			minCut[i] = isVisited(i);
		}
		markAllNodesUnvisited();
	}
};

#endif