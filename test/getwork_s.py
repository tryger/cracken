#!/usr/bin/python

## ./getwork 127.0.0.1 4
## hardcoded length 4        JUST FOR TEST

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind(("0.0.0.0", 7070))

s.listen(4)
p = s.accept()[0]

r = p.recv(20)

print(r.encode("hex"))

p.send("\x02\x02\x05\x00\x00\x00\x00\x00\x1b\x00\x00\x00\x00\x00\x00\x00aaaa;bb;ccc;ddd;0123456789\x00")
