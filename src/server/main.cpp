/*
** EPITECH PROJECT, 2021
** babel
** File description:
** main
*/

#include <iostream>
#include <asio.hpp>
#include <string>

void read_it(asio::ip::tcp::socket sock);

asio::streambuf b;

void accept_handler(const asio::error_code& error)
{
    if (!error) {
        // Accept succeeded.
    }
}

void handle_read(const asio::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::istream is(&b);
        std::string line;
        std::getline(is, line);
        std::cout << "line " << line << std::endl;
    }
}

void read_it(asio::ip::tcp::socket *sock) {
    asio::async_read_until(*sock, b, "\n", handle_read);
}

int main(int ac, char *av[])
{
    asio::io_service io_service_object;
    asio::ip::tcp::acceptor acceptor_server(
        io_service_object, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9999));
    asio::ip::tcp::socket server_socket(io_service_object);
    asio::streambuf buf;

    acceptor_server.accept(server_socket); // TODO: use async accept
    read_it(&server_socket);
}