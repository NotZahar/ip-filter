#include <gtest/gtest.h>

#include <cstdlib>
#include <io.h>

TEST(IpFilter, md5sum_check_linux) {
    const char* command = "cat ip_filter.tsv | ./ip_filter | md5sum > md5sum_check_l.txt";
    int returnSystemValue = std::system(command);
    std::ifstream istream;
    std::string checkLine;

    istream.open("md5sum_check_l.txt");
    if (!istream.is_open()) 
        FAIL();

    std::getline(istream, checkLine);

    EXPECT_EQ(returnSystemValue, 0);
    EXPECT_EQ(checkLine, "24e7a7b2270daee89c64d3ca5fb3da1a  -");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
