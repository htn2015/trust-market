import socket

s = socket.socket()
s.bind(("localhost", 666))
s.listen(1)

sc, addr = s.accept()

while True:
      received = sc.recv(1024)
      print "Received: ", received
      sc.send(received)

sc.close()
s.close()