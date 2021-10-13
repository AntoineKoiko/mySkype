/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallHandler
*/

#include "CallHandler.hpp"
#include "SoundPacketManager.hpp"

CallHandler::CallHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> client) : _input(this), _udpNetwork(this), _client(client)
{
    std::cout << "->: ctor CallHandler" << std::endl;
    _input.openInputStream();
    _output.openOutputStream();
    //_connectedPeople.push_back(std::make_tuple("173.42.31.4", "Michel"));
}

CallHandler::~CallHandler()
{
    std::cout << "-> dtor CallHandler" << std::endl;
    _input.close();
    _output.close();
}

void CallHandler::call(const std::vector<std::string> &contact_to_call, const std::string &myIp)
{
    DataPacket data;
    std::string contacts;

    for (auto &contact : contact_to_call) {
        contacts.append(contact);
        contacts.append(";");
    }
    _connectedPeople.clear();
    _udpNetwork.connect(PORT_SOUND, myIp);
    _input.startRecording();
    _output.startPlaying();
    std::memcpy(data.data, contacts.data(), contacts.size());
    data.size = contacts.size();
    data.code = Babel::Req::CALL_SOMEONE;
    _client->send(DataPacketManager::serialize(data));
    std::cout << "Call Start" << std::endl;
    return;
}

void CallHandler::acceptCall()
{
    _input.startRecording();
    _output.startPlaying();
}

void CallHandler::rejectCall()
{

}

void CallHandler::hangup()
{
    _input.stopRecording();
    _output.stopPlaying();
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
        for (auto &people : _connectedPeople) {
            _udpNetwork.send(std::get<0>(people), PORT_SOUND, packetSerialize);
            std::cout << "On send des packet ip: " << std::get<0>(people) << "name " << std::get<1>(people) << std::endl;
        }
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

void CallHandler::addPeopleOnCall(const std::string &name, const std::string &ip)
{
    _connectedPeople.push_back(std::make_tuple(ip, name));
}

void CallHandler::setCallOwner(const std::string &callOwner)
{
    _callOwner = callOwner;
}

const std::string CallHandler::getCallOwner()
{
    return _callOwner;
}