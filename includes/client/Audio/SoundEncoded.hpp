/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundEncoded
*/

#ifndef SOUNDENCODED_HPP_
#define SOUNDENCODED_HPP_

#include <vector>
#include "Audio.hpp"

namespace Babel::Client::Audio
{
    class SoundEncoded {
        public:
            SoundEncoded();
            ~SoundEncoded();

            std::vector<unsigned char> encodedSound;
            unsigned int size;

        protected:
        private:
    };
}

#endif /* !SOUNDENCODED_HPP_ */
