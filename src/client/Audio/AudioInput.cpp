/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioInput
*/

#include "AudioInput.hpp"

using namespace Babel::Client::Audio;

AudioInput::AudioInput() : _isRecording(false)
{
    PaError err = Pa_Initialize();

    if (err != paNoError) {
        std::cerr << "Audio error: " << Pa_GetErrorText(err) << std::endl;
        //throw AudioException(Pa_GetErrorText(err));
        return;
    }
    _params.device = Pa_GetDefaultInputDevice();
    if (_params.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        return;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        //throw AudioException("No default input device");
    }
    _params.channelCount = Audio::NumberOfChannels;
    _params.sampleFormat = paFloat32;
    _params.suggestedLatency = Pa_GetDeviceInfo(_params.device)->defaultLowInputLatency;
    _params.hostApiSpecificStreamInfo = nullptr;
}

AudioInput::~AudioInput()
{
    PaError err;

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    } else {
        std::cout << "Successfuly destroy Audio" << std::endl;
    }
}

void AudioInput::openInputStream()
{
    PaError err;

    err = Pa_OpenStream(
        &_stream,
        &_params,
        NULL,
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

void AudioInput::startRecording()
{
     if (!_isRecording) {
        PaError err;
        err = Pa_StartStream(_stream);
        if (err != paNoError) {
            //throw AudioException(Pa_GetErrorText(err));
            return;
        }
        _isRecording = true;
    }
}

void AudioInput::stopRecording()
{
    if (_isRecording) {
        PaError err;
        err = Pa_StopStream(_stream);
        if (err != paNoError) {
            // throw AudioException(Pa_GetErrorText(err));
            return;
        }
        _isRecording = false;
    }
}

int AudioInput::callback(const void *inputBuffer, [[maybe_unused]] void *outputBuffer,
                   [[maybe_unused]] unsigned long framesPerBuffer,
                   [[maybe_unused]] const PaStreamCallbackTimeInfo *timeInfo,
                   [[maybe_unused]] PaStreamCallbackFlags statusFlags,
                   void *userData)
{
    auto _this = static_cast<AudioInput *>(userData);
    float *audioRecorded = (float *)inputBuffer;
    SoundFrameBuffer soundBuffer;

    if (audioRecorded) {
        std::copy(audioRecorded, audioRecorded+Audio::BufferSize, soundBuffer.frames.begin());
        _this->_sound.push(soundBuffer);
    }
    return paContinue;
}

void AudioInput::close()
{
    PaError err = Pa_CloseStream(_stream);

    if (err != paNoError) {
        //throw AudioException(Pa_GetErrorText(err));
    }
}