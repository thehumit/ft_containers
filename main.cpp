#include "vector.hpp"
#include <unistd.h>

int main()
{
	ft::vector<int> vec;
	for (int i = 0; i < 5; i++)
	{
		vec.push_pack(10);
		std::cout << *(vec.begin() + i) << " capacity:" << vec.capacity() << std::endl;
	}
	// vec.begin();
	vec.insert(vec.begin(), 20,  100);
	for (int i = 5; i < 10; i++)
		std::cout << *(vec.begin() + i) << " capacity:" << vec.capacity() << std::endl;
	pause();
}