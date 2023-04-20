"""
@file receiver.cpp
@author Rick Waasdorp (r.waasdorp@tudelft.nl)
@brief Receives a message from the sender over a tcp socket. Halts process
execution till a message is received. Works with both C++ sender.cpp and
Python sender.py implementations.
@version 0.1
@date 2023-04-20
@copyright Copyright (c) 2023
"""

import time
from datetime import datetime
import zmq

endpoint = "tcp://localhost:4242"

context = zmq.Context()
socket = context.socket(zmq.PULL)
print(f"Connecting to {endpoint}...")
socket.connect(endpoint)

print("Ready to Receive message...")

message = socket.recv()
t_rcv = datetime.now()
t_rcv_ms = int(time.time() * 1000)

print(f"Received Message at {t_rcv}")
print(f"Message: {message}")


t_tx_ms = int(message)
print(f"t_rcv:      {t_rcv_ms} ms")
print(f"t_tx:       {t_tx_ms} ms")
print(f"Time difference: {t_rcv_ms - t_tx_ms} ms")

socket.close()
print("Finished.")
