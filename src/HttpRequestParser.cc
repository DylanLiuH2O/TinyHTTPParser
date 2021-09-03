/*
 * @Author: dylan
 * @Date: 2021-09-03 16:01:41
 * @LastEditTime: 2021-09-03 23:37:07
 * @LastEditors: dylan
 * @Description: 
 * @FilePath: /TinyHTTPParser/src/HttpRequestParser.cc
 */
#include <cctype>
#include "../include/HttpRequestParser.h"

ParseResult HttpRequestParser::parse(HttpRequest& httpRequest, char* bufferBegin, char* bufferEnd) {
    char* charPtr = bufferBegin;
    char ch;

    while (charPtr != bufferEnd) {
        ch = *charPtr;    
        switch (m_currentState) {
            case ParseState::ParseStart:
                if (std::isalpha(ch) == 0) {
                    return ParseResult::ParseError;
                } else {
                    m_currentState = ParseState::RequestLine_Method;
                    httpRequest.m_method.push_back(ch);
                }
                break;
            case ParseState::RequestLine_Method:
                if (ch == ' ') {
                    m_currentState = ParseState::RequestLine_SpaceBeforeURI;
                } else if (std::isalpha(ch) == 0) {
                    return ParseResult::ParseError;
                } else {
                    httpRequest.m_method.push_back(ch);
                }
                break;
            case ParseState::RequestLine_SpaceBeforeURI:
                if (std::iscntrl(ch) == 0)  {
                    m_currentState = ParseState::RequestLine_URI;
                    httpRequest.m_uri.push_back(ch);
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_URI:
                if (ch == ' ') {
                    m_currentState = ParseState::RequestLine_SpaceBeforeProtocol;
                } else if (std::iscntrl(ch) != 0)  {
                    return ParseResult::ParseError;
                } else {
                    httpRequest.m_uri.push_back(ch);
                }
                break;
            case ParseState::RequestLine_SpaceBeforeProtocol:
                if (ch == 'H') {
                    m_currentState = ParseState::RequestLine_ProtocolH;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_ProtocolH:
                if (ch == 'T') {
                    m_currentState = ParseState::RequestLine_ProtocolHT;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_ProtocolHT:
                if (ch == 'T') {
                    m_currentState = ParseState::RequestLine_ProtocolHTT;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_ProtocolHTT:
                if (ch == 'P') {
                    m_currentState = ParseState::RequestLine_ProtocolHTTP;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_ProtocolHTTP:
                if (ch == '/') {
                    m_currentState = ParseState::RequestLine_ProtocolSlash;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_ProtocolSlash:
                if (std::isdigit(ch) != 0) {
                    m_currentState = ParseState::RequestLine_VersionMajor;
                    httpRequest.m_majorVersion = ch - '0';
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_VersionMajor:
                if (ch == '.') {
                    m_currentState = ParseState::RequestLine_VersionDot;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_VersionDot:
                if (std::isdigit(ch) != 0) {
                    m_currentState = ParseState::RequestLine_VersionMinor;
                    httpRequest.m_minorVersion = ch - '0';
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_VersionMinor:
                if (ch == '\r') {
                    m_currentState = ParseState::RequestLine_Carriage;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_Carriage:
                if (ch == '\n') {
                    m_currentState = ParseState::RequestLine_LineFeed;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::RequestLine_LineFeed:
                if (ch == '\r') {
                    m_currentState = ParseState::BlankLine_Carriage;
                } else if (std::isalpha(ch) != 0){
                    m_currentState = ParseState::Headers_Key;
                    m_headerKeyBuffer.push_back(ch);
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::Headers_Key:
                if (ch == ':') {
                    m_currentState = ParseState::Headers_Colon;
                    httpRequest.m_headers[m_headerKeyBuffer] = "";
                } else if (std::iscntrl(ch) != 0){
                    return ParseResult::ParseError;
                } else {
                    m_headerKeyBuffer.push_back(ch);
                }
                break;
            case ParseState::Headers_Colon:
                if (ch == ' ') {
                    m_currentState = ParseState::Headers_SpaceBeforeValue;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::Headers_SpaceBeforeValue:
                if (std::iscntrl(ch) == 0) {
                    m_currentState = ParseState::Headers_Value;
                    m_headerValueBuffer.push_back(ch);
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::Headers_Value:
                if (ch == '\r') {
                    httpRequest.m_headers[m_headerKeyBuffer] = m_headerValueBuffer;
                    m_headerKeyBuffer.clear();
                    m_headerValueBuffer.clear();
                    m_currentState = ParseState::Headers_Carriage;
                } else if (std::iscntrl(ch) == 0) {
                    m_headerValueBuffer.push_back(ch);
                } else {
                    return ParseResult::ParseError;
                }
                break;

            case ParseState::Headers_Carriage:
                if (ch == '\n') {
                    m_currentState = ParseState::Headers_LineFeed;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::Headers_LineFeed:
                if (ch == '\r') {
                    m_currentState = ParseState::BlankLine_Carriage;
                } else if (std::isalpha(ch) != 0) {
                    m_currentState = ParseState::Headers_Key;
                    m_headerKeyBuffer.push_back(ch);
                } else {
                    return ParseResult::ParseError;
                }
                break;
            case ParseState::BlankLine_Carriage:
                if (ch == '\n') {
                    return ParseResult::ParseSuccess;
                } else {
                    return ParseResult::ParseError;
                }
                break;
            default:
                break;
        }
        charPtr++;
    }

    return ParseResult::ParseAgain;
}

void HttpRequestParser::reset() {
    m_currentState = ParseState::ParseStart;
    m_headerKeyBuffer.clear();
    m_headerValueBuffer.clear();
}