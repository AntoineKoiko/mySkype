/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Audio Error
*/

#include "AudioError.hpp"

AudioError::AudioError(const std::string message)
{
    _message = message;
}

const char *AudioError::what() const noexcept
{
    return _message.c_str();
}

DecoderError::DecoderError(const std::string message) : AudioError("Decoder Error : " + message) {}

EncoderError::EncoderError(const std::string message) : AudioError("Encoder Error : " + message) {}

InputError::InputError(const std::string message) : AudioError("Input Error : " + message) {}

OutputError::OutputError(const std::string message) : AudioError("Output Error : " + message) {}