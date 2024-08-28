#include "bot.h"
#include "log.h"

int main() {
    Log::init();
    Log::Info("Bot started");

    MyBot bot;
    bot.start();

    Log::shutdown();
    return 0;
}