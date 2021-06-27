/*
 * Copyright CONFIG. 2021-2021
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <iostream>
#include "httprequestparser.h"
#include "httpheaderparser.h"
#include "../bytebuffer.h"


HttpRequestParser::HttpRequestParser() {
    parser = new HttpHeaderParser();
}

HttpRequestParser::~HttpRequestParser() {
    delete parser;
}

int HttpRequestParser::parse(ByteBuffer &buffer, HttpRequest &request) {
    while (buffer.more()) {
        switch (state) {
            case METHOD_WHITESPACE:
                parseWhitespace(buffer, true, State::METHOD);
                break;
            case METHOD:
                parseMethod(buffer, request);
                break;
            case URI_WHITESPACE:
                parseWhitespace(buffer, false, State::URI);
                break;
            case URI:
                parseUri(buffer, request);
                break;
            case QUERYSTRING_WHITESPACE:
                parseWhitespace(buffer, false, State::QUERYSTRING);
                break;
            case QUERYSTRING:
                parseQueryString(buffer, request);
                break;
            case PROTOCOL_WHITESPACE:
                parseWhitespace(buffer, false, State::PROTOCOL);
                break;
            case PROTOCOL:
                parseProtocol(buffer, request);
                break;
            case HEADER:
                parserHeader(buffer, request);
                break;
            default:
                break;
        }

        if (state == State::COMPLETE) {
            return true;
        }
    }
    return 0;
}

int HttpRequestParser::parse(const char *data, int length, HttpRequest &request) {
    ByteBuffer buffer(data, length);
    return parse(buffer, request);
}

void HttpRequestParser::parseMethod(ByteBuffer &buffer, HttpRequest &request) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == ' ' || c == '\t') {
            changeState(State::URI_WHITESPACE);
            break;
        } else if (c == '\r' || c == '\n') {
            //throw new IllegalArgumentException("The HTTP request line missing URI.");
        } else {
            method << c;
        }
    }

    if (state != State::METHOD) {
        request.setMethod(method.str());
    }
}


void HttpRequestParser::parseUri(ByteBuffer &buffer, HttpRequest &request) {
    //
    // the URI has three patterns below.
    // case 1) /context/test.jsp HTTP/1.1          : without a query string
    // case 2) /context/test.jsp?a=a&b=b HTTP/1.1  : with a query string
    // case 3) /context/test.jsp?a=a&b=b\r\n       : HTTP/0.9
    //
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == ' ' || c == '\t') {
            changeState(State::PROTOCOL_WHITESPACE);
            break;
        } else if (c == '?') {
            changeState(State::QUERYSTRING_WHITESPACE);
            break;
        } else if (c == '\r' || c == '\n') {
            changeState(State::COMPLETE);
            break;
        } else {
            uri << c;
        }
    }

    if (state != State::URI) {
        request.setUri(uri.str());
    }
}

void HttpRequestParser::parseQueryString(ByteBuffer &buffer, HttpRequest &request) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == ' ' || c == '\t') {
            changeState(State::PROTOCOL_WHITESPACE);
            break;
        } else if (c == '\r' || c == '\n') {
            changeState(State::COMPLETE);
            break;
        } else {
            queryString << c;
        }
    }

    if (state != State::QUERYSTRING) {
        request.setQueryString(queryString.str());
    }
}


void HttpRequestParser::parseProtocol(ByteBuffer &buffer, HttpRequest &request) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == '\r') {
            continue;
        } else if (c == '\n') {
            changeState(State::HEADER);
            break;
        } else {
            protocol << c;
        }
    }

    if (state != State::PROTOCOL) {
        request.setVersion(protocol.str());
    }
}

void HttpRequestParser::parserHeader(ByteBuffer &buffer, HttpRequest &request) {
    if (parser->parse(buffer, *request.getHeader())) {
        changeState(State::COMPLETE);
    }
}

void HttpRequestParser::parseWhitespace(ByteBuffer &buffer, bool includeCrlf, State next) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == ' ' || c == '\t') {
            continue;
        }

        if (includeCrlf) {
            if (c == '\r' || c == '\n') {
                continue;
            }
        }
        buffer.push(c);
        changeState(next);
        break;
    }
}

void HttpRequestParser::changeState(State state) {
    this->state = state;
}

