#include <iostream>
#include <restless.hpp>
using Http = asoni::Handle;
int main()
{

    /*
     * A simple get request
     **/

    auto res1 = Http().get("http://httpbin.org/get")
                .exec();

    std::cout << res1.body << "\n";

    /*
     * A get request with basic auth and a custom header
     **/

    auto res2 = Http().get("http://httpbin.org/get", "password-for-basic-auth")
                .header({{"Hello", "This is a header"}, {"Second","Another header"}})
                .exec();

    std::cout << res2.body << '\n';

    auto post1 = Http().post("http://httpbin.org/post", "super-secret-password")
                    .content("text/plain", "Hello world")
                    .exec();
    std::cout << post1.body << '\n';
}