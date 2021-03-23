#include "bits/stdc++.h"
#include "headers/maxflow.h"
#include "headers/fordfulkerson.h"
using namespace std;

/**
 * takes the input from given file
 * @param  inputFile location of the input file
 * @return           max-flow solver class
 */
FordFulkerson takeInput(const string &inputFile) {
	ifstream fin(inputFile);
	
	int n, m, s, t;
	fin >> n >> m >> s >> t;
	FordFulkerson maxFlowSolver(n, s, t);

	int u, v, w;
	for(int i = 0; i < m; i++) {
		fin >> u >> v >> w;
		maxFlowSolver.addEdge(u, v, w);
	}
	return maxFlowSolver;
}

int main(int argc, char const *argv[])
{
	// FordFulkerson maxFlowSolver = takeInput("Testcases/small_testcase_1.txt");
	FordFulkerson maxFlowSolver = takeInput("Testcases/small_testcase_2.txt");
	cout << "Maximun Flow for given graph is: " << maxFlowSolver.getMaxFlow() << endl;  // O(max_flow * m)

	// It won't recalculate untill you change the graph
	// cout << "Maximun Flow for given graph is: " << maxFlowSolver.getMaxFlow() << endl;  // O(1)

	// Now it will recalculate the answer, because we are changing the graph
	// For small_testcase_1.txt file
	// maxFlowSolver.addEdge(0, 3, 1000);
	// maxFlowSolver.addEdge(3, 10, 1000);
	// maxFlowSolver.addEdge(10, 11, 1000);
	// cout << "Maximun Flow for given graph is: " << maxFlowSolver.getMaxFlow() << endl;  // O(max_flow * m)
	
	// Now it will recalculate the answer, because we are changing the graph
	maxFlowSolver.addEdge(0, 1, 1000);
	maxFlowSolver.addEdge(1, 3, 1000);
	maxFlowSolver.addEdge(3, 5, 1000);
	cout << "Maximun Flow for given graph is: " << maxFlowSolver.getMaxFlow() << endl;  // O(max_flow * m)
	return 0;
}