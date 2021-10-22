#include "vector_test.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void time(int start, int end) {
    std::cout << "[" << GREEN << end - start << RESET << "] ticks && "
              << "[" << GREEN << ((float)end - start) / CLOCKS_PER_SEC
              << RESET << "]"
              << " sec.\n";
}

void percentage_compare(int std_ticks, int ft_ticks) {
    double per;
    if (ft_ticks > std_ticks) {
        std::cout << "FT SLOWER BY ";
        per = ((float)std_ticks / ft_ticks) * 100;
        std::cout << YELLOW "[" << 100 - per  << "%]\n" << RESET;
    } else {
        std::cout << "FT FASTER BY ";
        per = ((float)ft_ticks / std_ticks) * 100;
        std::cout << BOLDCYAN << "[" <<  100 - per  << "%]\n" << RESET;
    }
}

void checker(bool equal) {
    if (equal)
        std::cout << GREEN << "[OK]" << RESET << " ";
    else
        std::cout << BOLDRED << "[ERROR]" << RESET << " ";
    std::cout << "\n";
}

void test_title(std::string str) {
    std::cout << YELLOW << str << RESET << ":\n";
}

Test::Test() {
    srand(time(0));

    bool r = rand() % 2;
    storage = new int(10);
    size = 10;
    if (r)
        throw 1;
}
Test::Test(const Test &other) {
    storage = new int(10);
    size = other.size;
}
Test::~Test() {
    delete storage;
}

Test&	Test::operator=(const Test &other) {
    if (this == &other)
        return *this;
    if (storage != NULL) {

    }
    return *this;
}

