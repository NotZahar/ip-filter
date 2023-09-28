#ifndef IPV4_H
#define IPV4_H

#include <vector>
#include <string>
#include <optional>

namespace filter {
    class IPv4 {
    public:
        IPv4() = delete;
        explicit IPv4(int p1, int p2, int p3, int p4);

        IPv4(const IPv4& other) = default;
        IPv4(IPv4&& other) = default;
        
        ~IPv4() = default;

    public:
        static std::optional<IPv4> toIPv4(const std::string& str);
        const std::vector<int>& getAddress() const;

        bool operator<(const IPv4& other) const;
        bool operator>(const IPv4& other) const;

    private:
        std::vector<int> _address;
    };
}

#endif // IPV4_H