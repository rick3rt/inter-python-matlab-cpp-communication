/**
 * @file sender.cpp
 * @author Rick Waasdorp (r.waasdorp@tudelft.nl)
 * @brief Sends a message from to a receiver over a tcp socket. Halts process
 * execution till a key is pressed to send the message. Works with both C++
 * reciever.cpp and Python reciever.py implementations.
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>

#include "helper.hpp"

int main(int argc, char *argv[])
{
    const std::string endpoint = "tcp://*:4242";

    // initialize the 0MQ context
    zmqpp::context context;

    // generate a push socket
    zmqpp::socket_type type = zmqpp::socket_type::push;
    zmqpp::socket socket(context, type);

    // open the connection
    std::cout << "Connecting to " << endpoint << "..." << std::endl;
    socket.bind(endpoint);

    std::cout << "Press any key to send message..."; // << std::endl;
    std::cin.get();

    zmqpp::message message;
    auto t_tx = timestamp();
    size_t t_tx_ms = timestamp_ms();
    message << std::to_string(t_tx_ms);
    socket.send(message);
    std::cout << "Message send at " << t_tx << std::endl;

    // std::cout << "Sent message." << std::endl;
    std::cout << "Finished." << std::endl;

    return 0;
}