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

    Ptr<BotCommand> randomFactsCmd(new BotCommand());
    randomFactsCmd->command = "/randomfact";
    randomFactsCmd->description = "A random true fact";

    Ptr<BotCommand> randomCommitMessageCmd(new BotCommand());
    randomCommitMessageCmd->command = "/randomcommit";
    randomCommitMessageCmd->description = "A random commit message";

    Ptr<BotCommand> mememakerCmd(new BotCommand());
    mememakerCmd->command = "/mememaker";
    mememakerCmd->description = "Create memes using imgflip. Check usage with /mememaker";

    Ptr<BotCommand> memesCmd(new BotCommand());
    memesCmd->command = "/memes";
    memesCmd->description = "Use our memes";

    api()->setMyCommands({duckCmd, randomFactsCmd, randomCommitMessageCmd, mememakerCmd, memesCmd});
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

// Why this instead of InlineKeyboard?
// Because this one disappears after using. It's sad it's not cool as InlineKeyboard but I prefer this option instead of keeping it on the chat.
Ptr<ReplyKeyboardMarkup> MyBot::getMemesKeyboard() {
    Ptr<ReplyKeyboardMarkup> memeKeyboard(new ReplyKeyboardMarkup());
    memeKeyboard->oneTimeKeyboard = true;
    memeKeyboard->resizeKeyboard = true;

    std::vector<Ptr<KeyboardButton>> memeRow;
    Ptr<KeyboardButton> randomCommitButton(new KeyboardButton());
    randomCommitButton->text = "/randomcommit";
    memeRow.push_back(randomCommitButton);

    Ptr<KeyboardButton> randomFactButton(new KeyboardButton());
    randomFactButton->text = "/randomfact";
    memeRow.push_back(randomFactButton);

    Ptr<KeyboardButton> duckButton(new KeyboardButton());
    duckButton->text = "/duck";
    memeRow.push_back(duckButton);

    memeKeyboard->keyboard.push_back(memeRow);

    return memeKeyboard;
}

void MyBot::handleCommands(const Ptr<Message> &message) {
    static const std::unordered_map<std::string, int> commandMap = {
        {"/duck", 1},
        {"/randomfact", 2},
        {"/randomcommit", 3},
        {"/mememaker", 4},
        {"/memes", 5}
    };

    for (const auto& command : commandMap) {
        // Check if the message text starts with the command
        if (message->text.rfind(command.first, 0) == 0) {
            switch (command.second) {
                case 1:
                    api()->sendMessage(message->chat->id, Handler::handleDuck());
                break;
                case 2:
                    api()->sendMessage(message->chat->id, Handler::handleFact());
                break;
                case 3:
                    api()->sendMessage(message->chat->id, Handler::handleCommit());
                break;
                case 4:
                    api()->sendMessage(message->chat->id, Handler::handleMememaker(message->text));
                break;
                case 5:
                    api()->sendMessage(message->chat->id, "Select a meme: ",  0, "", {}, false, false, false, 0, false, getMemesKeyboard());
                break;
                default:
                    break;
            }
            return;
        }
    }
}

