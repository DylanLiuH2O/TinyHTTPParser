/*
 * @Author: dylan
 * @Date: 2021-09-03 16:56:15
 * @LastEditTime: 2021-09-04 00:14:04
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TinyHTTPParser/test/TestHttpRequest.cc
 */
#include <gtest/gtest.h>
#include "../include/HttpRequestParser.h"
#include "../include/HttpRequest.h"

int main()
{
    HttpRequestParser httpRequestParser;
    HttpRequest httpRequest;

    std::string getTest("GET /index.html HTTP/1.1\r\n\r\n");
    if (httpRequestParser.parse(httpRequest, &*getTest.begin(), &*getTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "getTest parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    std::cout << std::endl;

    std::string postTest("POST /index.html HTTP/1.1\r\n\r\n");
    if(httpRequestParser.parse(httpRequest, &*postTest.begin(), &*postTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "postTest parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    std::cout << std::endl;

    std::string getHeadersTest("GET /index.html HTTP/1.1\r\n"
                        "Host: 127.0.0.1\r\n"
                        "Connection: Keep-Alive\r\n"
                        "\r\n");
    if(httpRequestParser.parse(httpRequest, &*getHeadersTest.begin(), &*getHeadersTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "getHeadersTest parsed successfully!\n";
        std::cout << "grequest dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    std::cout << std::endl;

    std::string incompleteReqTestA("GET /index.html HTTP/1\r\n"
                                  "Host: 127.0.0.1\r\n"
                                  "Connection: Keep-Alive\r\n"
                                  "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestA.begin(), &*incompleteReqTestA.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestA parsed successfully!\n";
        std::cout << "grequest dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    std::string incompleteReqTestB("GET /index.html HTTP/1.1\r\n"
                                  "Host 127.0.0.1\r\n"
                                  "Connection: Keep-Alive\r\n"
                                  "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestB.begin(), &*incompleteReqTestB.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestB parsed successfully!\n";
        std::cout << "grequest dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    std::string incompleteReqTestC("GET /index.html HTTP/1.1\n"
                                  "Host 127.0.0.1\r\n"
                                  "Connection: Keep-Alive\r\n"
                                  "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestC.begin(), &*incompleteReqTestC.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestC parsed successfully!\n";
        std::cout << "grequest dump:\n";
        httpRequest.dump();
        httpRequestParser.reset();
        httpRequest.clear();
    } else {
        std::cout << "parsed failed!\n";
    }

    return 0;
}