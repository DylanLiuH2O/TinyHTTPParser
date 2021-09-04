/*
 * @Author: dylan
 * @Date: 2021-09-03 15:45:53
 * @LastEditTime: 2021-09-04 22:58:46
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TinyHTTPParser/src/HttpRequest.cc
 */
#include "../include/HttpRequest.h"

void HttpRequest::dump() const {
    std::cout << m_method << " " << m_uri << " ";
    std::cout << "HTTP/" << m_majorVersion << ".";
    std::cout << m_minorVersion << "\n";
    for (auto& item : m_headers) {
        std::cout << item.first << ": "  << item.second << "\n";
    }
    std::cout << m_content << "\n";
}

std::string HttpRequest::method() const {
    return m_method;
}
std::string HttpRequest::protocol() const {
    return "HTTP/" + std::to_string(m_majorVersion) + "." + std::to_string(m_minorVersion);
}
std::string HttpRequest::uri() const {
    return m_uri;
}
std::string HttpRequest::content() const {
    return m_content;
}

void HttpRequest::clear() {
    m_method.clear();
    m_uri.clear();
    m_majorVersion = 0;
    m_minorVersion = 0;
    m_headers.clear();
    m_content.clear();
    m_keepAlive = false;
}