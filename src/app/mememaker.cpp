/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#include "mememaker.h"

#include "environment.h"
#include "cpr/cpr.h"
#include "fmt/format.h"

#include <nlohmann/json.hpp>

std::string MemeMaker::createMeme(const std::string &memeId, const std::string &topText, const std::string &bottomText) {
    std::string url = "https://api.imgflip.com/caption_image";
    std::string response;

    std::string form_params = fmt::format(
        "username={}&password={}&text0={}&text1={}&template_id={}",
        cpr::util::urlEncode(m_username),
        cpr::util::urlEncode(m_password),
        cpr::util::urlEncode(topText),
        cpr::util::urlEncode(bottomText),
        cpr::util::urlEncode(memeId)
    );

    try {
        cpr::Response r = cpr::Post(
                cpr::Url{url},
                cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                cpr::Body{form_params});

        if (r.status_code == 200) {
            nlohmann::json jsonResponse = nlohmann::json::parse(r.text);
            if (jsonResponse["success"].get<bool>()) {
                response = jsonResponse["data"]["url"].get<std::string>();
            } else {
                fmt::println("MemeMaker Error: {}\n", jsonResponse["error_message"].get<std::string>());
                return "MemeMaker couldn't create or find this meme.";
            }
        } else {
            fmt::println("MemeMaker Error: Received status code {}\n", r.status_code);
            return "MemeMaker has a problem. Please contact the administrator.";
        }

    } catch (std::exception& e) {
        fmt::println("MemeMaker Error: {}", e.what());
    }

    fmt::println("MemeMaker made a meme with success: {}", response);
    return response;
}

std::string MemeMaker::help() {
    return fmt::format("{}\n\n{}", "You can use mememaker with:\n/mememaker <memeId> \"Top text here (between quotes)\" \"Bottom text here (between quotes)\"", "Find meme IDs on imgflip site:\nhttps://imgflip.com/popular-meme-ids");
}

std::string MemeMaker::extractQuotedText(std::istringstream& iss) {
    std::string result;
    std::getline(iss, result, '"');
    std::getline(iss, result, '"');
    return result;
}

std::string MemeMaker::extractMemeInfo(std::string& memeId, std::istringstream& iss)
{
    std::string topText;
    std::string bottomText;

    // Extract topText and bottomText, assuming they are enclosed in quotes
    try {
        topText = extractQuotedText(iss);
        bottomText = extractQuotedText(iss);
    } catch (const std::exception& e) {
        return "Error parsing the meme command.";
    }

    return createMeme(memeId, topText, bottomText);
}

std::string MemeMaker::handleMessage(const std::string& message) {
    std::string subCommand;

    std::istringstream iss(message);

    // Extract the command part "/mememaker" and ignore it
    std::string command;
    iss >> command;

    // Extract subCommand
    iss >> subCommand;

    if (subCommand.empty()) {
        return help();
    }

    return extractMemeInfo(subCommand, iss);
}

MemeMaker::MemeMaker() {
    m_username = Environment().configfile.GetValue("mememaker", "username");
    m_password = Environment().configfile.GetValue("mememaker", "password");
}