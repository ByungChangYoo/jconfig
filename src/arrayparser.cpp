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

#include "arrayparser.h"
#include "arrayvalue.h"
#include "tokeniterator.h"
#include "comma.h"
#include "openarray.h"
#include "closearray.h"
#include "openmethod.h"
#include "closemethod.h"

ArrayParser::ArrayParser(TokenIterator *iterator)
        : Parser(iterator) {
    state = State::OPEN;
}

ConfigValue *ArrayParser::parse() {
    return parse(new ArrayValue());
}

ConfigValue *ArrayParser::parse(ArrayValue *array) {
    while (iterator->more()) {
        if (state == State::FINISH) {
            break;
        }
        Token *token = iterator->next();
        switch (state) {
            case OPEN: {
                parseOpen(token);
                break;
            }
            case VALUE: {
                ConfigValue *value = parseValue(token);
                if (value != nullptr) {
                    array->add(value);
                }
                break;
            }
            case NEXT: {
                parseNext(token);
                break;
            }
        }
    }
    return (ConfigValue *) array;
}

void ArrayParser::parseOpen(Token *token) {
    if (isOpenToken(token)) {
        state = State::VALUE;
    } else {
        state = State::FINISH;
    }
}

ConfigValue *ArrayParser::parseValue(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Comma) {
        return nullptr;
    } else if (isCloseToken(token)) {
        state = State::FINISH;
        return nullptr;
    } else {
        state = State::NEXT;
        iterator->push(token);
        Parser *parser = Parser::create(token, iterator);
        if (parser != nullptr) {
            return parser->parse();
        } else {
            return nullptr;
        }
    }
}

void ArrayParser::parseNext(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Comma) {
        state = State::VALUE;
    } else if (type == Token::CloseArray) {
        state = State::FINISH;
    } else {
        // [A B C] without comma
        iterator->push(token);
        state = State::VALUE;
    }
}

bool ArrayParser::isOpenToken(Token *token) {
    const Token::Type type = token->type();
    return (type == Token::OpenArray ||
            type == Token::OpenMethod);
}

bool ArrayParser::isCloseToken(Token *token) {
    const Token::Type type = token->type();
    return (type == Token::CloseArray ||
            type == Token::CloseMethod);
}