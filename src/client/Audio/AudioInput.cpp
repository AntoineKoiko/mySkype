/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioInput
*/

#include "AudioInput.hpp"

using namespace Babel::Client::Audio;

AudioInput::AudioInput(ICallHandler *callHandler) : _callHandler(callHandler), _isRecording(false)
{
    PaError err = Pa_Initialize();

    if (err != paNoError)
    {
        throw InputError(Pa_GetErrorText(err));
    }
    _params.device = Pa_GetDefaultInputDevice();
    if (_params.device == paNoDevice)
    {
        throw InputError("No default input device !");
    }
    _params.channelCount = Audio::NumberOfChannels;
    _params.sampleFormat = paFloat32;
    _params.suggestedLatency = Pa_GetDeviceInfo(_params.device)->defaultLowInputLatency;
    _params.hostApiSpecificStreamInfo = nullptr;
}

void AudioInput::info()
{
    int numDevices = Pa_GetDeviceCount();
    const PaDeviceInfo *deviceInfo;
    int defaultDisplayed;

    printf("Number of devices = %d\n", numDevices);
    for (int i = 0; i < numDevices; i++)
    {
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("--------------------------------------- device #%d %s\n", i, deviceInfo->name);

        /* Mark global and API specific default devices */
        defaultDisplayed = 0;
        if (i == Pa_GetDefaultInputDevice())
        {
            printf("[ Default Input");
            defaultDisplayed = 1;
        }
        else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultInputDevice)
        {
            const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
            printf("[ Default %s Input", hostInfo->name);
            defaultDisplayed = 1;
        }

        if (i == Pa_GetDefaultOutputDevice())
        {
            printf((defaultDisplayed ? "," : "["));
            printf(" Default Output");
            defaultDisplayed = 1;
        }
        else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultOutputDevice)
        {
            const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
            printf((defaultDisplayed ? "," : "["));
            printf(" Default %s Output", hostInfo->name);
            defaultDisplayed = 1;
        }

        if (defaultDisplayed)
            printf(" ]\n");
    }
}

AudioInput::~AudioInput()
{
    PaError err;

    err = Pa_Terminate();
    if (err != paNoError)
    {
        std::cerr << "Error: Pa_Terminate(): " << Pa_GetErrorText(err) << std::endl;
    }
    else
    {
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
    if (err != paNoError)
    {
        throw InputError(Pa_GetErrorText(err));
    }
}

void AudioInput::startRecording()
{
    if (!_isRecording)
    {
        PaError err;
        err = Pa_StartStream(_stream);
        if (err != paNoError)
        {
            throw InputError(Pa_GetErrorText(err));
        }
        _isRecording = true;
    }
}

SoundFrameBuffer AudioInput::getSound()
{
    SoundFrameBuffer soundBuffer;

    soundBuffer = _sound.front();
    _sound.pop();
    return soundBuffer;
}

bool AudioInput::isEmpty() const
{
    return _sound.empty();
}

void AudioInput::stopRecording()
{
    if (_isRecording)
    {
        PaError err;
        err = Pa_StopStream(_stream);
        if (err != paNoError)
        {
            throw InputError(Pa_GetErrorText(err));
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

    if (audioRecorded)
    {
        std::copy(audioRecorded, audioRecorded + Audio::BufferSize, soundBuffer.frames.begin());
        _this->_sound.push(soundBuffer);
    }
    _this->_callHandler->dataRecordedAvailable();
    return paContinue;
}

void AudioInput::close()
{
    PaError err = Pa_CloseStream(_stream);

    if (err != paNoError)
    {
        throw InputError(Pa_GetErrorText(err));
    }
}