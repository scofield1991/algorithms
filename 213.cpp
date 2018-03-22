#include <iostream>
#include <stdlib.h> 

using namespace std;

struct battleship
{
  int num = 0;
  int *tunels_num = new int[100]();

};

int main(int argc, char** argv)
{
  int N = atoi(argv[1]); // number of stars
  int M = atoi(argv[2]); // number ot tunels
  int S = atoi(argv[3])-1; // Dark Lord position
  int T = atoi(argv[4])-1; // Empire position

  int graph[N][N];
  for (int i = 0; i < N; i++)
  {
  	for (int j = 0; j < N; j++)
  	  graph[i][j] = 0;
  }


  int tunel_num = 0;
  for (int i = 0; i < M; ++i)
  {
  	int star_1, star_2;
  	cin >> star_1;
  	cin >> star_2;
  	graph[star_1-1][star_2-1] = ++tunel_num;
  }

  int queue[1000];
  int front = 0;
  int rear = 0;
  int level = 0;
  queue[rear++] = S;

  int *used = new int[N]();
  int *distances = new int[N]();
  int *parents = new int[N]();
  used[S] = 1;
  parents[S] = -1;
  distances[S] = 0;
  int distance_prev = 0;
  //int parent_prev = -1;
  int num_cristal_types = 0;
  battleship *battleships = new battleship[1000];
  int num_battleships[100];



  while(front != rear)
  {
  	int v = queue[front++];
  	if(v == T)
  		break;
  	//cout << "v: " << v << "\n";
  	


  	for(int i = 0; i < N; i++)
  	{
  		if(graph[v][i] != 0)
  		{
  			int to = i;
  			if(used[to] == 0)
  			{
  				used[to] = 1;
  				queue[rear++] = to;
  				distances[to] = distances[v] + 1;
  				parents[to] = v;

  			}
  			//cout << "distances[v]: " << distances[v] << "\n";
  			// if prev star on the same level then just add battleship
  			if(distance_prev == distances[v])
  			{
  				num_battleships[num_cristal_types]++;
  				int num = battleships[num_cristal_types].num;
  				battleships[num_cristal_types].tunels_num[num] = graph[v][i];
  				battleships[num_cristal_types].num++;
  			}
  			// if stars on different layers then add new crystal
  			else
  			{  	
  				distance_prev = distances[v];		
  				num_cristal_types++;
  				num_battleships[num_cristal_types]++;
  				int num = battleships[num_cristal_types].num;
  				battleships[num_cristal_types].tunels_num[num] = graph[v][i];
  				battleships[num_cristal_types].num++;
  			}
  		}

  	}

  }

  cout << "num_cristal_types: " << num_cristal_types+1 << "\n";
  for (int i = 0; i < num_cristal_types+1; i++)
  {	
  	cout << battleships[i].num  << " ";

  	for (int j = 0; j < battleships[i].num; j++)
  	{
  		cout  << battleships[i].tunels_num[j] << " ";
  	}
  	cout << "\n";

  }


}