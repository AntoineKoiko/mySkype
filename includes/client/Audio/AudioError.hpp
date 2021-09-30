/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Audio Error
*/

#ifndef AUDIO_ERROR_HPP
#define AUDIO_ERROR_HPP

#include <iostream>

class AudioError : public std::exception
{
    public:
        AudioError(const std::string message);

        const char *what() const noexcept override;

    private:
        std::string _message;
};

class DecoderError : public AudioError
{
    public:
        DecoderError(const std::string message);
};

class EncoderError : public AudioError
{
    public:
        EncoderError(const std::string message);
};

class InputError : public AudioError
{
    public:
        InputError(const std::string message);
};

class OutputError : public AudioError
{
    public:
        OutputError(const std::string message);
};

#endif /* !AUDIO_ERROR_HPP */