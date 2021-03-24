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

    bool solved, edgeListChanged;
    int s; // src
    int t; // sink
    int n; // no. of nodes(including src, sink)
    int maxFlow, minCost;
    const int INF = numeric_limits<int>::max() >> 1;

    // adj[u].push_back({v, w, +cost})
    // adj[v].push_back({u, 0, -cost}) <--- residual edge
    vector<int> residualSize;
    vector<vector<vector<int>>> adj;
    vector<vector<Edge>> g;
    vector<bool> minCut;

    int visitedToken;
    vector<int> visited;

public:
    MaxFlowBase(int _n) : MaxFlowBase(_n, 0, _n) {}

    MaxFlowBase(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        clear();
    }

    void updateSource(int _s) {
        assert(0 <= _s && _s < g.size());
        s = _s;
        solved &= s == _s;
    }

    void updateSink(int _t) {
        assert(0 <= _t && _t < g.size());
        t = _t;
        solved &= t == _t;
    }

    void addEdge(int from, int to, int capacity, int cost = 0) {
        assert(capacity > 0);

        adj[from].push_back({to, capacity, cost});
        residualSize[to]++;
        
        solved = false;
        edgeListChanged = true;
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
        if(edgeListChanged) {
            updateEdgeList();
        }

        solve();
        solved = true;
    }

    /**
     * This function will generate the graph g
     */
    void updateEdgeList() {
        g.clear();
        g.resize(n + 1);

        vector<int> ptr(n + 1, 0);
        for(int i = 0; i <= n; i++) {
            g[i].resize(adj[i].size() + residualSize[i]);
        }

        int m, u, v, w, cost;
        for(int i = 0; i <= n; i++) {
            m = adj[i].size();
            for(int j = 0; j < m; j++) {
                u = i;
                v = adj[i][j][0];
                w = adj[i][j][1];
                cost = adj[i][j][2];

                g[u][ptr[u]] = Edge(u, v, w, cost);
                g[v][ptr[v]] = Edge(v, u, 0, -cost);

                g[u][ptr[u]].residual = &g[v][ptr[v]];
                g[v][ptr[v]].residual = &g[u][ptr[u]];

                ptr[u]++;
                ptr[v]++;
            }
        }
        edgeListChanged = false;
    }

    void clear() {
        solved = false;
        edgeListChanged = false;
        visitedToken = 0;
        visited.assign(n + 1, -1);
        minCut.assign(n + 1, false);

        g.clear();
        g.resize(n + 1);

        adj.clear();
        adj.resize(n + 1);

        residualSize.clear();
        residualSize.assign(n + 1, 0);
    }

    virtual void solve() = 0;
};

#endif