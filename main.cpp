#include "vector.hpp"

int main()
{
	ft::vector<int> vec;
	vec.push_pack(10);
	// vec.begin();
	vec.insert(vec.begin(), 100);
	std::cout << vec[0] << std::endl;
}