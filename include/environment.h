/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SimpleIni.h>

constexpr const char *ENVIRONMENT =
#include "env.ini"
        ;

class Environment {
public:
    CSimpleIniA configfile;
    Environment() {
        configfile.SetUnicode();
        configfile.LoadData(ENVIRONMENT);
    }
};

#endif //ENVIRONMENT_H
