/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#include "fmt/format.h"
#include <bot.h>

void MyBot::setCommands()
{
    Ptr<BotCommand> duckCmd(new BotCommand());
    duckCmd->command = "/duck";
    duckCmd->description = "A random quack";
    api()->setMyCommands({duckCmd});
}

void MyBot::onStart() {
    // Called before Bot starts receiving updates
    // Initialize your code here...
    api()->deleteWebhook(true);
    setCommands();
    fmt::println("Bot {} Started", api()->getMe()->username);
}

void MyBot::onStop() {
    // Called before Bot shuts down (triggered by Bot::stop())
    // Cleanup your code here
    fmt::println("Bot Stopped");
}

void MyBot::onAnyMessage(const Ptr<tgbotxx::Message> &message) {
}

void MyBot::onCommand(const Ptr<Message> &message) {
    handleCommands(message);
}

void MyBot::handleCommands(const Ptr<Message> &message) {
    static const std::unordered_map<std::string, int> commandMap = {
        {"/duck", 1}
    };

    auto it = commandMap.find(message->text);
    if (it != commandMap.end()) {
        switch (it->second) {
            case 1:
                api()->sendMessage(message->chat->id, m_handler.handleDuck());
            break;
            default:
                break;
        }
    } else {
        // For now, it does nothing
    }
}

