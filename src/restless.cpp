/*
 * @Filename: restless.cpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: A small wrapper around libcurl to make HTTP requests
 */

#include "restless.hpp"
#include <cstring>
namespace asoni {
// set the user agent
const std::string Handle::user_agent{AGENT_NAME};

// Set custom headers
Handle &Handle::header(std::map<std::string, std::string> iHeaders) {
        if (!iHeaders.empty()) {
                this->custom_headers = iHeaders;
        }
        return *this;
}

Handle &Handle::get(const std::string iUri, const std::string password) {
        this->URI = iUri;
        this->method = Request_Type::GET;
        if (!password.empty()) {
                this->basic_auth_pass = password;
        }
        return *this;
}

Handle &Handle::post(const std::string iUri, const std::string password) {
        this->URI = iUri;
        this->method = Request_Type::POST;
        if (!password.empty()) {
                this->basic_auth_pass = password;
        }
        return *this;
}

Handle &Handle::put(const std::string iUri, const std::string password) {
        this->URI = iUri;
        this->method = Request_Type::PUT;
        if (!password.empty()) {
                this->basic_auth_pass = password;
        }
        return *this;
}

Handle &Handle::del(const std::string iUri, const std::string password) {
        this->URI = iUri;
        this->method = Request_Type::DEL;
        if (!password.empty()) {
                this->basic_auth_pass = password;
        }
        return *this;
}

Handle &Handle::content(const std::string content_type,
                        const std::string content_data) {
        this->post_content = content_data;
        this->post_content_type = content_type;
        return *this;
}

Handle::response Handle::exec() {
        response result;

        if (curl) {
                // Check if basic auth password provided
                if (!basic_auth_pass.empty()) {
                        curl_easy_setopt(curl.get(), CURLOPT_HTTPAUTH,
                                         CURLAUTH_BASIC);
                        curl_easy_setopt(curl.get(), CURLOPT_USERPWD,
                                         basic_auth_pass.c_str());
                }

                // User agent
                curl_easy_setopt(curl.get(), CURLOPT_USERAGENT,
                                 Handle::user_agent.c_str());
                // Requested URL
                curl_easy_setopt(curl.get(), CURLOPT_URL, URI.c_str());
                switch (method) {
                        case Request_Type::GET:
                                result = execGet();
                                break;
                        case Request_Type::POST:
                                result = execPost();
                                break;
                        case Request_Type::PUT:
                                result = execPut();
                                break;
                        case Request_Type::DEL:
                                result = execDel();
                                break;
                        default:
                                result.code = -1;
                                result.body = "Invalid HTTP Method called";
                }
        } else {
                result.body = "Failed to initialize curl";
                result.code = -1;
        }

        return result;
}

Handle::response Handle::execGet() {
        response res;
        // Write callback function
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &res);
        struct curl_slist *chunk = nullptr;
        if (!custom_headers.empty()) {
                for (auto x : custom_headers) {
                        std::string temp_header = x.first + ": " + x.second;
                        chunk = curl_slist_append(chunk, temp_header.c_str());
                }
                curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, chunk);
        }

        // Header callback function
        curl_easy_setopt(curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl.get(), CURLOPT_HEADERDATA, &res);
        // Perform curl request
        const auto req = curl_easy_perform(curl.get());
        if (req != CURLE_OK) {
                res.body = "Failed to fetch response.";
                res.code = -1;
                curl_slist_free_all(chunk);
                return res;
        }
        long http_code{0};
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);
        res.code = static_cast<int>(http_code);
        /* free the custom headers */
        curl_slist_free_all(chunk);
        return res;
}

Handle::response Handle::execPost() {
        response res;

        // 1L tells libcurl to do a regular HTTP post.
        // This will also make the library use a
        // "Content-Type: application/x-www-form-urlencoded" header.
        curl_easy_setopt(curl.get(), CURLOPT_POST, 1L);
        // Set post fields and post field size
        if (!post_content.empty()) {
                curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS,
                                 post_content.c_str());
                curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDSIZE,
                                 post_content.size());
        } else {
                res.body =
                    "Empty post content not allowed. Did you mean to use GET?";
                res.code = -1;
                return res;
        }
        // Write callback function
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &res);

        // Header callback function
        curl_easy_setopt(curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl.get(), CURLOPT_HEADERDATA, &res);

        struct curl_slist *chunk = nullptr;
        if (!post_content_type.empty()) {
                std::string content_type = "Content-Type: " + post_content_type;
                chunk = curl_slist_append(chunk, content_type.c_str());
        } else {
                res.body = "Content-type needs to be provided.";
                res.code = -1;
                return res;
        }
        if (!custom_headers.empty()) {
                for (auto x : custom_headers) {
                        std::string temp_header = x.first + ": " + x.second;
                        chunk = curl_slist_append(chunk, temp_header.c_str());
                }
        }
        curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, chunk);

        // Perform curl request
        const auto req = curl_easy_perform(curl.get());
        if (req != CURLE_OK) {
                res.body = "Failed to post content.";
                res.code = -1;
                curl_slist_free_all(chunk);
                return res;
        }
        long http_code{0};
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);
        res.code = static_cast<int>(http_code);
        /* free the custom headers */
        curl_slist_free_all(chunk);
        return res;
}

Handle::response Handle::execPut() {
        response res;
        upload_object up_obj;
        if (!post_content.empty()) {
                up_obj.data = post_content.c_str();
                up_obj.length = post_content.size();
        } else {
                res.code = -1;
                res.body =
                    "Empty put content not allowed. Did you mean to use GET?";
                return res;
        }

        curl_easy_setopt(curl.get(), CURLOPT_PUT, 1L);
        curl_easy_setopt(curl.get(), CURLOPT_UPLOAD, 1L);

        // set read callback function
        curl_easy_setopt(curl.get(), CURLOPT_READFUNCTION, read_callback);
        // set data object to pass to callback function
        curl_easy_setopt(curl.get(), CURLOPT_READDATA, &up_obj);
        // Write callback function
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &res);

        // Header callback function
        curl_easy_setopt(curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl.get(), CURLOPT_HEADERDATA, &res);
        // set data size
        curl_easy_setopt(curl.get(), CURLOPT_INFILESIZE,
                         static_cast<long>(up_obj.length));
        struct curl_slist *chunk = nullptr;
        if (!post_content_type.empty()) {
                std::string content_type = "Content-Type: " + post_content_type;
                chunk = curl_slist_append(chunk, content_type.c_str());
        } else {
                res.body = "Content-type needs to be provided.";
                res.code = -1;
                return res;
        }
        if (!custom_headers.empty()) {
                for (auto x : custom_headers) {
                        std::string temp_header = x.first + ": " + x.second;
                        chunk = curl_slist_append(chunk, temp_header.c_str());
                }
        }
        curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, chunk);

        // Perform curl request
        const auto req = curl_easy_perform(curl.get());
        if (req != CURLE_OK) {
                res.body = "Put request failed.";
                res.code = -1;
                curl_slist_free_all(chunk);
                return res;
        }
        long http_code{0};
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);
        res.code = static_cast<int>(http_code);
        /* free the custom headers */
        curl_slist_free_all(chunk);
        return res;
}

Handle::response Handle::execDel() {
        response res;
        // We want the DELETE method
        curl_easy_setopt(curl.get(), CURLOPT_CUSTOMREQUEST, "DELETE");
        // Write callback function
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &res);
        struct curl_slist *chunk = nullptr;
        if (!custom_headers.empty()) {
                for (auto x : custom_headers) {
                        std::string temp_header = x.first + ": " + x.second;
                        chunk = curl_slist_append(chunk, temp_header.c_str());
                }
                curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, chunk);
        }

        // Header callback function
        curl_easy_setopt(curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl.get(), CURLOPT_HEADERDATA, &res);
        // Perform curl request
        const auto req = curl_easy_perform(curl.get());
        if (req != CURLE_OK) {
                res.body = "Delete request failed.";
                res.code = -1;
                curl_slist_free_all(chunk);
                return res;
        }
        long http_code{0};
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);
        res.code = static_cast<int>(http_code);
        /* free the custom headers */
        curl_slist_free_all(chunk);

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
size_t Handle::write_callback(void *data, size_t size, size_t nmemb,
                              Handle::response *res) {
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
size_t Handle::header_callback(void *data, size_t size, size_t nmemb,
                               Handle::response *res) {
        std::string header(reinterpret_cast<char *>(data), size * nmemb);
        size_t break_point = header.find_first_of(":");
        if (break_point == std::string::npos) {
                trim(header);
                if (0 == header.length()) {
                        return (size * nmemb);
                }
                res->headers[header] = "true";
        } else {
                std::string header_key = header.substr(0, break_point);
                trim(header_key);
                std::string header_value = header.substr(break_point + 1);
                trim(header_value);
                res->headers[header_key] = header_value;
        }
        return (size * nmemb);
}

size_t Handle::read_callback(void *data, size_t size, size_t nmemb,
                             Handle::upload_object *up_obj) {
        // set size
        size_t curl_size = size * nmemb;
        size_t copy_size =
            (up_obj->length < curl_size) ? up_obj->length : curl_size;
        // copy data to buffer
        memcpy(data, up_obj->data, copy_size);
        // decrement length and increment data pointer
        up_obj->length -= copy_size;
        up_obj->data += copy_size;
        // return copied size
        return copy_size;
}

}  // namespace asoni ends here
