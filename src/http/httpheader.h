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

#ifndef CONFIG_HTTPHEADER_H
#define CONFIG_HTTPHEADER_H

#include <string>
#include <vector>
#include <map>

// https://github.com/envoyproxy/envoy/blob/main/source/common/http/headers.h


class HttpHeader {
private:
    std::map<std::string, std::string> headers;

public:
    void addHeader(const std::string& name, const std::string& value);
    std::string getHeader(const std::string& name);
    std::vector<std::string> getHeaderNames();
};


#endif //CONFIG_HTTPHEADER_H
