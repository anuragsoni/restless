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
#include <vector>
#include <memory>
#include "helpers.hpp"

namespace asoni
{
class Handle
{
private:

    std::unique_ptr<CURL,  void(*)(CURL*)> curl;

    // Request Types
    enum class Request_Type {GET, PUT, POST, DEL};

    Request_Type method;

    // Request URI
    std::string URI;

    // Maximum time the request is allowed to take
    long timeout_value = 0L;

    // Password for Basic Auth
    std::string basic_auth_pass;

    // Post content type
    std::string post_content_type;

    // Post content
    std::vector<uint8_t > post_content;

    // Custom headers
    std::map<std::string, std::string> custom_headers;

    // Http response
    struct response
    {
        int code;
        std::string body;
        std::map<std::string, std::string> headers;
        ~response() { }
        std::vector<uint8_t > bodyRaw() {
            return std::vector<uint8_t> (body.begin(), body.end());
        }
    };

    // struct for uploading data
    struct upload_object
    {
        const char* data;
        size_t length;
    };

    response execGet();

    response execPost();

    response execPut();

    response execDel();

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
    static size_t write_callback(void *data, size_t size, size_t nmemb, Handle::response *res);

    /*
     * Callback that receives the header data. [CURLOPT_HEADERFUNCTION]
     * This function gets called by libcurl as soon as it has received
     * header data. The header callback will be called once for each
     * header
     */
    static size_t header_callback(void *data, size_t size, size_t nmemb, Handle::response *res);

    /*
    * This function will be called by libcurl as soon as it needs
    * to read data in order to send it to the peer.
    */
    static size_t read_callback(void *data, size_t size, size_t nmemb, Handle::upload_object *up_obj);

public:

    Handle() : curl(curl_easy_init(), curl_easy_cleanup) { curl_global_init( CURL_GLOBAL_ALL ); }

    ~Handle()
    {
        curl_global_cleanup();
    }

    Handle &get(const std::string iUri, const std::string password = "");

    Handle &post(const std::string iUri, const std::string password = "");

    Handle &put(const std::string iUrl, const std::string password = "");

    Handle &del(const std::string iUrl, const std::string password = "");

    Handle &header(std::map<std::string, std::string> iHeaders);

    Handle &content(const std::string content_type, const std::string content_data);

    Handle &content(const std::string content_type, const std::vector<uint8_t > content_data);

    Handle &timeout(long timeout);

    response exec();
};
} // Namespace asoni ends
