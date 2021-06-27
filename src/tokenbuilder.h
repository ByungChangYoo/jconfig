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

#ifndef CONFIG_TOKENBUILDER_H
#define CONFIG_TOKENBUILDER_H


#include <string>

class CharReader;

class TokenQueue;

class Token;

class TokenBuilder {
public:
    static void build(CharReader *reader, TokenQueue *queue);

    static Token *createSingleLineComment(CharReader *reader);

    static Token *createMultipleLineComment(CharReader *reader);

    static Token *createWhiteSpaceToken(CharReader *reader);

    static Token *createQuotedText(CharReader *reader);

    static Token *createDoubleQuotedText(CharReader *reader);

    static Token *createTripleQuotedText(CharReader *reader);

    static Token *createSingleQuotedText(CharReader *reader);

    static Token *createText(CharReader *reader);

    static Token *createText(CharReader *reader, const std::string &text);

    static void add(Token *token, TokenQueue *queue);
};


#endif //CONFIG_TOKENBUILDER_H
