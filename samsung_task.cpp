//============================================================================
// Name        : samsung_task.cpp
// Author      : Alex
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

const int N = 10;
const int N_ops = 4;
int nums[N] = {0};
int op_visited[N_ops] = {0};
int op_variant[N] = {0};
int total_permutations = 0;


void f(int n, int len)
{

	if(n == len)
	{
		if(op_visited[3] > 0)
		{
			int num = nums[0];
			int num_left = -1;
			int num_right = 0;
			for(int i = 1; i < n+1; i++)
			{
				if(op_variant[i-1] == 0)
					num += nums[i];
				if(op_variant[i-1] == 1)
					num *= nums[i];
				if(op_variant[i-1] == 2)
				{
					if(nums[i] != 0)
						num %= nums[i];
					else
						return;
				}
				if(op_variant[i-1] == 3)
				{
					num_left = num;
					num = nums[i];
				}

				std::cout << op_variant[i-1] << " ";
			  }

				if(num_left == num)
				{
					std::cout << "num_left: " << num_left << "\n";
					std::cout << "num_right: " << num << "\n";
					total_permutations++;
				}
				std::cout << "\n";
			}
		return;

	}

	for(int i = 0; i < N_ops; i++)
	{
		if(i == 3)
		{
			if(op_visited[i] == 0)
			{
				op_variant[n] = i;
				op_visited[i]++;
				f(n+1, len);
				op_visited[i]--;
			}

		}
		else
		{

			op_variant[n] = i;
			op_visited[i]++;
			f(n+1, len);
			op_visited[i]--;

		}



	}

	return;

}

/*
int main() {

	//int b = 0;
	//auto product = [&](int a){return a * b;};

	int len = 0;
	std::cin >> len;
	for(int i = 0; i < len; i++)
		std::cin >> nums[i];

	f(0, len-1);
	std::cout << "total_perms: " << total_permutations << "\n";

	return 0;
}

*/
