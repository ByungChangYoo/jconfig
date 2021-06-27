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

#include "objectvalue.h"
#include "field.h"

bool ObjectValue::isObject() {
    return true;
}

void ObjectValue::addMethod(ConfigValue *name, ConfigValue *value) {
    fields.push_back(new Field(name, value));
}

void ObjectValue::addField(ConfigValue *name, ConfigValue *value) {
    Field *field = new Field(name, value);
    fields.push_back(field);
    if(mapping.find(name->text()) == mapping.end()) {
        mapping.insert({name->text(), new std::vector<Field*>});
    }
    mapping.at(name->text())->push_back(field);
}

void ObjectValue::each(std::function<void(ConfigValue*, ConfigValue*)> consumer) {
    for_each(fields.begin(), fields.end(), [=](Field *field) {
        consumer(field->getName(), field->getValue());
    });
}

void ObjectValue::visit(ConfigValue::Visitor visitor) const {
    for_each(fields.begin(), fields.end(), [=](Field *field) {
        ConfigValue *name = field->getName();
        ConfigValue *value = field->getValue();
        visitor(name, value);
        if (value != nullptr) {
            value->visit(visitor);
        }
    });
}
