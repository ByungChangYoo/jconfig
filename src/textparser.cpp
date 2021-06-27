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

#include "textparser.h"
#include "textvalue.h"
#include "text.h"
#include "tokeniterator.h"
#include "token.h"

TextParser::TextParser(TokenIterator *iterator)
    : Parser(iterator) {
}

ConfigValue *TextParser::parse() {
    const Token* token = iterator->next();
    if (token->type() != Token::Text) {
        return nullptr;
    }
    return new TextValue(token->text());
}
