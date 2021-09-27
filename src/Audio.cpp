/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Audio
*/

#include "Audio.hpp"

//test if throw destroy
//std::cout on dtor

Audio::Audio() :
    _sampleRate(44100), _isPlaying(false), _isRecording(false)
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Audio error: " << Pa_GetErrorText(err) << std::endl;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        throw AudioException(Pa_GetErrorText(err));
    }
    initParameters();
}

Audio::~Audio()
{
    PaError err;

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    std::cout << "Successfuly destroy Audio" << std::endl;
}

void Audio::initParameters()
{
    //INPUT PARAMETERS
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        throw AudioException("No default input device");
    }
    _inputParameters.channelCount = 2;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = nullptr;
    //OUTPUT PARAMETERS
    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cerr << "Error: No default output device." << std::endl;
        //IF NOT DESTRUCTED MISSING Pa_Terminate();
        throw AudioException("No default output device");
    }
    _outputParameters.channelCount = 2;
    _outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = nullptr;
}

void Audio::OpenInputStream(PaStreamCallback callback, void *data)
{
    PaError err;

    err = Pa_OpenStream(
        &stream,
        &_inputParameters,
        NULL,
        _sampleRate,
        FRAMES_PER_BUFFER,
        paClipOff,
        callback,
        data);
    if (err != paNoError) {
        throw AudioException(Pa_GetErrorText(err));
    }
}

void Audio::OpenOutputStream(PaStreamCallback callback, void *data)
{
    PaError err;

    err = Pa_OpenStream(
        &stream,
        nullptr,
        &_outputParameters,
        _sampleRate,
        FRAMES_PER_BUFFER,
        paClipOff,
        callback,
        data);
    if (err != paNoError) {
         throw AudioException(Pa_GetErrorText(err));
    }
}

void Audio::StartPlaying()
{
    if (!_isPlaying) {
        PaError err;
        err = Pa_StartStream(stream);
        if (err != paNoError) {
            throw AudioException(Pa_GetErrorText(err));
        }
        _isPlaying = true;
    }
}

void Audio::StartRecording()
{
    if (!_isRecording) {
        PaError err;
        err = Pa_StartStream(stream);
        if (err != paNoError) {
            throw AudioException(Pa_GetErrorText(err));
        }
        _isRecording = true;
    }
}

void Audio::StopPlaying()
{
    if (_isPlaying) {
        PaError err;
        err = Pa_StopStream(stream);
        if (err != paNoError) {
            throw AudioException(Pa_GetErrorText(err));
        }
        _isPlaying = false;
    }
}

void Audio::StopRecording()
{
    if (_isRecording) {
        PaError err;
        err = Pa_StopStream(stream);
        if (err != paNoError) {
            throw AudioException(Pa_GetErrorText(err));
        }
        _isRecording = false;
    }
}

void Audio::Close() {
    PaError err;

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        throw AudioException(Pa_GetErrorText(err));
    }
}

bool Audio::IsPlaying()
{
    return _isPlaying;
}

bool Audio::isRecording()
{
    return _isRecording;
}