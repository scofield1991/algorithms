/*
 * 346.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: alex
 */
// Example program

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

constexpr auto N = 100;

int a_variants[N] = {0};
int b_variants[N] = {0};
bool a_visited[N] = {0};
bool b_visited[N] = {0};
char a[N] = {'\0'};
char b[N] = {'\0'};
int c = 0;
bool answer = false;
int answer_a = 0;
int answer_b = 0;

void f_new(int n_1, int n_2, int len)
{

	if(n_1 == len && n_2 == len)
	{
		char a_variant[N];
		char b_variant[N];
		int a_variant_int;
		int b_variant_int;
		for(int i = 0; i < len; i++)
		{
			a_variant[i] =  a[a_variants[i]];
			a_variant_int = atoi(a_variant);
		}
		//std::cout << "\n";

		for(int i = 0; i < len; i++)
		{
			b_variant[i] =  b[b_variants[i]];
			b_variant_int = atoi(b_variant);
			//std::cout << b_variants[i];
		}
		if(a_variant_int + b_variant_int == c)
		{
			answer = true;
			answer_a = a_variant_int;
			answer_b = b_variant_int;
		}
		//std::cout << "\n";
		return;
	}

	for(int i = 0; i < len; i++)
	{
		if(!a_visited[i])
		{
			a_visited[i] = true;
			a_variants[i] = n_1;
			f_new(n_1+1, n_2, len);
			a_visited[i] = false;

		}

		if(!b_visited[i])
		{
			b_visited[i] = true;
			b_variants[i] = n_2;
			f_new(n_1, n_2+1, len);
			b_visited[i] = false;

		}



	}
}

int main()
{
    std::cin >> a >> b >> c;
    int len = strlen(a);

    //std::cout << a << " " << b << " " << c << " " << len << "\n";

    f_new(0, 0, len);

    if(answer)
    {
    	std::cout << "YES\n";
    	std::cout << answer_a << " " << answer_b;
    }
    else
    	std::cout << "NO";

}





