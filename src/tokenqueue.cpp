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
#include <queue>
#include <stack>
#include "tokenqueue.h"
#include "token.h"
#include "tokeniterator.h"

class TokenIteratorImpl : public TokenIterator {
private:
    std::stack<Token*> pushed;
    std::queue<Token*>* queue;

public:
    TokenIteratorImpl(std::queue<Token*>* queue) {
        this->queue = queue;
    }

public:
    Token* next() override {
        Token* token = nullptr;
        if (!pushed.empty()) {
            token = pushed.top();
            pushed.pop();
            return token;
        }
        token = queue->front();
        queue->pop();
        return token;
    }

    void push(Token* token) override {
        pushed.push(token);
    }

    bool more() override {
        if (!pushed.empty()) {
            return true;
        }
        return !queue->empty();
    }
};


Token* TokenQueue::peek() {
    return tokens.front();
}

void TokenQueue::add(Token *token) {
    if (token == nullptr) {
        return;
    }
    const Token::Type type = token->type();
    if (type == Token::SingleLineComment ||
            type == Token::MultipleLineComment ||
            type == Token::WhiteSpace ||
            type == Token::NewLine) {
        return;
    }
    tokens.push(token);
}

TokenIterator* TokenQueue::iterator() {
    return new TokenIteratorImpl(&tokens);
}
