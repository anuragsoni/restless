#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST(Restless, invalidRequestType) {
        auto result = asoni::Handle().exec();
        EXPECT_EQ(result.code, -1);
        EXPECT_EQ(std::string("Invalid HTTP Method called"), result.body);
}

int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
