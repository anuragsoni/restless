/*
 * @Filename: helpers.hpp
 * @Author: Anurag Soni <anuragsoni.13@gmail.com>
 * @Description: Helper functions and meta information
 */
#pragma once
#include <algorithm>
#define AGENT_NAME "restless/0.2"
namespace
{
// Extensions for std::string to trim whitespace
inline std::string& ltrim( std::string& str )
{
    if ( !str.size() ) return str;
    // find the last whitespace chr, then delete from there to end.
    auto iter = --str.end() ;
    while ( isspace( *iter ) ) --iter;
    str.erase( ++iter, str.end() ) ;
    return str ;
}

inline std::string& rtrim( std::string& str )
{
    if ( !str.size() ) return str;
    // find first non-whitespace, then delete from begin to there.
    auto iter = str.begin() ;
    while ( iter != str.end() && isspace( *iter ) ) ++iter;
    str.erase( str.begin(), iter ) ;
    return str ;
}

inline std::string& trim( std::string& str )
{
    return rtrim( ltrim( str ) ) ;
}

}