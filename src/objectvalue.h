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

#ifndef CONFIG_OBJECTVALUE_H
#define CONFIG_OBJECTVALUE_H


#include <vector>
#include <map>
#include "configvalue.h"

class Field;

class ObjectValue : public ConfigValue {
    using Fields = std::vector<Field *>;
private:
    Fields fields;
    std::map<std::string, Fields *> mapping;

public:
    bool isObject() override;

    void addMethod(ConfigValue *name, ConfigValue *value);

    void addField(ConfigValue *name, ConfigValue *value);

public:
    void each(std::function<void(ConfigValue *, ConfigValue *)> consumer);
    void visit(Visitor visitor) const override;
};


#endif //CONFIG_OBJECTVALUE_H
