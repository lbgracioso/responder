/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#ifndef MEMEMAKER_H
#define MEMEMAKER_H
#include <string>
#include <vector>

class MemeMaker {
private:
    enum LIST_TYPE { RANDOM, TOP10 };
    static std::string extractQuotedText(std::istringstream& iss);
    std::string createMeme(std::istringstream& iss);
    static std::vector<std::string> getRandomMemes(std::vector<std::string> list);
    static std::vector<std::string> get10Memes(std::vector<std::string> list);
    std::string m_username;
	std::string m_password;
public:
    std::string createMeme(const std::string& memeId, const std::string& topText, const std::string& bottomText);
    static std::string help();
    static std::string handleList(LIST_TYPE type);
    static std::string handleList(std::istringstream& iss);
    std::string handleMessage(const std::string& message);
    MemeMaker();
};



#endif //MEMEMAKER_H
