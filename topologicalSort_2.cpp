#include <iostream>
#include <stdlib.h>

struct AdjListNode
{
	int dest;
	AdjListNode *next;
};

struct AdjList
{
	AdjListNode *head;
};

struct Graph
{
	int V;
	AdjList *array;
};

AdjListNode* newNode(int dest)
{
	AdjListNode *node = new AdjListNode;
	node->dest = dest;

	return node;
}

Graph *newGraph(int V)
{
	Graph *graph = new Graph;
	graph->V = V;
	graph->array = new AdjList[V];

	for (int i = 0; i < V; i++)
	{	
		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(Graph* graph, int src, int dst)
{
	AdjListNode *node = newNode(dst);
	node->next = graph->array[src].head;
	graph->array[src].head = node;
}

void printGraph(Graph *graph)
{
	int V = graph->V;

	for(int i = 0; i < V; i++)
	{
		AdjListNode *node = graph->array[i].head;
		std::cout << "Node: " << i << "->";
		while(node)
		{
			std::cout << node->dest << "->";
			node = node->next;
		}

		std::cout << "\n";
	}
}

void dfs(Graph *graph, int v, bool *used, int *ans, int &num_ans)
{
	used[v] = true;

	AdjListNode *node = graph->array[v].head;

	int pos = num_ans;

	while(node)
	{
		int to = node->dest;
		node = node->next;

		if(!used[to])
		{
			//std::cout  << "num_ans: " << num_ans <<  " v: " << v << " to: " << to << "\n";
			dfs(graph, to, used, ans, ++num_ans);
		}
		else
		{
			++num_ans;
		}
	}

	std::cout << "pos: " << num_ans << " v: " << v << "\n";
	ans[pos] = v;
}

void topologicalSort(Graph *graph, bool *used, int *ans)
{
	int v = graph->V;


}

int main(int argc, char **argv)
{
	int v = atoi(argv[1]);
	int e = atoi(argv[2]);
	Graph *graph = newGraph(v);

	for (int i = 0; i < e; i++)
	{
		int src, dest;
	    std::cin >> src;
	    std::cin >> dest;

	    addEdge(graph, src-1, dest-1);
	}

	printGraph(graph);

	bool *used = new bool[v];
	int *ans = new int [v*e];
	int num_ans = 0;

	for (int i = 0; i < v; i++)
	{
		if(!used[i])
		{
			dfs(graph, i, used, ans, num_ans);
			num_ans++;
		}

		std::cout << "num_ans: " << num_ans << "\n";

			for (int i = 0; i < v*e; i++)
				std::cout << ans[i];
			std::cout << "\n";
	}

	//for (int i = 0; i < v*e; i++)
	//	std::cout << ans[i];
	//std::cout << "\n";

	return 0;
}