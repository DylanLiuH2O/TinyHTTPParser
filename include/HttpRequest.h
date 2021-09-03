/*
 * @Author: dylan
 * @Date: 2021-09-03 15:54:42
 * @LastEditTime: 2021-09-03 22:54:48
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TinyHTTPParser/include/HttpRequest.h
 */
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <iostream>
#include <sstream>
#include <unordered_map>

class HttpReuestParser;
class HttpRequest {
    friend class HttpRequestParser;
public:
    HttpRequest()
        : m_majorVersion(0), m_minorVersion(0), m_keepAlive(false)
    { }

    void dump() const;
    std::string method() const;
    std::string protocol() const;
    std::string uri() const;
    std::string content() const;

    void clear();

private:
    std::string                                  m_method;
    std::string                                  m_uri;
    int                                          m_majorVersion;
    int                                          m_minorVersion;
    std::unordered_map<std::string, std::string> m_headers;
    std::string                                  m_content;
    bool                                         m_keepAlive;
};

#endif /* HTTP_REQUEST_H */