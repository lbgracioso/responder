/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef RESPONDER_BOT_H
#define RESPONDER_BOT_H
#include "handler.h"

#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

constexpr const char *TELEGRAM_TOKEN =
#include "telegram.token"
        ;

class MyBot : public Bot {
public:
    MyBot() : Bot(TELEGRAM_TOKEN) {}

private:
    Handler m_handler;
    void setCommands();
    void onStart() override;
    void onStop() override;
    void onAnyMessage(const Ptr<Message> &message) override;
    void onCommand(const Ptr<Message> &message) override;
    void handleCommands(const Ptr<Message> &message);
};

#endif//RESPONDER_BOT_H
