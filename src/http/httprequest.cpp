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
#include "httprequest.h"
#include "httpheader.h"

HttpRequest::HttpRequest() {
    header = new HttpHeader();
}


HttpRequest::~HttpRequest() {
    delete header;
}


std::string HttpRequest::getScheme() {
    return scheme;
}

std::string HttpRequest::getDomain() {
    return domain;
}

std::string HttpRequest::getPort() {
    return port;
}

std::string HttpRequest::getUri() {
    return uri;
}

std::string HttpRequest::getQueryString() {
    return queryString;
}

HttpHeader *HttpRequest::getHeader() {
    return header;
}

std::string HttpRequest::getParameter(const std::string &name) {
    return std::string();
}

std::string HttpRequest::getCookie(const std::string &name) {
    return std::string();
}

std::string HttpRequest::getMethod() {
    return method;
}

std::string HttpRequest::getVersion() {
    return version;
}

std::string HttpRequest::getRemoteAddress() {
    return remoteAddress;
}

void HttpRequest::setScheme(const std::string &scheme) {
    this->scheme = scheme;
}

void HttpRequest::setDomain(const std::string &domain) {
    this->domain = domain;
}

void HttpRequest::setPort(const std::string &port) {
    this->port = port;
}

void HttpRequest::setUri(const std::string &uri) {
    this->uri = uri;
}

void HttpRequest::setQueryString(const std::string &queryString) {
    this->queryString = queryString;
}

void HttpRequest::setMethod(const std::string &method) {
    this->method = method;
}

void HttpRequest::setVersion(const std::string &version) {
    this->version = version;
}

void HttpRequest::setRemoteAddress(const std::string &remoteAddress) {
    this->remoteAddress = remoteAddress;
}

