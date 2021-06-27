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

#include <sstream>
#include "tokenbuilder.h"
#include "charreader.h"
#include "tokenqueue.h"
#include "singlelinecomment.h"
#include "multiplelinecomment.h"
#include "whitespace.h"
#include "doublequotedtext.h"
#include "triplequotedtext.h"
#include "singlequotedtext.h"
#include "newline.h"
#include "colon.h"
#include "comma.h"
#include "closearray.h"
#include "openarray.h"
#include "closeobject.h"
#include "openobject.h"
#include "exclamation.h"
#include "openmethod.h"
#include "closemethod.h"

void TokenBuilder::build(CharReader *reader, TokenQueue *queue) {
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\n') {
            reader->next();
            add(new NewLine(), queue);
        } else if (c == '#') {
            add(createSingleLineComment(reader), queue);
        } else if (c == '/') {
            reader->next();
            if (reader->more()) {
                c = reader->peek();
                if (c == '*') {
                    add(createMultipleLineComment(reader), queue);
                } else {
                    add(createText(reader, "/"), queue);
                }
            } else {
                add(createText(reader, "/"), queue);
            }
        } else if (c == ' ' || c == '\t') {
            add(createWhiteSpaceToken(reader), queue);
        } else if (c == '\"') {
            add(createQuotedText(reader), queue);
        } else if (c == '\'') {
            add(createSingleQuotedText(reader), queue);
        } else if (c == ':') {
            reader->next();
            add(new Colon(), queue);
        } else if (c == '!') {
            reader->next();
            add(new Exclamation(), queue);
        } else if (c == '{') {
            reader->next();
            add(new OpenObject(), queue);
        } else if (c == '}') {
            reader->next();
            add(new CloseObject(), queue);
        } else if (c == '[') {
            reader->next();
            add(new OpenArray(), queue);
        } else if (c == ']') {
            reader->next();
            add((new CloseArray()), queue);
        } else if (c == '(') {
            reader->next();
            add(new OpenMethod(), queue);
        } else if (c == ')') {
            reader->next();
            add(new CloseMethod(), queue);
        } else if (c == ',') {
            reader->next();
            add(new Comma(), queue);
        } else {
            add(createText(reader), queue);
        }
    }
}

Token *TokenBuilder::createSingleLineComment(CharReader *reader) {
    std::stringstream ss;
    reader->next();
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\n') {
            break;
        }
        ss << reader->next();
    }
    return new SingleLineComment(ss.str());
}

Token *TokenBuilder::createMultipleLineComment(CharReader *reader) {
    std::stringstream ss;
    reader->next();
    while (reader->more()) {
        char c = reader->next();
        if (c == '*') {
            if (reader->more()) {
                c = reader->next();
                if (c == '/') {
                    break;
                } else {
                    ss << '*' << c;
                }
            }
        } else {
            ss << c;
        }
    }
    return new MultipleLineComment(ss.str());
}

Token *TokenBuilder::createWhiteSpaceToken(CharReader *reader) {
    std::stringstream ss;
    while (reader->more()) {
        char c = reader->peek();
        if (c != ' ' && c != '\t') {
            break;
        }
        ss << reader->next();
    }
    return new WhiteSpace(ss.str());
}

Token *TokenBuilder::createQuotedText(CharReader *reader) {
    int quoteCount = 0;
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\"') {
            reader->next();
            quoteCount++;
            if (quoteCount == 3) {
                break;
            }
        } else {
            break;
        }
    }

    // This means empty string ""
    if (quoteCount == 2) {
        return new DoubleQuotedText("");
    }

    if (quoteCount == 3) {
        return createTripleQuotedText(reader);
    } else {
        return createDoubleQuotedText(reader);
    }
}

Token *TokenBuilder::createDoubleQuotedText(CharReader *reader) {
    std::stringstream ss;
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\"') {
            reader->next();
            break;
        }
        ss << reader->next();
    }
    return new DoubleQuotedText(ss.str());
}

Token *TokenBuilder::createTripleQuotedText(CharReader *reader) {
    std::stringstream ss;
    int quoteCount = 0;
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\"') {
            reader->next();
            quoteCount++;
            if (quoteCount == 3) {
                break;
            }
        } else {
            if (quoteCount == 1) {
                ss << "\"";
            }
            if (quoteCount == 2) {
                ss << "\"\"";
            }
            quoteCount = 0;
            ss << reader->next();
        }
    }
    return new TripleQuotedText(ss.str());
}

Token *TokenBuilder::createSingleQuotedText(CharReader *reader) {
    std::stringstream ss;
    reader->next();
    while (reader->more()) {
        char c = reader->peek();
        if (c == '\'') {
            reader->next();
            break;
        }
        ss << reader->next();
    }
    return new SingleQuotedText(ss.str());
}

Token *TokenBuilder::createText(CharReader *reader) {
    std::stringstream ss;
    while (reader->more()) {
        char c = reader->peek();
        if (' ' == c ||
            '\t' == c ||
            '\n' == c ||
            ':' == c ||
            '{' == c ||
            '}' == c ||
            '[' == c ||
            ']' == c ||
            '(' == c ||
            ')' == c) {
            break;
        }
        ss << reader->next();
    }
    return new Text(ss.str());
}

Token *TokenBuilder::createText(CharReader *reader, const std::string &text) {
    std::stringstream ss;
    ss << text;
    while (reader->more()) {
        char c = reader->peek();
        if (' ' == c ||
            '\t' == c ||
            '\n' == c ||
            ':' == c ||
            '{' == c ||
            '}' == c ||
            '[' == c ||
            ']' == c ||
            '(' == c ||
            ')' == c) {
            break;
        }
        ss << reader->next();
    }
    return new Text(ss.str());
}

void TokenBuilder::add(Token *token, TokenQueue *queue) {
    queue->add(token);
}
