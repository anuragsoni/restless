TEST_CASE( "Get Request Response Code", "[get]" ) {
    auto result = asoni::Handle()
        .get("http://httpbin.org/robots.txt")
        .exec();
    REQUIRE(result.code == 200);
}

TEST_CASE( "Simple Get Request", "[get]" ) {
    auto result = asoni::Handle()
        .get("http://httpbin.org/robots.txt")
        .exec();
    std::string actual = "User-agent: *\nDisallow: /deny\n";
    REQUIRE(result.body == actual);
}
