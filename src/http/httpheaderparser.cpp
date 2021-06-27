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

#include "httpheaderparser.h"
#include "httpheader.h"
#include "../bytebuffer.h"

HttpHeaderParser::~HttpHeaderParser() {
    name.str("");
    value.str("");
}

bool HttpHeaderParser::parse(ByteBuffer &buffer, HttpHeader &header) {
    while (buffer.more()) {
        switch (state) {
            case NAME_WHITESPACE:
                parseNameWhiteSpace(buffer);
                break;
            case NAME:
                parseName(buffer);
                break;
            case VALUE_WHITESPACE:
                parseValueWhiteSpace(buffer);
                break;
            case VALUE:
                parseValue(buffer, header);
                break;
            case LAST_CRLF:
                parseLastCrlf(buffer);
                break;
            default:
                break;
        }
        if (state == State::COMPLETE) {
            return true;
        }
    }
    return false;
}

bool HttpHeaderParser::parse(const char *data, const int length, HttpHeader &header) {
    ByteBuffer buffer(data, length);
    return parse(buffer, header);
}

void HttpHeaderParser::parseNameWhiteSpace(ByteBuffer &buffer) {
    if (!buffer.more()) {
        return;
    }

    //
    // the folded header start with the space(' ') or the tab('\t')
    // the content-type below is a folded header value.

    // Content-Type : text/html;
    //                charset=UTF-8   <------ folded
    // Content-Length : 1024
    //

    char c = buffer.next();

    // it is a folded value, so change a state to a value.
    if (c == ' ' || c == '\t') {
        changeState(State::VALUE_WHITESPACE);
        return;
    } else {
        buffer.push(c);
    }
    changeState(State::NAME);
}

void HttpHeaderParser::parseName(ByteBuffer &buffer) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == '\n') {
            changeState(State::COMPLETE);
            break;
        } else if (c == '\r') {
            changeState(State::LAST_CRLF);
            break;
        } else if (c == ':') {
            changeState(State::VALUE);
            break;
        } else {
            name << c;
        }
    }
}

void HttpHeaderParser::parseValueWhiteSpace(ByteBuffer &buffer) {
    char c;
    while (buffer.more()) {
        c = buffer.next();
        if (c == ' ' || c == '\t') {
            continue;
        }
        changeState(State::VALUE);
        buffer.push(c);
        break;
    }
}


void HttpHeaderParser::parseValue(ByteBuffer &buffer, HttpHeader &header) {
    char c = 0;
    while (buffer.more()) {
        c = buffer.next();
        // break while loop to remove '\r'
        if (c == '\r') {
            continue;
        } else if (c == '\n') {
            header.addHeader(name.str(), value.str());
            name.str("");
            value.str("");
            changeState(State::NAME_WHITESPACE);
            break;
        } else {
            value << c;
        }
    }
}


void HttpHeaderParser::parseLastCrlf(ByteBuffer &buffer) {
    char c;
    if (buffer.more()) {
        c = buffer.next();
        if (c == '\n') {
            changeState(State::COMPLETE);
        } else {
            // throw new IllegalArgumentException("The illegal character[" + (char) b + "] exists in last line feed.");
        }
    }
}


void HttpHeaderParser::changeState(State state) {
    this->state = state;
}


