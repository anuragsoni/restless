#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST(PutRequestTest, PutRequestHttps) {
        std::string put_content = "Hello world";
        auto result = asoni::Handle()
                          .put("https://httpbin.org/put")
                          .content("text/plain", put_content)
                          .exec();
        auto response = json::parse(result.body);
        EXPECT_EQ(result.code, 200);
        EXPECT_EQ(response["data"], put_content);
}

TEST(PutRequestTest, PutRequestBasicAuth) {
        std::string put_content = "Hello world";
        auto result = asoni::Handle()
                          .put("https://httpbin.org/put", "password")
                          .content("text/plain", put_content)
                          .exec();
        auto response = json::parse(result.body);
        EXPECT_EQ(result.code, 200);
        EXPECT_EQ(response["data"], put_content);
}

TEST(PutRequestTest, PutRequestCustomHeaders) {
        std::string put_content = "Hello world";
        auto result = asoni::Handle()
                          .put("https://httpbin.org/put")
                          .content("text/plain", put_content)
                          .header({{"Hello", "This is a header"},
                                   {"Second", "Another header"}})
                          .exec();
        auto response = json::parse(result.body);
        std::string header_hello = response["headers"]["Hello"];
        std::string header_second = response["headers"]["Second"];
        EXPECT_EQ(result.code, 200);
        EXPECT_EQ(response["data"], put_content);
        EXPECT_EQ(header_hello, "This is a header");
        EXPECT_EQ(header_second, "Another header");
}

int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
