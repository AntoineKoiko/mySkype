/*
** EPITECH PROJECT, 2021
** babel
** File description:
** utils
*/

#include "BabelServer.hpp"
#include <memory>

using namespace Babel::Server;

std::shared_ptr<BabelServer> get_server(bool set = false, std::shared_ptr<BabelServer> serv_ptr = nullptr)
{
    static std::shared_ptr<BabelServer> serv = nullptr;

    if (set)
        serv = serv_ptr;
    return serv;
}

std::vector<std::string> splitString(const std::string &s, const std::string &delimiter)
{
    std::string copy = std::string(s);
    size_t pos = 0;
    std::vector<std::string> tokenList;


    while ((pos = copy.find(delimiter)) != std::string::npos) {
        tokenList.push_back(copy.substr(0, pos));
        copy.erase(0, pos + delimiter.length());
    }
    if (!copy.empty()) {
        tokenList.push_back(copy);
    }
    return tokenList;
}