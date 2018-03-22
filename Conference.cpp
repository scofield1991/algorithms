#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
	int dest;

	int start;
	int end;
	int time;
};


Node createNode(int start, int end, int numPrograms)
{
	Node node;
	node.start = start;
	node.end = end;
	node.time = end - start;

	return node;
}


bool checkAdj(Node* programNodes, int indCur, int indPrev)
{
	if(indPrev == -1 || programNodes[indCur].start >= programNodes[indPrev].end)
		return true;
	return false;
}

int maxTime(Node* programNodes, int numPrograms, int prev_a = -1, int prev_b = -1, int cur_index = 0, int a = 0, int b = 0, int c = 0)
{
	if(cur_index == numPrograms)
		return (a + b + c);

	int maxTime_1 = 0;
	int maxTime_2 = 0;
	int maxTime_3 = 0;
	int maxTime_all = 0;

	Node curTime = programNodes[cur_index];
	int timeLength = curTime.time;

	if(checkAdj(programNodes, cur_index, prev_a))
		maxTime_1 = maxTime(programNodes, numPrograms, cur_index, prev_b, cur_index+1, a + timeLength, b, c);

	if(checkAdj(programNodes, cur_index, prev_b))
		maxTime_2 = maxTime(programNodes, numPrograms, prev_a, cur_index, cur_index+1, a, b + timeLength, c);

	maxTime_3 = maxTime(programNodes, numPrograms, prev_a, prev_b, cur_index+1, a, b, c);

	if (maxTime_1 > maxTime_all)
		maxTime_all = maxTime_1;

	if (maxTime_2 > maxTime_all)
		maxTime_all = maxTime_2;

	if (maxTime_3 > maxTime_all)
		maxTime_all = maxTime_3;

	return maxTime_all;
}

int main(int argc, char** argv)
{
	int numTestCases;
	cin >> numTestCases;

	for(int testCase = 0; testCase < numTestCases; testCase++)
	{
		int numPrograms;
		cin >> numPrograms;

		Node* programNodes = new Node[numPrograms];

		for(int prog = 0; prog < numPrograms; prog++)
		{
			int startHours, startMinutes, endHours, endMinutes;
			int start, end;

			cin >> startHours;
			cin >> startMinutes;
			cin >> endHours;
			cin >> endMinutes;

			start = startHours * 60 + startMinutes;

			end = endHours * 60 + endMinutes;

			//cout << "crate mode num: " << prog << '\n';
			//cout << "strat: " << start << " end: " << end << "\n";
			programNodes[prog] = createNode(start, end, numPrograms);

			//for(int i = 0; i < prog; i++)
			//{
			//	if(start >= programNodes[i].end || end <= programNodes[i].start )
			//	{
			//		programNodes[i].adjacent[prog] = true;
			//	}
			//}

		}

		for(int prog = 0; prog < numPrograms; prog++)
		{
			
			for(int i = prog+1; i < numPrograms; i++)
			{
				if(programNodes[prog].start > programNodes[i].start)
				{
					Node temp = programNodes[prog];
					programNodes[prog] = programNodes[i];
					programNodes[i] = temp;
				}
			}
		}

		int answer = maxTime(programNodes, numPrograms);

		cout << answer << "\n";

	}

}