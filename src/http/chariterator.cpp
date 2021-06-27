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

#include "chariterator.h"

CharIterator::CharIterator(const char *data, const int length) {
    this->data = data;
    this->length = length;
}

char CharIterator::peek() {
    if (!pushed.empty()) {
        return pushed.top();
    }
    return data[position];
}


char CharIterator::next() {
    if (!pushed.empty()) {
        char c = pushed.top();
        pushed.pop();
        return c;
    }
    return data[position++];
}


void CharIterator::push(char c) {
    pushed.push(c);
}


bool CharIterator::more() {
    if (!pushed.empty()) {
        return true;
    }
    return position < length;
}