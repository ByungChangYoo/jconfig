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

#ifndef CONFIG_BYTEBUFFER_H
#define CONFIG_BYTEBUFFER_H

#include <stack>

/*
 * @author ByungChang Yoo (blueeyes@potalab.com)
 */
class ByteBuffer {
private:
    const char *data;
    int length = 0;
    int position = 0;
    std::stack<char> pushed;

public:
    ByteBuffer(const char *data, const int length);

public:
    char peek() const;
    char next();
    void push(char c);
    bool more() const;
    int remaining() const;
};

#endif
