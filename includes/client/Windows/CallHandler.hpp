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

class CallHandler : public Babel::Client::Audio::ICallHandler
{
    public:
        CallHandler();
        ~CallHandler();

        void make_call(const std::string &contact_to_call);
        void dataRecordedAvailable();
        void dataPacketAvailable(const std::vector<char> &packetSerialize);

    protected:
    private:
        Babel::Client::Audio::AudioInput _input;
        Babel::Client::Audio::AudioOutput _output;
        Babel::Client::Network::Udp _udpNetwork;
        Babel::Client::Audio::AudioEncoder _audioEncoder;
        Babel::Client::Audio::AudioDecoder _audioDecoder;

private:
};

#endif /* !CALLHANDLER_HPP_ */
