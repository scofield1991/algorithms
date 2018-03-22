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

struct Stack
{
	int i;
	int *stackArray;

	Stack(int v)
	{
		i = -1;
		stackArray = new int[v];
	}

	void push(int v)
	{
		i++;
		stackArray[i] = v;
		
	}

	int pop()
	{
		
		int v = stackArray[i];
		i--;
		
		return v;
	}

	bool isEmpty()
	{
		if (i == -1)
			return true;
		return false;
	}
	
};

AdjListNode* createNewNode(int dest)
{
	AdjListNode* node = new AdjListNode;
	node->dest = dest;
	
	return node;
}

void addEdge(Graph* graph, int src, int dest)
{
	AdjListNode* node = createNewNode(dest);
	node->next = graph->array[src].head;
	graph->array[src].head = node;
}

Graph* newGraph(int V)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->array = new AdjList[V];

	for(int i = 0; i < V; i++)
	{
		graph->array[i].head = NULL;
	}

	return graph;
}

Graph* graphTranspose(Graph* graph)
{
	Graph* transposeGraph = newGraph(graph->V);
	for(int i = 0; i < graph->V; i++)
	{
		AdjListNode* node = graph->array[i].head;
		while(node)
		{
			int to = node->dest;
			//AdjListNode* transposeNode = createNewNode(i);
			addEdge(transposeGraph, to, i);
			node = node->next;
		}
	}
	return transposeGraph;
}

void printGraph(Graph* graph)
{
	for(int i = 0; i < graph->V; i++)
	{
		std::cout << "vertex " <<  i << ": ";
		AdjListNode* node = graph->array[i].head;
		while(node)
		{
			int to = node->dest;
			std::cout << to << " ";
			node = node->next;
		}
		std::cout << "\n";
	}
}



void dfs(Graph* graph, int v, bool *visited, Stack &vStack, bool scc = false)
{
	visited[v] = true;
	AdjListNode *node = graph->array[v].head;

	if(scc)
		std::cout << v << " ";

	while(node)
	{
		int to = node->dest;
		node = node->next;

		if (!visited[to])
		{
			if(scc)
				dfs(graph, to, visited, vStack, true);
			else
				dfs(graph, to, visited, vStack);
		}

	}
	//std::cout << "push to Stack: " << v << " ";
	vStack.push(v);
}



int main(int argc, char** argv)
{
	int v = atoi(argv[1]);
	int e = atoi(argv[2]);
	Graph *graph = newGraph(v);

	for (int i = 0; i < e; i++)
	{
		int src, dest;
	    std::cin >> src;
	    std::cin >> dest;

	    addEdge(graph, src, dest);
	}

	printGraph(graph);

	Stack vStack(10);
	bool *visited = new bool[graph->V];

	for (int i = 0; i < graph->V; i++)
	{
		if(!visited[i])
			dfs(graph, i, visited, vStack);
	}
	//while(!vStack.isEmpty())
	//	std::cout << vStack.pop() << " ";
	//std::cout << "\n";

	Graph* transposeGraph = graphTranspose(graph);
	printGraph(transposeGraph);

	Stack emptyStack(10);
	visited = new bool[graph->V];

	while(!vStack.isEmpty())
	{
		v = vStack.pop();
		if(!visited[v])
		{
			dfs(transposeGraph, v, visited, emptyStack, true);
			std::cout << "\n";
		}
	}


}