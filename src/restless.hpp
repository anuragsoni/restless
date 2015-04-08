/*
 * @Filename: restless.hpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: A small wrapper around libcurl to make HTTP requests
 */
#pragma once
#include <curl/curl.h>
#include <string>
#include <iostream>
#include "json.hpp"
#include <map>
#include "helpers.hpp"
#define AGENT_NAME "restless/0.1"

using json = nlohmann::json;

namespace asoni
{
class Handle
{
    // Request Types
    enum Request_Type {GET, PUT, POST, DELETE};

    Request_Type method;

    // Request URI
    std::string URI;

    // Http response
    struct response
    {
        int code;
        std::string body;
        std::map<std::string, std::string> headers;
    };

    response execGet(const std::string &iUri);

    /*
     * HTTP user-agent header
     */
    const static std::string user_agent;

    /*
    * Callback for writing received data. [CURLOPT_WRITEFUNCTION]
    * This function will be called by libcurl as soon as there is
    * data received that needs to be saved. ptr points to the
    * delivered data, and the size of that data is size multiplied
    * with nmemb.
    */
    static size_t write_callback(void *ptr, size_t size, size_t nmemb, Handle::response *res);

    /*
     * Callback that receives the header data. [CURLOPT_HEADERFUNCTION]
     * This function gets called by libcurl as soon as it has received
     * header data. The header callback will be called once for each
     * header
     */
    static size_t header_callback(void *ptr, size_t size, size_t nmemb, Handle::response *res);

public:
    Handle() {}
    Handle &get(const std::string iUri);

    response exec();

};
} // Namespace asoni ends