/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#ifndef HANDLER_H
#define HANDLER_H

#include <string>

#include "mememaker.h"

class Handler {
public:
    static std::string handleDuck();
    static std::string handleFact();
    static std::string handleCommit();
    static std::string handleMememaker(std::string& message);
};



#endif //HANDLER_H
