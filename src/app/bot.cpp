/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#include "bot.h"

void MyBot::onStart() {
    // Called before Bot starts receiving updates
    // Initialize your code here...
    std::cout << "Bot Started\n";
}

void MyBot::onStop() {
    // Called before Bot shuts down (triggered by Bot::stop())
    // Cleanup your code here
    std::cout << "Bot Stopped\n";
}

void MyBot::onAnyMessage(const Ptr<tgbotxx::Message> &message) {
    api()->sendMessage(message->chat->id, "Hi " + message->from->firstName + ", got your message!");
}