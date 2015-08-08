#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;

TEST(GetRequestTest, simpleGetRequest) {
  auto result = asoni::Handle().get("http://httpbin.org/robots.txt").exec();
  EXPECT_EQ(result.code, 200);
  std::string actual = "User-agent: *\nDisallow: /deny\n";
  EXPECT_EQ(result.body, actual);
}

TEST(GetRequestTest, GetRequestHTTPS) {
  auto result = asoni::Handle().get("https://httpbin.org/robots.txt").exec();
  EXPECT_EQ(result.code, 200);
  std::string actual = "User-agent: *\nDisallow: /deny\n";
  EXPECT_EQ(result.body, actual);
}

TEST(GetRequestTest, GetRequestBasicAuth) {
  auto result =
      asoni::Handle()
          .get("http://httpbin.org/get", "password")
          .header({{"Hello", "This is a header"}, {"Second", "Another header"}})
          .exec();
  EXPECT_EQ(result.code, 200);
  auto response = json::parse(result.body);
  std::string header_hello = response["headers"]["Hello"];
  std::string header_second = response["headers"]["Second"];
  EXPECT_EQ(header_hello, "This is a header");
  EXPECT_EQ(header_second, "Another header");
}

TEST(GetRequestTest, GetRequestInvalid) {
  auto result = asoni::Handle().get("http://xyz").exec();
  EXPECT_EQ(result.code, -1);
  EXPECT_EQ(result.body, "Failed to fetch response.");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
