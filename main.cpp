#include <string>
#include <iostream>
#include <restless.hpp>
int main(void)
{
    auto result = asoni::Handle()
        .get("http://httpbin.org/get")
        .exec();

    std::cout << result.body << "\n";

}