"""
@file sender.cpp
@author Rick Waasdorp (r.waasdorp@tudelft.nl)
@brief Sends a message from to a receiver over a tcp socket. Halts process
execution till a key is pressed to send the message. Works with both C++
reciever.cpp and Python reciever.py implementations.
@version 0.1
@date 2023-04-20
@copyright Copyright (c) 2023
"""

import time
from datetime import datetime
import zmq

endpoint = "tcp://*:4242"

context = zmq.Context()
socket = context.socket(zmq.PUSH)

print(f"Connecting to {endpoint}...")
socket.bind(endpoint)

input("Press any key to send message...")
t_tx = datetime.now()
t_tx_ms = int(time.time() * 1000)
socket.send_string(str(t_tx_ms))

socket.close()
print("Finished.")
