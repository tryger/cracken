#!/usr/bin/python

## ./getwork 127.0.0.1 5
## hardcoded length 4        JUST FOR TEST

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind(("0.0.0.0", 7070))

s.listen(4)
p = s.accept()[0]

print "waiting for register packet..."

r = p.recv(3)

print "register packet received:"
print(r.encode("hex"))
print "sending acceptation\n"

p.send("\x01\x02\x02")

print "waiting to offer some work..."

r = p.recv(20)

print "work petition received:"
print(r.encode("hex"))
print "sending work 1"

p.send("\x02\x02\x05\x00\x00\x00\x00\x00\x1b\x00\x00\x00\x00\x00\x00\x00aaaa;bb;ccc;ddd;0123456789\x00")
r = p.recv(3)
print r.encode("hex")
print

print "waiting to offer some work..."

r = p.recv(20)

print "work petition received:"
print(r.encode("hex"))
print "sending work 2"

p.send("\x02\x02\x05\x00\x00\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00aaaa;cracken;ccc;ddd;0123456789\x00")
r = p.recv(3)
print r.encode("hex")

