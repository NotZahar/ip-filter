#include <iostream>
#include "some.h"
#include "things.h"

namespace sm
{
    C::C(/* args */)
    {
    }
    
    C::~C()
    {
    }

    void printSomething()
    {
        std::cout << "ololo, " << someString << std::endl;
    }
}