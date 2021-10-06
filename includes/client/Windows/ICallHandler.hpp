/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ICallHandler
*/

#ifndef ICALLHANDLER_HPP_
#define ICALLHANDLER_HPP_

#include <string>
#include <vector>

namespace Babel::Client::Audio
{
    class ICallHandler {
        public:
            virtual ~ICallHandler() = default;

            virtual void call(const std::string &contact_to_call) = 0;
            virtual void dataRecordedAvailable() = 0;
            virtual void dataPacketAvailable(const std::vector<char> &packetSerialize) = 0;

    protected:
    private:
};
}



#endif /* !ICALLHANDLER_HPP_ */
