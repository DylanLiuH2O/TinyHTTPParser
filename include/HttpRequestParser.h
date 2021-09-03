/*
 * @Author: dylan
 * @Date: 2021-09-03 16:01:31
 * @LastEditTime: 2021-09-03 23:15:04
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TinyHTTPParser/include/HttpRequestParser.h
 */
#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include "HttpRequest.h"

enum class ParseResult {
    ParseSuccess,
    ParseAgain,
    ParseError
};

class HttpRequestParser {
public:
    explicit HttpRequestParser()
        : m_currentState(ParseState::ParseStart) {
    }
    ParseResult parse(HttpRequest& httpRequest, char* bufferBegin, char* bufferEnd);
    void reset();

    HttpRequestParser(HttpRequestParser&) = delete;
    HttpRequestParser& operator=(HttpRequestParser&) = delete;
private:
    enum class ParseState {
        ParseStart,
        RequestLine_Method,
        RequestLine_SpaceBeforeURI,
        RequestLine_URI,
        RequestLine_SpaceBeforeProtocol,
        RequestLine_ProtocolH,
        RequestLine_ProtocolHT,
        RequestLine_ProtocolHTT,
        RequestLine_ProtocolHTTP,
        RequestLine_ProtocolSlash,
        RequestLine_VersionMajor,
        RequestLine_VersionDot,
        RequestLine_VersionMinor,
        RequestLine_Carriage,
        RequestLine_LineFeed,

        Headers_Key,
        Headers_Colon,
        Headers_SpaceBeforeValue,
        Headers_Value,
        Headers_Carriage,
        Headers_LineFeed,

        BlankLine_Carriage,
        BlankLine_LineFeed 
    };

    ParseState  m_currentState;
    std::string m_headerKeyBuffer;
    std::string m_headerValueBuffer;
};

#endif /* HTTP_REQUEST_PARSER_H */