/*
 * @Author: dylan
 * @Date: 2021-09-03 16:56:15
 * @LastEditTime: 2021-09-04 23:48:03
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

    // std::string getTest("GET /index.html HTTP/1.1\r\n\r\n");
    // if (httpRequestParser.parse(httpRequest, &*getTest.begin(), &*getTest.end()) == ParseResult::ParseSuccess) {
    //     std::cout << "getTest parsed successfully!\n";
    //     std::cout << "request dump:\n";
    //     httpRequest.dump();
    //     httpRequestParser.reset();
    //     httpRequest.clear();
    // } else {
    //     std::cout << "getTest parsed failed!\n";
    // }

    // std::cout << std::endl;

    // std::string postTest("POST /index.html HTTP/1.1\r\n\r\n");
    // if(httpRequestParser.parse(httpRequest, &*postTest.begin(), &*postTest.end()) == ParseResult::ParseSuccess) {
    //     std::cout << "postTest parsed successfully!\n";
    //     std::cout << "request dump:\n";
    //     httpRequest.dump();
    //     httpRequestParser.reset();
    //     httpRequest.clear();
    // } else {
    //     std::cout << "postTest parsed failed!\n";
    // }

    // std::cout << std::endl;

    std::string getHeadersTest("GET /index.html HTTP/1.1\r\n"
                               "Host: 127.0.0.1\r\n"
                               "Connection: Keep-Alive\r\n"
                               "\r\n");
    if(httpRequestParser.parse(httpRequest, &*getHeadersTest.begin(), &*getHeadersTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "getHeadersTest parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "getHeadersTest parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    std::string incompleteReqTestA("GET /index.html HTTP/1\r\n"
                                   "Host: 127.0.0.1\r\n"
                                   "Connection: Keep-Alive\r\n"
                                   "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestA.begin(), &*incompleteReqTestA.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestA parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "incompleteReqTestA parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    std::string incompleteReqTestB("GET /index.html HTTP/1.1\r\n"
                                  "Host 127.0.0.1\r\n"
                                  "Connection: Keep-Alive\r\n"
                                  "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestB.begin(), &*incompleteReqTestB.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestB parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "incompleteReqTestB parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    std::string incompleteReqTestC("GET /index.html HTTP/1.1\n"
                                  "Host 127.0.0.1\r\n"
                                  "Connection: Keep-Alive\r\n"
                                  "\r\n");
    if(httpRequestParser.parse(httpRequest, &*incompleteReqTestC.begin(), &*incompleteReqTestC.end()) == ParseResult::ParseSuccess) {
        std::cout << "incompleteReqTestC parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "incompleteReqTestC parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    std::string postContentTest("POST /index.html HTTP/1.1\r\n"
                                "Host: 127.0.0.1\r\n"
                                "Content-Length: 10\r\n"
                                "Connection: Keep-Alive\r\n"
                                "\r\n"
                                "0123456789");
    if(httpRequestParser.parse(httpRequest, &*postContentTest.begin(), &*postContentTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "postContentTest parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "postContentTest parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    std::string postChunkTest("POST /index.html HTTP/1.1\r\n"
                              "Host: 127.0.0.1\r\n"
                              "Transfer-Encoding: Chunked\r\n"
                              "Connection: Keep-Alive\r\n"
                              "\r\n"
                              "8\r\n"
                              "fuck you\r\n"
                              "3\r\n"
                              "thu\r\n"
                              "0\r\n"
                              "\r\n");
    if(httpRequestParser.parse(httpRequest, &*postChunkTest.begin(), &*postChunkTest.end()) == ParseResult::ParseSuccess) {
        std::cout << "postChunkTest parsed successfully!\n";
        std::cout << "request dump:\n";
        httpRequest.dump();
    } else {
        std::cout << "postChunkTest parsed failed!\n";
    }

    httpRequestParser.reset();
    httpRequest.clear();
    std::cout << std::endl;

    return 0;
}