#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <restless.hpp>

TEST_CASE( "Simple Get Request", "[get]" ) {
    auto result = asoni::Handle()
        .get("http://httpbin.org/robots.txt")
        .exec();
    std::string actual = "User-agent: *\nDisallow: /deny\n";
    REQUIRE(result.code == 200);
    REQUIRE(result.body == actual);
}
