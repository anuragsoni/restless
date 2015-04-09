# Restless

Restless is a simple wrapper around libcurl.
This will help to make simple HTTP calls in your C++
code.


## Integration

You can use your project's existing build system to compile
all the files in `src` directory and link to your project.

To use this all you need to do is add

```cpp
#include <restless.hpp>

// for a more readable name
using Http = asoni::Handle;
```

## Examples

```cpp

/*
 * A simple get request
 **/

auto res1 = Http::Handle()
            .get("http://httpbin.org/get")
            .exec();

std::cout << res1.body << "\n";

/*
 * A get request with basic auth and a custom header
 **/

std::map<std::string, std::string> custom_headers;
custom_headers["Hello"] = "This is a header";
auto res2 = Http::Handle()
            .get("http://httpbin.org/get", "password-for-basic-auth")
            .header(custom_headers)
            .exec();

std::cout << res2.body << '\n';

```


## Prerequisites
* libcurl
* A C++ compiler
* cmake

### External libraries
* [nlohmann's json library](https://github.com/nlohmann/json)
* [philsquared's catch unit testing](https://github.com/philsquared/Catch)

### Steps to build
* cd build
* cmake ..
* make
* make test (optional)
