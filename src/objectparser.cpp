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

#include "objectparser.h"
#include "objectvalue.h"
#include "tokeniterator.h"
#include "openobject.h"
#include "closeobject.h"
#include "openmethod.h"
#include "closemethod.h"
#include "comma.h"
#include "emptyvalue.h"
#include "colon.h"
#include "text.h"

ObjectParser::ObjectParser(TokenIterator *iterator)
        : Parser(iterator) {

}

ConfigValue *ObjectParser::parse() {
    return parse(new ObjectValue());
}


ConfigValue *ObjectParser::parse(ObjectValue *object) {
    while (iterator->more()) {
        if (state == State::FINISH) {
            break;
        }
        Token *token = iterator->next();
        switch (state) {
            case OPEN:
                parseOpen(token);
                break;
            case NAME:
                name = parseName(token);
                break;
            case NAME_PARAMETER:
                parseNameParameter(token);
                break;
            case COLON:
                parseColon(token);
                break;
            case ADD_FILED:
                iterator->push(token);
                if (method) {
                    object->addMethod(name, value);
                } else {
                    object->addField(name, value);
                }
                name = nullptr;
                value = nullptr;
                method = false;
                state = State::COMMA;
                break;
            case VALUE:
                value = parseValue(token);
                state = State::VALUE_PARAMETER;
                break;
            case VALUE_PARAMETER:
                parseValueParameter(token);
                break;
            case COMMA:
                parseComma(token);
                break;
            default:
                break;
        }
    }
    return (ConfigValue *) object;
}

void ObjectParser::parseOpen(Token *token) {
    const Token::Type type = token->type();
    if (type != Token::OpenObject) {
        return;
        //throw new ConfigException.Parse("The object must start with open brace bracket('{')", token);
    }
    state = State::NAME;
}

/**
 * Parses the name.
 *
 * <pre>
 * A) case : close appears without name.
 * { name : value }
 *               ~~~
 *
 * B) case : comma appears without name.
 * { name : value,,,, ... }
 *               ~~~~~
 *
 * C) case : invalid token appears.
 * { name: value, [], () }
 *                ~~~~~~
 * </pre>
 *
 * @param token the token.
 */
ConfigValue *ObjectParser::parseName(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::CloseObject) {
        // A) case : close appears without name.
        state = State::FINISH;
    } else if (type == Token::Comma) {
        // B) case : comma appears without name.
        state = State::NAME;
    } else {
        state = State::NAME_PARAMETER;
        iterator->push(token);
        Parser *parser = Parser::create(token, iterator);
        if (parser != nullptr) {
            return parser->parse();
        }
    }
    return (ConfigValue *) new EmptyValue();
}

void ObjectParser::parseNameParameter(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Colon) {
        state = State::VALUE;
    } else {
        iterator->push(token);
        Parser *parser = Parser::create(token, iterator);
        if (name != nullptr && parser != nullptr) {
            parser->parse();
            //name->parameter(parser.parse());
        }
        method = type == Token::OpenMethod;
        state = State::COLON;
    }
}

void ObjectParser::parseColon(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Colon) {
        state = State::VALUE;
    } else {
        iterator->push(token);
        state = State::ADD_FILED;
    }
}

/**
 * Parses the value parameter.
 *
 * <pre>
 * A) case : comma appears without value.
 * { name : , name : value}
 *         ~~~
 *
 * B) case : close appears without value.
 * { name : }
 *          ~~
 *
 * C) case : colon appears without value.
 * { name : : : : : , name : value}
 *          ~~~~~~~
 * </pre>
 *
 * @param token the token.
 * @return the value.
 */
ConfigValue *ObjectParser::parseValue(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Comma) {
        // A) case : comma appears without value.
        state = State::NAME;
    } else if (type == Token::CloseObject) {
        // B) case : close appears without value.
        state = State::FINISH;
    } else if (type == Token::Colon) {
        // C) case : colon appears without value.
        state = State::VALUE;
    } else {
        state = State::VALUE_PARAMETER;
        iterator->push(token);
        Parser *parser = Parser::create(token, iterator);
        if (parser != nullptr) {
            return parser->parse();
        }
    }
    return nullptr;
}

/**
 * Parses the value parameter.
 *
 * <pre>
 * A) case : comma appears without parameter.
 * { name : value, ... }
 *             ~~~
 *
 * B) case : name appears without parameter and comma.
 * { name : value name : value ... }
 *                ~~~~~
 * C) case : close appears without parameter.
 * { name: value }
 *              ~~~
 *
 * D) case : appears parameter.
 * { name: value {} : }
 *              ~~~-
 *             parameter
 *
 * </pre>
 *
 * @param token the token.
 */
void ObjectParser::parseValueParameter(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Comma) {
        // A) case : comma appears without parameter.
    } else if (type == Token::Text) {
        // B) case : name appears without parameter and comma.
        iterator->push(token);
    } else if (type == Token::CloseObject) {
        // C) case : close appears without parameter.
        iterator->push(token);
    } else if (type != Token::Comma) {
        // D) case : appears parameter.
        iterator->push(token);
        Parser *parser = Parser::create(token, iterator);
        if (value != nullptr && parser != nullptr) {
            //value.parameter(parser->parse());
        }
    }
    state = State::ADD_FILED;
}

void ObjectParser::parseComma(Token *token) {
    const Token::Type type = token->type();
    if (type == Token::Comma) {
        state = State::NAME;
    } else if (type == Token::CloseObject) {
        state = State::FINISH;
    } else {
        state = State::NAME;
        iterator->push(token);
    }
}