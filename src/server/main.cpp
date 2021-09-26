// Server-side Synchronous Chatting Application
// using C++ asio

#include <asio.hpp>
#include <iostream>

using namespace std;
using namespace asio;
using namespace asio::ip;

// Driver program for receiving data from buffer
string getData(tcp::socket& socket)
{
    asio::streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

// Driver program to send data
void sendData(tcp::socket& socket, const string& message)
{
    write(socket,
          buffer(message + "\n"));
}

int main(int argc, char* argv[])
{
    io_service io_service;

    // Initializing server acceptor
    tcp::acceptor acceptor_server(io_service, tcp::endpoint(tcp::v4(), 9999));

    // Creating socket object
    tcp::socket server_socket(io_service);

    // waiting for connection (could also use async_accept to do it asynchronously)
    acceptor_server.accept(server_socket);

    // Reading username (waiting for first msg)
    string u_name = getData(server_socket);
    // Removing "\n" from the username
    u_name.pop_back();

    // Replying with default message to initiate chat
    string response, reply;
    reply = "Hello " + u_name + "!";
    cout << "Server: " << reply << endl;
    sendData(server_socket, reply);

    while (true) {

        // Fetching response
        response = getData(server_socket);
        response.pop_back();

        // Validating if the connection has to be closed
        if (response == "exit") {
            cout << u_name << " left!" << endl;
            break;
        }
        cout << u_name << ": " << response << endl;

        // Reading new message from input stream
        cout << "Server" << ": ";
        getline(cin, reply);
        sendData(server_socket, reply);

        if (reply == "exit")
            break;
    }
    return 0;
}