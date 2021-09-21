/*
** EPITECH PROJECT, 2021
** babel
** File description:
** main
*/

#include <iostream>
#include <asio.hpp>

int main(int ac, char *av[])
{
    asio::io_service io_service_object;
    asio::ip::tcp::socket client_socket(io_service_object);

    if (ac < 2) {
        std::cerr << "Usage: ./" << av[0] << " <host>" << std::endl;
    }
    client_socket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(av[1]), 9999));
    asio::write(client_socket, asio::buffer("ptdr t ki ?"));
}