#include <iostream>
#include <restless.hpp>
using Http = asoni::Handle;
int main()
{

    /*
     * A simple get request
     **/

    auto res1 = Http()
                .get("http://httpbin.org/get")
                .exec();

    std::cout << res1.body << "\n";

    /*
     * A get request with basic auth and a custom header
     **/

    std::map<std::string, std::string> custom_headers;
    custom_headers["Hello"] = "This is a header";
    auto res2 = Http()
                .get("http://httpbin.org/get", "password-for-basic-auth")
                .header(custom_headers)
                .exec();

    std::cout << res2.body << '\n';
}