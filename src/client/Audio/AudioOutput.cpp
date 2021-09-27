/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioOutput
*/

#include "AudioOutput.hpp"

using namespace Babel::Client::Audio;

AudioOutput::AudioOutput() : _isPlaying(false)
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Audio error: " << Pa_GetErrorText(err) << std::endl;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        //throw AudioException(Pa_GetErrorText(err));
    }
    _params.device = Pa_GetDefaultOutputDevice();
    if (_params.device == paNoDevice) {
        std::cerr << "Error: No default output device." << std::endl;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        //throw AudioException("No default output device");
        return;
    }
    _params.channelCount = Audio::NumberOfChannels;
    _params.sampleFormat = paFloat32;
    _params.suggestedLatency = Pa_GetDeviceInfo(_params.device)->defaultLowOutputLatency;
    _params.hostApiSpecificStreamInfo = nullptr;
}

AudioOutput::~AudioOutput()
{
    PaError err;

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    } else {
        std::cout << "Successfuly destroy Audio" << std::endl;
    }
}

void AudioOutput::openOutputStream()
{
    PaError err;

    err = Pa_OpenStream(
        &_stream,
        nullptr,
        &_params,
        Audio::SamplingRate,
        Audio::FrameSize,
        paClipOff,
        this->callback,
        this);
    if (err != paNoError) {
        //throw AudioException(Pa_GetErrorText(err));
        return;
    }
}

void AudioOutput::startPlaying()
{
    if (!_isPlaying) {
        PaError err;
        err = Pa_StartStream(_stream);
        if (err != paNoError) {
            //throw AudioException(Pa_GetErrorText(err));
            return;
        }
        _isPlaying = true;
    }
}

void AudioOutput::stopPlaying()
{
    if (_isPlaying) {
        PaError err;
        err = Pa_StopStream(_stream);
        if (err != paNoError) {
            // throw AudioException(Pa_GetErrorText(err));
            return;
        }
        _isPlaying = false;
    }
}
#include <iostream>
int AudioOutput::callback([[maybe_unused]] const void *inputBuffer, void *outputBuffer,
                   [[maybe_unused]] unsigned long framesPerBuffer,
                   [[maybe_unused]] const PaStreamCallbackTimeInfo *timeInfo,
                   [[maybe_unused]] PaStreamCallbackFlags statusFlags,
                   void *userData)
{
    auto _this = static_cast<AudioOutput *>(userData);
    SoundFrameBuffer frameBuffer;
    float *audio = (float *)outputBuffer;

    std::memset(outputBuffer, 0, Audio::BufferSize);
    if (!_this->_sound.empty()) {
        frameBuffer = _this->_sound.front();
        std::copy(frameBuffer.frames.begin(), frameBuffer.frames.end(), audio);
        _this->_sound.pop();
    }
    return paContinue;
}

void AudioOutput::close()
{
    PaError err = Pa_CloseStream(_stream);

    if (err != paNoError) {
        //throw AudioException(Pa_GetErrorText(err));
    }
}