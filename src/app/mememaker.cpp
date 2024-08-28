/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include "mememaker.h"
#include "environment.h"
#include "log.h"
#include "cpr/cpr.h"
#include "fmt/format.h"

#include <random>
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
                Log::Error("MemeMaker Error: {}\n", jsonResponse["error_message"].get<std::string>());
                return "MemeMaker couldn't create or find this meme.";
            }
        } else {
            Log::Error("MemeMaker Error: Received status code {}\n", r.status_code);
            return "MemeMaker has a problem. Please contact the administrator.";
        }

    } catch (std::exception& e) {
        Log::Error("MemeMaker Error: {}", e.what());
    }

    Log::Info("MemeMaker made a meme with success: {}", response);
    return response;
}

std::string MemeMaker::help() {
    return fmt::format("{}\n\n{}\n\n{}\n\n{}",
                                    "You can use mememaker with:",
                                    "/mememaker create <memeId> \"Top text here (between quotes)\" \"Bottom text here (between quotes)\"",
                                    "/mememaker list for the TOP10 memes OR /mememaker list random for 10 random memes",
                                    "Find meme IDs on imgflip site:\nhttps://imgflip.com/popular-meme-ids");
}

std::string MemeMaker::handleList(LIST_TYPE type) {
    std::string url = "https://api.imgflip.com/get_memes";

    try {
        cpr::Response r = cpr::Get(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}});

        Log::Info ("MemeMaker get_memes status code: {}", r.status_code);

        auto jsonObj = nlohmann::json::parse(r.text);
        if (jsonObj.contains("data") && jsonObj["data"].contains("memes")) {
            std::vector<std::string> memeList;
            for (const auto& meme : jsonObj["data"]["memes"]) {
                std::string id = meme["id"];
                std::string name = meme["name"];
                std::string URL = meme["url"];
                memeList.emplace_back(fmt::format("ID: {}\nName: {}\nURL: {}", id, name, URL));
            }

            switch(type) { \
                case RANDOM:
                    return fmt::format("Random popular memes:\n\n {}", fmt::join(getRandomMemes(memeList), "\n\n"));
                    break;
                case TOP10:
                    return fmt::format("TOP 10 memes:\n\n {}", fmt::join(get10Memes(memeList), "\n\n"));
                    break;
                default:
                    return help();
                    break;
            }
        }

    } catch (std::exception& e) {
        Log::Error("MemeMaker get_memes error: {}", e.what());
    }

    return "MemeMaker had trouble finding popular memes";
}

std::string MemeMaker::handleList(std::istringstream &iss) {
    std::string type;
    iss >> type;

    if (type == "random") {
        return handleList(LIST_TYPE::RANDOM);
    } else {
        return handleList(LIST_TYPE::TOP10);
    }
}

std::string MemeMaker::extractQuotedText(std::istringstream& iss) {
    std::string result;
    std::getline(iss, result, '"');
    std::getline(iss, result, '"');
    return result;
}

std::string MemeMaker::createMeme(std::istringstream& iss)
{
    std::string memeId;
    iss >> memeId;
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

std::vector<std::string> MemeMaker::getRandomMemes(std::vector<std::string> list) {
    // Create a random device and use it to seed the generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine

    // Shuffle the vector using the generator
    std::shuffle(list.begin(), list.end(), gen);

    return get10Memes(list);
}

std::vector<std::string> MemeMaker::get10Memes(std::vector<std::string> list) {
    // Retrieve the first 10 memes or the actual amount (if lesser than 10)
    size_t numMemesToReturn = std::min(list.size(), static_cast<size_t>(10));
    std::vector<std::string> selectedMemes(list.begin(), list.begin() + numMemesToReturn);
    return selectedMemes;
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
    } else if (subCommand == "list") {
        return handleList(iss);
    } else if (subCommand == "create") {
        return createMeme(iss);
    }

    return help();
}

MemeMaker::MemeMaker() {
    m_username = Environment().configfile.GetValue("mememaker", "username");
    m_password = Environment().configfile.GetValue("mememaker", "password");
}