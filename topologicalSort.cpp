#include <iostream>
#include <stdlib.h>


struct AdjListNode
{
	int dest;
	AdjListNode* next;
};

struct AdjList
{
	AdjListNode* head;
};

struct Graph
{
	int V;
	AdjList* array;
};

AdjListNode* newAdjListNode(int dest)
{
	AdjListNode* node = new AdjListNode;
	node->dest = dest;

	return node;
}

Graph* newGraph(int V)
{
	Graph* graph = new Graph;
	graph->V = V;

	graph->array = new AdjList[V];
	for (int i = 0; i < V; i++)
		graph->array[i].head = NULL;

	return graph;

}

void addEdge(Graph* graph, int src, int dest)
{
	AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void printGraph(Graph* graph)
{
	for(int v = 0; v < graph->V; v++)
	{
		AdjListNode* node = graph->array[v].head;
		std::cout << "list node:" << v << "\n";
		while(node)
		{
			std::cout << "->" << node->dest;
			node = node->next; 
		}
		std::cout << "\n";

	}

}

void dfs(int v, bool *used, Graph *graph, int *ans, int num_ans)
{
	used[v] = true;
	std::cout << v << "\n";
	AdjListNode *node = graph->array[v].head;
	if (node!=NULL)
	{
		//std::cout << "node is not null";
		while(node != NULL)
		{
			//std::cout << node->dest;
			int to = node->dest;
			node = node->next;
			if(!used[to])
			{
				//std::cout << "to: " << to << "\n";
				dfs(to, used, graph, ans, ++num_ans);
			}
		}

	}

	ans[num_ans] = v;
	return;
}

int main(int argc, char** argv)
{
	int V = atoi(argv[1]);
	int E = atoi(argv[2]);
	int src;
	int dest;
	Graph *graph = newGraph(V);

	for (int i = 0; i < E; i++)
	{
		std::cin >> src;
		std::cin >> dest;
		addEdge(graph, src-1, dest-1);	
	}
	
	printGraph(graph);

	bool *used = new bool[V]();
	int *ans = new int[V*E]();
	int num_ans = 0;

	for (int i = 0; i < V; i++)
	{
		if(!used[i])
			dfs(i, used, graph, ans, num_ans);
	}

	for(int i = 0; i < V*E; i++)
		std::cout << ans[i] << " ";
	
	return 0;

}