/*
 * @Filename: restless.hpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: A small wrapper around libcurl to make HTTP requests
 */
#pragma once
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <map>
namespace asoni
{
class Handle
{
    // Request URI
    std::string URI;
    struct response
    {
        int code;
        std::string body;
        std::map<std::string, std::string> headers;
    };
public:
    Handle() {}
    Handle &get(const std::string iUri = "")
    {
        if(iUri.empty())
        {
            std::cout << "No request URI provided\n";
        }
        this->URI = iUri;
        std::cout << URI << "\n";
        return *this;
    }
    auto exec()
    {
        response res;
        res.code = 200;
        res.body = "Hello world";
        res.headers = {{"1","one"}};
        return res;
    };

};
} // Namespace asoni ends