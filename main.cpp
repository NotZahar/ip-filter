#include <iostream>
#include <some.h>

int main(int, char**) {
    std::cout << "base application message" << std::endl;
    sm::printSomething();
}