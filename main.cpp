#include <set>
#include <io.h>

int main(int, char**) {
    filter::IO io(filter::inputType::file); 
    std::multiset<filter::IPv4, std::greater<filter::IPv4>> addresses;
    io.in(addresses);
    io.out(addresses);
}