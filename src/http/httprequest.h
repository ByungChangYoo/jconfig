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
#ifndef CONFIG_HTTPREQUEST_H
#define CONFIG_HTTPREQUEST_H

#include "request.h"

class HttpHeader;

class HttpRequest : public Request {
private:
    std::string scheme;
    std::string domain;
    std::string port;
    std::string uri;
    std::string queryString;
    std::string method;
    std::string version;
    std::string remoteAddress;
    HttpHeader *header = nullptr;

public:
    HttpRequest();
    virtual ~HttpRequest();

public:

    std::string getScheme() override;

    std::string getDomain() override;

    std::string getPort() override;

    std::string getUri() override;

    std::string getQueryString() override;

    HttpHeader *getHeader() override;

    std::string getParameter(const std::string &name) override;

    std::string getCookie(const std::string &name) override;

    std::string getMethod() override;

    std::string getVersion() override;

    std::string getRemoteAddress();

    void setScheme(const std::string &scheme);

    void setDomain(const std::string &domain);

    void setPort(const std::string &port);

    void setUri(const std::string &uri);

    void setQueryString(const std::string &queryString);

    void setMethod(const std::string &method);

    void setVersion(const std::string &version);

    void setRemoteAddress(const std::string &remoteAddress);
};


#endif //CONFIG_HTTPREQUEST_H
