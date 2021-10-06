/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallHandler
*/

#include "CallHandler.hpp"
#include "SoundPacketManager.hpp"

CallHandler::CallHandler() : _input(this), _udpNetwork(this)
{
    _input.openInputStream();
    _output.openOutputStream();
}

CallHandler::~CallHandler()
{
    _input.stopRecording();
    _output.stopPlaying();
}

void CallHandler::call([[maybe_unused]]const std::string &contact_to_call)
{
    _udpNetwork.connect(8082, std::string("127.0.0.1"));
    _input.startRecording();
    _output.startPlaying();
    std::cout << "Call Start" << std::endl;
    return;
}

void CallHandler::dataRecordedAvailable()
{
    Babel::Client::Audio::SoundFrameBuffer soundFrame;
    Babel::Client::Audio::SoundEncoded encoded;
    Babel::Client::Network::SoundPacket packet;
    std::vector<char> packetSerialize;

    while (!_input.isEmpty()) {
        soundFrame = _input.getSound();
        encoded = _audioEncoder.encodeAudio(soundFrame);
        packet = SoundPacketManager::createPacket(encoded);
        packetSerialize = SoundPacketManager::serialize(packet);
        _udpNetwork.send(std::string("0.0.0.0"), 8081, packetSerialize);
        std::cout << "On send des packet" << std::endl;
    }
}

void CallHandler::dataPacketAvailable(const std::vector<char> &packetSerialize)
{
    Babel::Client::Network::SoundPacket packet = SoundPacketManager::deserialize(packetSerialize);
    Babel::Client::Audio::SoundFrameBuffer soundFrame;
    Babel::Client::Audio::SoundEncoded encodedSound;

    encodedSound.encodedSound = std::vector<unsigned char>(packet.soundPayload, packet.soundPayload + packet.payloadSize);
    encodedSound.size = packet.payloadSize;
    soundFrame = _audioDecoder.decodeAudio(encodedSound);
    _output.addSound(soundFrame);
    std::cout << "Receive Packet" << std::endl;
}