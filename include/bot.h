/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef RESPONDER_BOT_H
#define RESPONDER_BOT_H
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

constexpr const char *TOKEN =
#include "token"
        ;

class MyBot : public Bot {
public:
    MyBot() : Bot(TOKEN) {}

private:
    void onStart() override;
    void onStop() override;
    void onAnyMessage(const Ptr<Message> &message) override;
};

#endif//RESPONDER_BOT_H
