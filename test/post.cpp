#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;

TEST(PostRequestTest, PostWithoutContent) {
  auto result = asoni::Handle().post("http://httpbin.org/post").exec();
  EXPECT_EQ(result.code, -1);
  EXPECT_EQ(result.body,
            "Empty post content not allowed. Did you meant to use GET?");
}

TEST(PostRequestTest, SimplePostRequest) {
  std::string post_content = "Hello world";
  auto result = asoni::Handle()
                    .post("http://httpbin.org/post")
                    .content("text/plain", post_content)
                    .exec();
  auto response = json::parse(result.body);
  EXPECT_EQ(result.code, 200);
  EXPECT_EQ(response["data"], post_content);
}

TEST(PostRequestTest, PostRequestHTTPS) {
  std::string post_content = "Hello world";
  auto result = asoni::Handle()
                    .post("https://httpbin.org/post")
                    .content("text/plain", post_content)
                    .exec();
  auto response = json::parse(result.body);
  EXPECT_EQ(result.code, 200);
  EXPECT_EQ(response["data"], post_content);
}

TEST(PostRequestTest, PostRequestCustomHeader) {
  std::string post_content = "Hello world";
  auto result =
      asoni::Handle()
          .post("http://httpbin.org/post")
          .content("text/plain", post_content)
          .header({{"Hello", "This is a header"}, {"Second", "Another header"}})
          .exec();
  auto response = json::parse(result.body);
  std::string header_hello = response["headers"]["Hello"];
  std::string header_second = response["headers"]["Second"];
  EXPECT_EQ(result.code, 200);
  EXPECT_EQ(header_hello, "This is a header");
  EXPECT_EQ(header_second, "Another header");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
