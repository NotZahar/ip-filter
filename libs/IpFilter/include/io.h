#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <optional>
#include <filesystem>
#include <fstream>
#include <set>

#include "ipv4.h"

namespace filter {
    enum class inputType : int {
        invalid,
        standard,
        file
    };

    class IO {
    public:
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
        void out(const std::multiset<IPv4, Compare>& addresses) {
            for (const auto& address : addresses) {
                auto addr = address.getAddress();
                std::cout << addr[0] << '.' << addr[1] << '.' << addr[2] << '.' << addr[3] << '\n';
            }
        }

        // template <class Compare = std::less<IPv4>> // TODO: [here] add condition
        // void out(const std::multiset<IPv4, Compare>& addresses) {
        //     for (const auto& address : addresses) {
        //         auto addr = address.getAddress();
        //         std::cout << addr[0] << '.' << addr[1] << '.' << addr[2] << '.' << addr[3] << '\n';
        //     }
        // }

        std::optional<std::filesystem::path> getFilePath() const;

        friend std::ostream& operator<<(std::ostream& stream, const IO& io);

    private:
        const inputType _type;
        std::optional<std::filesystem::path> _filePath;
    };
}

#endif // IO_H