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

            virtual void call(const std::vector<std::string> &contact_to_call, const std::string &myIp) = 0;
            virtual void hangup() = 0;
            virtual void acceptCall(const std::string &myIp) = 0;
            virtual void rejectCall() = 0;
            virtual void dataRecordedAvailable() = 0;
            virtual void dataPacketAvailable(const std::vector<char> &packetSerialize) = 0;
            virtual void addPeopleOnCall(const std::string &name, const std::string &ip) = 0;
            virtual void setCallOwner(const std::string &callOwner) = 0;
            virtual const std::string getCallOwner() = 0;
            virtual const std::vector<std::tuple<std::string, std::string>> getConnectedPeople() = 0;

    protected:
    private:
};
}



#endif /* !ICALLHANDLER_HPP_ */
