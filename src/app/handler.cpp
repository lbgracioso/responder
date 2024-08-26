/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#include "handler.h"

#include "bot.h"
#include "cpr/cpr.h"
#include "fmt/format.h"

#include <nlohmann/json.hpp>

std::string Handler::handleDuck() {
    std::string url = "https://random-d.uk/api/random";
    std::string response;

    try {
        cpr::Response r = cpr::Get(
                cpr::Url{url},
                cpr::Header{{"Content-Type", "application/json"}});

        fmt::println("Duck status code: {}", r.status_code);

        auto jsonObj = nlohmann::json::parse(r.text);
        response = jsonObj.at("url").get<std::string>();
    } catch (std::exception& e) {
        fmt::println("Duck Error: {}", e.what());
    }

    return response;
}
