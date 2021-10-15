/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallHandler
*/

#ifndef CALLHANDLER_HPP_
#define CALLHANDLER_HPP_

#include <string>
#include <iostream>
#include "ICallHandler.hpp"
#include "AudioInput.hpp"
#include "AudioOutput.hpp"
#include "Udp.hpp"
#include "AudioEncoder.hpp"
#include "AudioDecoder.hpp"
#include "TcpClient.hpp"

#define PORT_SOUND 8085

class CallHandler : public Babel::Client::Audio::ICallHandler
{
    public:
        CallHandler(const std::shared_ptr<Babel::Client::Network::TcpClient>);
        ~CallHandler();

        void call(const std::vector<std::string> &contact_to_call, const std::string &myIp);
        void hangup();
        void acceptCall(const std::string &myIp);
        void rejectCall();
        void dataRecordedAvailable();
        void dataPacketAvailable(const std::vector<char> &packetSerialize);
        void addPeopleOnCall(const std::string &name, const std::string &ip);
        void setCallOwner(const std::string &callOwner);
        const std::string getCallOwner();
        const std::vector<std::tuple<std::string, std::string>> getConnectedPeople();

    protected:
    private:
        Babel::Client::Audio::AudioInput _input;
        Babel::Client::Audio::AudioOutput _output;
        Babel::Client::Network::Udp _udpNetwork;
        Babel::Client::Audio::AudioEncoder _audioEncoder;
        Babel::Client::Audio::AudioDecoder _audioDecoder;
        std::shared_ptr<Babel::Client::Network::TcpClient> _client;
        std::vector<std::tuple<std::string, std::string>> _connectedPeople;
        std::string _callOwner;

private:
};

#endif /* !CALLHANDLER_HPP_ */
