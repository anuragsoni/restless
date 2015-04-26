[![Build Status](https://drone.io/github.com/anuragsoni/restless/status.png)](https://drone.io/github.com/anuragsoni/restless/latest)
# Restless
Restless is a simple REST client for C++, powered by curl.


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

auto res1 = Http().get("http://httpbin.org/get")
            .exec();

/*
 * A get request with basic auth and a custom header
 **/

auto res2 = Http().get("http://httpbin.org/get", "password-for-basic-auth")
            .header({{"Hello", "This is a header"}, {"Second","Another header"}})
            .exec();

/*
 * A post request with basic auth
 **/
auto post1 = Http().post("http://httpbin.org/post", "super-secret-password")
                    .content("text/plain", "Hello world")
                    .exec();

/*
 * A simple put request
 **/

auto put1 = Http().put("http://httpbin.org/put")
            .content("text/plain", "Hello world")
            .exec();

/*
 * A simple delete request
 **/

auto del = Http().del("http://httpbin.org/delete")
           .exec();


```


## Dependencies
* libcurl
* A compiler with C++11 support (GCC 4.8 and higher, Clang 3.4 and higher)
* cmake (At least version 2.8.11)
* [catch unit testing](https://github.com/philsquared/Catch) - for development
* [json](https://github.com/nlohmann/json) - as a helper in testing


**Note:** A vagrant file has been provided that will provision a Ubuntu14.04
box with all the pre-requisites. Just ```vagrant up``` then ```vagrant ssh```.
You will find the code in /vagrant directory inside the vagrant box.

## Steps to build
* cd build
* cmake ..
* make
* make test (optional)

## Contribute
* Fork the project
* Make an addition or bugfix
* Add test cases
* Commit, then make a pull request (topic branches are recommended)