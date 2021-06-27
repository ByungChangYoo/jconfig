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

#include "parser.h"
#include "tokeniterator.h"
#include "arrayparser.h"
#include "objectparser.h"
#include "textparser.h"

Parser::Parser(TokenIterator *iterator) {
    this->iterator = iterator;
}

Parser *Parser::create(Token *token, TokenIterator *iterator) {
    if (token == nullptr) {
        return nullptr;
    }
    const Token::Type type = token->type();
    if (type == Token::Text ||
        type == Token::SingleQuotedText ||
        type == Token::DoubleQuotedText ||
        type == Token::TripleQuotedText) {
        return new TextParser(iterator);
    } else if (type == Token::OpenObject) {
        return new ObjectParser(iterator);
    } else if (type == Token::OpenArray) {
        return new ArrayParser(iterator);
    } else if (type == Token::OpenMethod) {
        return new ArrayParser(iterator);
    }
    return nullptr;
}