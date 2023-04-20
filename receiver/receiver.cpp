/**
 * @file receiver.cpp
 * @author Rick Waasdorp (r.waasdorp@tudelft.nl)
 * @brief Receives a message from the sender over a tcp socket. Halts process
 * execution till a message is received. Works with both C++ sender.cpp and
 * Python sender.py implementations.
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
    const std::string endpoint = "tcp://localhost:4242";

    // initialize the 0MQ context
    zmqpp::context context;

    // generate a pull socket
    zmqpp::socket_type type = zmqpp::socket_type::pull;
    zmqpp::socket socket(context, type);

    // bind to the socket
    std::cout << "Connecting to " << endpoint << "..." << std::endl;
    socket.connect(endpoint);

    // receive the message
    std::cout << "Ready to Receive message..." << std::endl;

    zmqpp::message message;
    // decompose the message
    socket.receive(message);
    size_t t_rcv_ms = timestamp_ms();
    auto t_rcv = timestamp();
    std::cout << "Received Message at " << t_rcv << std::endl;

    std::string text;
    message >> text;
    size_t t_tx_ms = std::stoull(text);

    std::cout << "t_rcv:  " << (t_rcv_ms) << " ms" << std::endl;
    std::cout << "t_tx:   " << (t_tx_ms) << " ms" << std::endl;
    std::cout << "Time difference: " << (t_rcv_ms - t_tx_ms) << " ms" << std::endl;

    std::cout << "Finished." << std::endl;

    return 0;
}