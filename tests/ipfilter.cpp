#include <gtest/gtest.h>

#include <cstdlib>
#include <io.h>

TEST(IpFilter, md5sum_check_linux) {
    [[nodiscard]] std::system("cat ip_filter.tsv | ./ip_filter | md5sum > ip_filter_md5sum_check_l.txt");
    std::ifstream istream;
    std::string checkLine;

    istream.open("ip_filter_md5sum_check_l.txt");
    if (!istream.is_open()) 
        FAIL();

    std::getline(istream, checkLine);

    EXPECT_EQ(checkLine, "24e7a7b2270daee89c64d3ca5fb3da1a  -");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
