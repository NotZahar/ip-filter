#include "ipv4.h"

#include <algorithm>
#include <iostream>
#include <array>

namespace filter {
    IPv4::IPv4(int p1, int p2, int p3, int p4) {
        _address.reserve(4);
        _address.push_back(p1);
        _address.push_back(p2);
        _address.push_back(p3);
        _address.push_back(p4);
    }

    std::optional<IPv4> IPv4::toIPv4(const std::string& str) {
        int startIndex = 0; 
        int endIndex = 0;
        std::array<int, 4> address{-1, -1, -1, -1};
        int addressPos = 0;
        for (std::size_t i = 0; i <= str.size(); ++i) {
            if (str[i] != '.' && i != str.size())
                continue;

            std::string temp;
            endIndex = i;
            temp.append(str, startIndex, endIndex - startIndex);
            try {
                int p = std::stoi(temp);
                if (p < 0 || p > 255) return {};
                if (addressPos > 3) return {};
                address[addressPos] = p;
                ++addressPos;
            } catch(const std::exception&) {
                return {};
            }
            startIndex = endIndex + 1;
        }
        
        return IPv4(address[0], address[1], address[2], address[3]);
    }

    const std::vector<int>& IPv4::getAddress() const {
        return _address;
    }

    bool IPv4::operator<(const IPv4& other) const {
        return std::lexicographical_compare(
            _address.begin(), _address.end(), 
            other._address.begin(), other._address.end()
        );
    }

    bool IPv4::operator>(const IPv4& other) const {
        return other < *this;
    }
}