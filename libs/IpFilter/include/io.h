#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <optional>
#include <filesystem>
#include <fstream>
#include <set>
#include <map>

#include "ipv4.h"

namespace filter {
    enum class inputType : int {
        invalid,
        standard,
        file
    };

    class IO {
    public:
        using bytePosition = int;
        using byteValue = int;

        IO() = delete;
        explicit IO(inputType type, const std::optional<std::filesystem::path>& filePath = {});

        IO(const IO& other) = delete;
        IO(IO&& other) = delete;
        
        ~IO() = default;

    public:
        template <class Compare = std::less<IPv4>>
        void in(std::multiset<IPv4, Compare>& addresses) {
            switch (_type) {
            case inputType::invalid:
                return;
            case inputType::standard:
                return;
            case inputType::file:
                std::ifstream istream;
                std::string line;

                istream.open(*_filePath);
                if (!istream.is_open()) return;

                while (!istream.eof()) {
                    std::getline(istream, line);
                    std::size_t tabPos = line.find('\t');

                    if (tabPos == std::string::npos)
                        continue;

                    auto ipv4 = IPv4::toIPv4(line.substr(0, tabPos));
                    if (ipv4) addresses.insert(*ipv4);
                }

                return;
            }
        }

        template <class Compare = std::less<IPv4>>
        void out(const std::multiset<IPv4, Compare>& addresses) const {
            for (const auto& address : addresses) {
                auto addr = address.getAddress();
                outAddress(addr);
            }
        }

        template <class Compare = std::less<IPv4>>
        void out(const std::multiset<IPv4, Compare>& addresses, byteValue value) const {
            for (const auto& address : addresses) {
                auto addr = address.getAddress();
                
                if (!bytePositionIsValid(value)) 
                    return;

                if (addr[0] == value 
                    || addr[1] == value
                    || addr[2] == value
                    || addr[3] == value)
                    outAddress(addr);
            }
        }

        template <class Compare = std::less<IPv4>>
        void out(const std::multiset<IPv4, Compare>& addresses, 
                const std::map<bytePosition, byteValue>& searchBytes) const {
            const std::size_t searchBytesSize = searchBytes.size();
            
            if (searchBytesSize < 1 || searchBytesSize > 4) 
                return;

            for (const auto& address : addresses) {
                auto addr = address.getAddress();

                std::size_t needToOut = 0;
                for (const auto& searchByte : searchBytes) {
                    if (!bytePositionIsValid(searchByte.first)) 
                        return;
                    if (addr[searchByte.first - 1] == searchByte.second)
                        needToOut += 1;
                }

                if (searchBytesSize == needToOut) 
                    outAddress(addr);
            }
        }

        std::optional<std::filesystem::path> getFilePath() const;

        friend std::ostream& operator<<(std::ostream& stream, const IO& io);

    private:
        bool bytePositionIsValid(bytePosition pos) const;
        void outAddress(const std::vector<int>& addr) const;

    private:
        const inputType _type;
        std::optional<std::filesystem::path> _filePath;
    };
}

#endif // IO_H