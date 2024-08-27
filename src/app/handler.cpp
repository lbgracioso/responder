/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include "log.h"
#include <handler.h>
#include <cpr/cpr.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

std::string Handler::handleDuck() {
    std::string url = "https://random-d.uk/api/random";
    std::string response;

    try {
        cpr::Response r = cpr::Get(
                cpr::Url{url},
                cpr::Header{{"Content-Type", "application/json"}});

        Log::Info("Duck status code: {}", r.status_code );

        auto jsonObj = nlohmann::json::parse(r.text);
        response = jsonObj.at("url").get<std::string>();
    } catch (std::exception& e) {
        Log::Error("Duck Error: {}", e.what());
    }

    return response;
}

std::string Handler::handleFact() {
    std::string url = "https://uselessfacts.jsph.pl/api/v2/facts/random";
    std::string response;

    try {
        cpr::Response r = cpr::Get(
                cpr::Url{url},
                cpr::Header{{"Content-Type", "application/json"}});

        Log::Info("Random Fact status code: {}", r.status_code);

        auto jsonObj = nlohmann::json::parse(r.text);
        response = jsonObj.at("text").get<std::string>();
    } catch (std::exception& e) {
        Log::Error("Random Fact Error: {}", e.what());
    }

    return response;
}

std::string Handler::handleCommit() {
    std::string url = "https://whatthecommit.com/index.txt";
    std::string response;

    try {
        cpr::Response r = cpr::Get(
                cpr::Url{url},
                cpr::Header{{"Content-Type", "application/json"}});

        Log::Info("Random Commit status code: {}", r.status_code);

        response = r.text;
    } catch (std::exception& e) {
        Log::Error("Random Fact Error: {}", e.what());
    }

    return response;
}

std::string Handler::handleMememaker(std::string& message) {
    return MemeMaker().handleMessage(message);
}
