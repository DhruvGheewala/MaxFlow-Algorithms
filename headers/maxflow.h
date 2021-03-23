#ifndef __INCLUDED_MAX_FLOW_BASE_CLASS_ONCE__
#define __INCLUDED_MAX_FLOW_BASE_CLASS_ONCE__

#include "bits/stdc++.h"
using namespace std;

class MaxFlowBase {
protected:
    struct Edge {
        int from, to;
        int flow, cost;
        int capacity, originalCost;
        Edge *residual;

        Edge() {}
        Edge(int _from, int _to, int _capacity, int _cost = 0) {
            flow = 0;
            from = _from;
            to = _to;
            capacity = _capacity;
            originalCost = cost = _cost;
        }

        bool isResidual() {
            return capacity == 0;
        }

        int remainingCapacity() {
            return capacity - flow;
        }

        void augment(int bottleNeck) {
            flow += bottleNeck;
            residual -> flow -= bottleNeck;
        }
    };

    bool solved;
    int s; // src
    int t; // sink
    int n; // no. of nodes(including src, sink)
    int maxFlow = 0, minCost = 0;
    const int INF = numeric_limits<int>::max() >> 1;

    vector<vector<Edge>> g;
    vector<bool> minCut;

    int visitedToken;
    vector<int> visited;

public:
    MaxFlowBase(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;

        solved = false;
        visitedToken = 0;
        visited.assign(n + 1, -1);
        minCut.assign(n + 1, false);

        g.clear();
        g.resize(n + 1);
    }

    void addEdge(int from, int to, int capacity, int cost = 0) {
        assert(capacity > 0);

        Edge e1 = Edge(from, to, capacity, cost);
        Edge e2 = Edge(to, from, 0, -cost);

        e1.residual = &e2;
        e2.residual = &e1;

        g[from].push_back(e1);
        g[to].push_back(e2);
        solved = false;
    }

    void visit(int i) {
        assert(i < visited.size());
        visited[i] = visitedToken;
    }

    bool isVisited(int i) {
        assert(i < visited.size());
        return visited[i] == visitedToken;
    }

    void markAllNodesUnvisited() {
        visitedToken++;
    }

    int getMaxFlow() {
        execute();
        return maxFlow;
    }

    int getMinCost() {
        execute();
        return minCost;
    }

    vector<vector<Edge>> getGraph() {
        execute();
        return g;
    }

    vector<bool> getMinCut() {
        execute();
        return minCut;
    }

    void execute() {
        if(solved) return;
        solve();
        solved = true;
    }

    virtual void solve() = 0;
};

#endif