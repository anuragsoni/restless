/*
 * @Filename: helpers.hpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: Helper functions and meta information
 */
#pragma once
#include <algorithm>
#include <functional>
#include <cctype>
#define AGENT_NAME "restless/0.2"
namespace
{
// Trim string from beginning
inline std::string &ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
// Trim string from the end
inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
// Trim string from both ends
inline std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}

}
