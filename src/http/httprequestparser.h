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

#ifndef CONFIG_HTTPREQUESTPARSER_H
#define CONFIG_HTTPREQUESTPARSER_H

#include <sstream>
#include "httprequest.h"

class ByteBuffer;
class HttpHeaderParser;

class HttpRequestParser {
    enum State {
        METHOD_WHITESPACE,
        METHOD,
        URI_WHITESPACE,
        URI,
        QUERYSTRING_WHITESPACE,
        QUERYSTRING,
        PROTOCOL_WHITESPACE,
        PROTOCOL,
        LAST_CRLF,
        HEADER,
        COMPLETE
    };

    std::stringstream method;
    std::stringstream uri;
    std::stringstream queryString;
    std::stringstream protocol;
    State state = State::METHOD_WHITESPACE;
    HttpHeaderParser *parser;

public:
    HttpRequestParser();
    virtual ~HttpRequestParser();

public:
    int parse(ByteBuffer &buffer, HttpRequest &request);
    int parse(const char *data, int length, HttpRequest &request);

private:
    void parseMethod(ByteBuffer &buffer, HttpRequest &request);

    void parseUri(ByteBuffer &buffer, HttpRequest &request);

    void parseQueryString(ByteBuffer &buffer, HttpRequest &request);

    void parseProtocol(ByteBuffer &buffer, HttpRequest &request);

    void parserHeader(ByteBuffer &buffer, HttpRequest &request);

    void parseWhitespace(ByteBuffer &buffer, bool includeCrlf, State next);

    void changeState(State state);
};


#endif
