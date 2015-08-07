#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include <catch.hpp>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST_CASE("Simple Put Request : HTTPS", "[put]") {
        std::string put_content = "Hello world";
        auto result = asoni::Handle()
                          .put("https://httpbin.org/put")
                          .content("text/plain", put_content)
                          .exec();
        auto response = json::parse(result.body);
        REQUIRE(result.code == 200);
        REQUIRE(response["data"] == put_content);
}
