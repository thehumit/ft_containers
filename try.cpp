#include <iostream>
#include <cmath>
#include <vector>

template <class T>

std::ostream& operator<< (std::ostream &out, const std::vector<T> &vec)
{
    int size = vec.size();

    for (int i = 0; i < size; i++)
        out << "++" << vec[i] << std::endl;
    return out;
}


int main(void)
{
	std::vector<int> v  (3, 100);
	std::vector<int>::iterator it = v.begin();
	v.insert(it, 200);
	std::cout << v << std::endl;

}

// template <class T>
