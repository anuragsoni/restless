
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include <catch.hpp>
#include <json.hpp>
#include <restless.hpp>
using json = nlohmann::json;
TEST_CASE("Simple Delete Request : HTTPS", "[delete]") {
        auto result = asoni::Handle().del("https://httpbin.org/delete").exec();
        REQUIRE(result.code == 200);
}
