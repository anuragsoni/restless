[![Build Status](https://travis-ci.org/anuragsoni/restless.svg?branch=master)] (https://travis-ci.org/anuragsoni/restless)

# Restless
**[STILL IN PROGRESS]**

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

```


## Prerequisites
* libcurl
* A compiler with C++11 support
* cmake (At least version 2.8.11)

**Note:**A vagrant file has been provided that will provision a Ubuntu14.04
box with all the pre-requisites. Just ```vagrant up``` then ```vagrant ssh```.
You will find the code in /vagrant directory inside the vagrant box.

## External libraries
* [philsquared's catch unit testing](https://github.com/philsquared/Catch)

## Steps to build
* cd build
* cmake ..
* make
* make test (optional)
