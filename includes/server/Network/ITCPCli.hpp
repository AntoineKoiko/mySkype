/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ITCPCli
*/

#ifndef ITCPCLI_HPP_
#define ITCPCLI_HPP_

#include <iostream>

namespace Babel::Server::Network
{
    class ITCPCli {
        public:
            virtual ~ITCPCli() = default;

            virtual void read() = 0;
            virtual void write(int code, const char data[2064]) = 0;
            virtual const std::string getIpString() const = 0;

        protected:
        private:
    };
}

#endif /* !ITCPCLI_HPP_ */
