/*
 * @Filename: restless.cpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: A small wrapper around libcurl to make HTTP requests
 */

#include "restless.hpp"

namespace asoni
{
// set the user agent
const std::string Handle::user_agent
{
    AGENT_NAME
};

// Set custom headers
Handle &Handle::header(std::map<std::string, std::string> iHeaders)
{
    if(!iHeaders.empty())
    {
        this->custom_headers = iHeaders;
    }
    return *this;
}

Handle &Handle::get(const std::string iUri, const std::string password)
{
    this->URI = iUri;
    this->method = Request_Type::GET;
    if(!password.empty())
    {
        this->basic_auth_pass = password;
    }
    return *this;
}

Handle::response Handle::exec()
{
    response result;

    switch (method)
    {
    case Request_Type::GET:
        result = execGet(URI);
        break;
    default:
        result.code = -1;
        result.body = "Invalid HTTP Method called";
    }
    return result;
}

Handle::response Handle::execGet(const std::string &iUrl)
{
    CURL *curl{nullptr};
    CURLcode req = CURLE_OK;
    response res;
    curl = curl_easy_init();
    if (curl)
    {
        // Check if basic auth password provided
        if(!basic_auth_pass.empty())
        {
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERPWD, basic_auth_pass.c_str());
        }

        // User agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, Handle::user_agent.c_str());
        // Requested URL
        curl_easy_setopt(curl, CURLOPT_URL, iUrl.c_str());
        // Write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        if(!custom_headers.empty())
        {
            struct curl_slist *chunk = nullptr;
            for(auto x:custom_headers)
            {
                std::string temp_header = x.first + ": " + x.second;
                chunk = curl_slist_append(chunk, temp_header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
        // Header callback function
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &res);
        // Perform curl request
        req = curl_easy_perform(curl);
        if (req != CURLE_OK)
        {
            res.body = "Failed to fetch response.";
            res.code = -1;
            return res;
        }
        long http_code {0};
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        res.code = static_cast<int>(http_code);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    return res;
}

/*
 * Function - write callback for libcurl
 * @param data
 * @param size
 * @param nmemb
 * @param userdata
 * @return size * nmemb
 */
size_t Handle::write_callback(void *data, size_t size, size_t nmemb, Handle::response *res)
{
    res->body.append(reinterpret_cast<char *>(data), size * nmemb);
    return (size * nmemb);
}

/*
 * Function - header callback for libcurl
 * @param data
 * @param size
 * @param nmemb
 * @param userdata
 * @return size * nmemb
 */
size_t Handle::header_callback(void *data, size_t size, size_t nmemb, Handle::response *res)
{
    std::string header(reinterpret_cast<char *>(data), size * nmemb);
    size_t break_point = header.find_first_of(":");
    if (break_point == std::string::npos)
    {
        trim(header);
        if (0 == header.length())
        {
            return (size * nmemb);
        }
        res->headers[header] = "true";
    }
    else
    {
        std::string header_key = header.substr(0, break_point);
        trim(header_key);
        std::string header_value = header.substr(break_point + 1);
        trim(header_value);
        res->headers[header_key] = header_value;
    }
    return (size * nmemb);
}

} // namespace asoni ends here