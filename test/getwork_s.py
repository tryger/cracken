import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind(("0.0.0.0", 7070))

s.listen(4)
p = s.accept()[0]

r = p.recv(20)

print(r.encode("hex"))

p.send("\x02\x02\x04\x00\x00\x00\x00\x00\x0f\x00\x00\x00\x00\x00\x00\x00aa;bbb;ccc;ddd")
