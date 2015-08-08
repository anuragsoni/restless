#include <gtest/gtest.h>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST(PutRequestTEst, PutRequestHttps) {
  std::string put_content = "Hello world";
  auto result = asoni::Handle()
                    .put("https://httpbin.org/put")
                    .content("text/plain", put_content)
                    .exec();
  auto response = json::parse(result.body);
  EXPECT_EQ(result.code, 200);
  EXPECT_EQ(response["data"], put_content);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
