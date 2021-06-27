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
#include "httpheader.h"

void HttpHeader::addHeader(const std::string &name, const std::string &value) {
    if (!name.empty()) {
        headers.insert(std::make_pair(name, value));
    }
}

std::string HttpHeader::getHeader(const std::string &name) {
    return headers.at(name);
}

std::vector<std::string> HttpHeader::getHeaderNames() {
    std::vector<std::string> names;
    names.reserve(headers.size());
    for_each(headers.begin(), headers.end(), [&](auto entry) {
        names.emplace_back(entry.first);
    });
    return names;
}
