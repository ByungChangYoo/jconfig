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

#ifndef CONFIG_TEXTVALUE_H
#define CONFIG_TEXTVALUE_H


#include <string>
#include "configvalue.h"

class TextValue : public ConfigValue {
private:
    std::string value;

public:
    TextValue(const std::string &value);

public:
    bool isText() override;
    std::string text() const override;
    void visit(Visitor visitor) const override;
};


#endif //CONFIG_TEXTVALUE_H
