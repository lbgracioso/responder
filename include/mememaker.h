/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef MEMEMAKER_H
#define MEMEMAKER_H
#include <string>

class MemeMaker {
private:
    static std::string extractQuotedText(std::istringstream& iss);
    std::string extractMemeInfo(std::string& memeId, std::istringstream& iss);
    std::string m_username;
	std::string m_password;
public:
    std::string createMeme(const std::string& memeId, const std::string& topText, const std::string& bottomText);
    static std::string help();
    std::string handleMessage(const std::string& message);
    MemeMaker();
};



#endif //MEMEMAKER_H
