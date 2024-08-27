/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef HANDLER_H
#define HANDLER_H

#include <string>

class Handler {
public:
    static std::string handleDuck();
    static std::string handleFact();
    static std::string handleCommit();
};



#endif //HANDLER_H
