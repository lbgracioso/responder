/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef RESPONDER_BOT_H
#define RESPONDER_BOT_H
#include "environment.h"
#include "handler.h"

#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

class MyBot : public Bot {
public:
    MyBot() : Bot(Environment().configfile.GetValue("telegram", "token")) {}

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
