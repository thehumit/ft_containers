#include <iostream>
#include <vector>

#include "vector_test.hpp"

#include <iterator>
#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <time.h>
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"
#include "rbtree.hpp"
#include "vector.hpp"
// #include "hdrs/rbiter.hpp"

using namespace std;


bool	equal(std::map<int, const int> m1, ft::map<int, const int> m2)
{
	auto i = m1.begin();
	auto j = m2.begin();

	while (i != m1.end() && j != m2.end())
	{
		if (i->first != j->first || i->second != j->second)
			return false;
		i++;
		j++;
	}
	if (i != m1.end() || j != m2.end())
		return false;
	return true;
}


void	set_test()
{
	ft::set<int>	x;
	for (int i = 0; i < 100; i++)
		x.insert(rand() % 10);

	x.erase(x.find(5), x.find(8));

	auto i = x.begin();
	int d = 0;
    

}

void	map_test()
{
	std::map<int, const int>	m1;
	ft::map<int, const int>		m2;
	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 7;
		m1.insert(std::make_pair(x, i));
		m2.insert(ft::make_pair(x, i));

		if (!equal(m1, m2))
		{
			std::cout << "ERROR" << std::endl;
			return ;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		int x = rand() % 7 + (i + 1) * 7;
		m1.insert(std::make_pair(x, i));

		if (equal(m1, m2))
		{
			std::cout << "map - error" << std::endl;
			return ;
		}
		m2.insert(ft::make_pair(x, i));
	}

	ft::map<int, int>	numbers_to_delete;
	for (int i = 0; i < m1.size(); i++)
	{
		if (rand() % 25 > 12)
			numbers_to_delete[i] = 1;
	}
	auto i = m1.begin();
	auto j = m2.begin();
	for (int n = 0; n < m1.size(); n++)
	{
		if (numbers_to_delete[n] == 1 && m1.end() != i && m2.end() != j)
		{
			m1.erase(i++);
			m2.erase(j++);
		}
		if (m1.end() != i)
			i++;
		if (m2.end() != j)
			j++;
	}
	if (j != m2.end() || i != m1.end())
	{
		std::cout << "map - error" << std::endl;
		return ;
	}
	if (!equal(m1, m2))
	{
		std::cout << "map - error" << std::endl;
		return ;
	}
	std::cout << "map - good" << std::endl;
}


void	stack_test()
{
	ft::stack<int>	x;
	std::stack<int>	y;

	for (int i = 0; i < 15; i++)
	{
		int z = rand() % 15;
		x.push(z);
		if (x.top() != z)
		{
			std::cout << "stack - error" << std::endl;
			return;
		}
	}
	if (x.size() != 15)
	{
		std::cout << "stack - error" << std::endl;
		return;
	}
	while (x.size() != 0)
	{
		x.pop();
	}
	if (x.empty())
		std::cout << "stack - good\n";
	else
		std::cout << "stack - error\n";
}

void	vector_test()
{
	ft::vector<int>	a;
	std::vector<int>	b;

	for (int i = 0; i < 50; i++)
	{
		int x = rand() % 50;
		a.push_back(x);
		b.push_back(x);
	}
	auto i1 = a.begin();
	auto i2 = b.begin();
	for (int i = 0; i < a.size(); i++, i1++, i2++)
	{
		if (rand() % 50 > 35)
		{
			a.erase(i1);
			b.erase(i2);
		}
	}
	if (a.size() != b.size())
	{
		std::cout << "VECTOR ERROR\n";
		return ;
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
		{
			std::cout << "VECTOR ERROR\n";
			return ;
		}
	}
	std::cout << "vector - good\n";
}

int		main()
{
	srand(1642617733);
	set_test();
	map_test();
	stack_test();
	vector_test();
}