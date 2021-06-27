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

#ifndef CONFIG_REQUEST_H
#define CONFIG_REQUEST_H

#include <string>

class HttpHeader;

class Request {
public:
    virtual std::string getScheme() = 0;

    virtual std::string getDomain() = 0;

    virtual std::string getPort() = 0;

    virtual std::string getUri() = 0;

    virtual std::string getQueryString() = 0;

    virtual HttpHeader *getHeader() = 0;

    virtual std::string getParameter(const std::string &name) = 0;

    virtual std::string getCookie(const std::string &name) = 0;

    virtual std::string getMethod() = 0;

    virtual std::string getVersion() = 0;

    virtual std::string getRemoteAddress() = 0;
};


#endif //CONFIG_REQUEST_H
