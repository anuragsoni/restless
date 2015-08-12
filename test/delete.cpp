#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST(DeleteRequestTest, simpleDelete) {
        auto result = asoni::Handle().del("https://httpbin.org/delete").exec();
        EXPECT_EQ(result.code, 200);
}

TEST(DeleteRequestTest, simpleDeleteBasicAuth) {
        auto result = asoni::Handle()
                          .del("https://httpbin.org/delete", "password")
                          .exec();
        EXPECT_EQ(result.code, 200);
}
int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
