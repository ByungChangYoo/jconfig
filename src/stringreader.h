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

#ifndef CONFIG_STRINGREADER_H
#define CONFIG_STRINGREADER_H

#include <string>
#include "charreader.h"

class StringReader : public CharReader {
private:
    std::string text;
    int length = 0;
    int position = 0;

public:
    StringReader(const std::string text);

public:
    virtual char next();
    virtual char peek();
    virtual bool more();
};


#endif //CONFIG_STRINGREADER_H